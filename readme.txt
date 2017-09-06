Set Conifguration
=================
change PORT_WEB , PORT_WS and WS_URL in common/config.h
default:
PORT_WEB  8080
PORT_WS 8001
WS_URL "ws://10.15.28.171:8001"

WS_URL should be in the form :
ws://<IPV4 of SERVER>:<PORT_WS>

Instruction to Run
==================

Compile both Websockt Server and Web Server

g++ webserver.c -std=c11 -pthread -o web_server.o
g++ ws_server.c -std=c11 -pthread -o ws_server.o

Run Compiled Binaries

./web_server.o
./ws_server.o

Instruction to Test
===================

The Server sets cookie so , to test multiple occourance , must use one tab
from normal mode and one from incognito mode .
