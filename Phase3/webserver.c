#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<pthread.h>
#include<mutex>
#include<atomic>

#include "common/util.h"
#include "common/config.h"
#include "web/static_loader.h"
#include "web/http.h"
#include "web/paths.h"
#include "ThreadPool.h"

#include<bits/stdc++.h>


mutex mtx;
using namespace std;
vector<pair<int,int> > clients;


void respond(pair<int,int> x){
  //pair<int,int> *x=(pair<int,int> *) args;
  int client=x.first;
  int posinarray=x.second;
  //cout<<"clien posinarray "<<client<<" "<<posinarray<<endl;
  char req[10000];
  int rcvd;
  int status_code=-1;
  rcvd=recv(client,req,10000,0);
  if(rcvd>0){
    http *p=new http(req,1);
    map<string,string> data=p->get_data();
    string resp="HTTP/1.0 200 OK\nConnection: keep-alive\n";
    resp=resp+process_req(p->get_url(),p->get_header(),p->get_data());
    send(client,resp.c_str(),strlen(resp.c_str()),0);
    shutdown(client,SHUT_RDWR);
    close(client);
    status_code=1;
  }else{
    printf(RED"Error in Recieveing \n"RESET);
  }
  mtx.lock();
  clients[posinarray].first=-1;
  mtx.unlock();
}


int start_server(int PORT){
  struct sockaddr_in server_addr;
  int addr_len=sizeof(server_addr);

  char data[BYTES]={0};
  int server_fd;

  //init socket
  if((server_fd=socket(AF_INET,SOCK_STREAM,0))==0){
    printf(RED"Socket Creation Failed\n"RESET);
    return -1;
  }
  int opt = 1;
  setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));


  //initialize server address
  bzero((char *) &server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons( PORT );

  //binding socket
  if (bind(server_fd, (struct sockaddr *)&server_addr,sizeof(server_addr))<0)
  {
      printf(RED"Socket Binding Failed\n"RESET);
      return -1;
  }

  //listening to port
  if (listen(server_fd, 3) < 0)
  {
      printf(RED"Socket Listening Failed\n"RESET);
      return -1;
  }

  printf(GRN "Socket Listening to : %d\n\n\n"RESET,PORT);
  return server_fd;
}

int main(){
  load_all_static_files();
  int PORT=PORT_WEB;
  ThreadPool pool(50);
  //printing menu and options and Configs
  print_header(1);
  print_config();
  printf("WEB SERVER\n");
  //pthread_attr_t ptatr;
  //pthread_attr_init(&ptatr);
  //init array for storing client info

  //pthread_t pthreads[CONMAX];
  int i;
  clients.resize(CONMAX);
  for(i=0;i<CONMAX;i++)
    clients[i].first=-1,clients[i].second=i;
  int slot=0;

  // server init
  int server;
  struct sockaddr_in client_addr;
  socklen_t addr_len;

  //start server
  if((server=start_server(PORT))>0){

    //run infinite and wait for connections
    while(1){
      addr_len=sizeof(client_addr);
      clients[slot].first=accept(server,(struct sockaddr *)&client_addr,&addr_len);
      if(clients[slot].first<0){
        printf(RED"Socket Accept Failed"RESET);
      }else{
        //pthread_create(&pthreads[slot],&ptatr,&respond,&clients[slot]);
        pair<int,int> client_sock=clients[slot];
        pool.enqueue([client_sock]{
            respond(client_sock);
        });
        slot++;
        while (clients[slot].first!=-1) slot = (slot+1)%CONMAX;
      }
    }
  }

  return 0;
}
