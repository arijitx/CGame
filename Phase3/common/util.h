#include<stdio.h>
#include<bits/stdc++.h>

#include "config.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

using namespace std;
void print_header(int version){
  printf(GRN "\n _______  _______  _______  ______    __   __  _______  ______   \n|       ||       ||       ||    _ |  |  | |  ||       ||    _ |  \n|       ||  _____||    ___||   | ||  |  |_|  ||    ___||   | ||  \n|       || |_____ |   |___ |   |_||_ |       ||   |___ |   |_||_ \n|      _||_____  ||    ___||    __  ||       ||    ___||    __  |\n|     |_  _____| ||   |___ |   |  | | |     | |   |___ |   |  | |\n|_______||_______||_______||___|  |_|  |___|  |_______||___|  |_|\n" RESET);
  printf(BLU "\n\n\t Welcome to CServer\n\t A Webserver Completely Built on C \n\t Version : %d\n\n" RESET,version);
}

void print_config(){
  printf(YEL"\n\t Config Current :\n\n" RESET);
  printf("\n\t PORT WebServer        \t : %d",PORT_WEB);
  printf("\n\t PORT WebSocket Server \t : %d",PORT_WS);
  printf("\n\t WebSocket Url         \t : %s",WS_URL);
  printf("\n\t Max Connections       \t : %d",CONMAX);
  // #printf("\n\t WebServer Directory  \t : " ROOT);
  printf("\n\n");
}

double string_to_float(string str)
{
  istringstream buffer(str);
  double temp;
  buffer >> temp;
  return temp;
}
