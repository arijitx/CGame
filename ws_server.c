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

#include "libwshandshake.hpp"
#include "ws_util.h"
#include "process_game.h"
#include <iostream>




#include "paths.h"


#include<bits/stdc++.h>

using namespace std;
int clients[CONMAX];

void * respond(void *arg){
  int client=((int *)arg)[0];
  string r="";
  char req[9999];
  char ws[9999];
  int rcvd;
  int flag;
  int status_code=-1;
  rcvd=recv(client,req,9999,0);
  cout<<client<<endl;
  if(rcvd>0){
    if(strstr(req,"raw")!=NULL){
      string retval=handle_raw_msg(req);
      send(client,retval.c_str(),sizeof(retval.c_str()),0);
    }else{
      http *p=new http(req);
      map<string,string> data=p->get_data();
      string key=data["Sec-WebSocket-Key"];
      char output[29] = {};
      WebSocketHandshake::generate(key.erase(0,1).c_str(), output);
      string resp="HTTP/1.1 101 Switching Protocols\nUpgrade: websocket\nConnection: Upgrade\nSec-WebSocket-Accept:";
      resp.append(output);
      resp.append("\n\n");
      send(client,resp.c_str(),strlen(resp.c_str()),0);
      string msg="";
      while(1){
        msg=decode(client);
        if(msg.compare("conn_closed")==0)
          break;
        resp=process(msg,client);
        r=encode(resp);
        send(client,r.c_str(),strlen(r.c_str()),0);
        if(strstr(resp.c_str(),"cmd,game_end")!=NULL){
          break;
        }
      }
    }
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
