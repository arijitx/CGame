#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<pthread.h>
#include "util.h"
#include "config.h"
#include "http.h"
#include "game.h"

map<string,game*> game_array;
typedef std::pair<std::string, game*> game_pair;

#include "paths.h"


#include<bits/stdc++.h>

using namespace std;



void * respond(void *arg){
  int client=((int *)arg)[0];
  char req[9999];
  int rcvd;
  int status_code=-1;
  rcvd=recv(client,req,9999,0);
  if(rcvd>0){
    http *p=new http(req);
    map<string,string> data=p->get_data();
    map<string,string> :: iterator it;
    cout<<p->get_url()<<endl;
    string resp="HTTP/1.0 200 OK\nConnection: keep-alive\n";
    resp=resp+process_req(p->get_url(),p->get_header(),p->get_data());
    send(client,resp.c_str(),strlen(resp.c_str()),0);
    shutdown(client,SHUT_RDWR);
    close(client);
    status_code=1;
  }else{
    printf(RED"Error in Recieveing \n"RESET);
  }
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

  printf(GRN "Socket Listening to : %d\n"RESET,PORT);
  return server_fd;
}

int main(){
  int PORT=8001;
  //printing menu and options and Configs
  print_header(1);
  print_config();
  pthread_attr_t ptatr;
  pthread_attr_init(&ptatr);
  //init array for storing client info
  int clients[CONMAX];
  pthread_t pthreads[CONMAX];
  int i;
  for(i=0;i<CONMAX;i++)
    clients[i]=-1;
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
      clients[slot]=accept(server,(struct sockaddr *)&client_addr,&addr_len);
      if(clients[slot]<0){
        printf(RED"Socket Accept Failed"RESET);
      }else{
        pthread_create(&pthreads[slot],&ptatr,&respond,&clients[slot]);
        slot++;
        while (clients[slot]!=-1) slot = (slot+1)%CONMAX;
      }
    }
  }

  return 0;
}
