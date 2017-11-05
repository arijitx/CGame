#define PARAMS map<string,string> header,map<string,string> data
#include<stdio.h>
#include <string>
#include <fstream>
#include <streambuf>

#include<bits/stdc++.h>

#include "server_comm.h"

using namespace std;

set<string> game_ids;

//static file fast
string static_fast(string path){
  if(!path.compare("index.html")){
    return "\n"+string(static_files["static/html/index.html"]);
  }
}
//send static html files
string static_html(string path){
  string html_dir="static/html/";
  ifstream ifs ((html_dir+path).c_str());
  string s;
  getline (ifs, s, (char) ifs.eof());
  string new_line="\n";
  return new_line+s;
}

//send static_file
string static_file(string path){
  ifstream ifs ((path).erase(0,1).c_str());
  string s;
  getline (ifs, s, (char) ifs.eof());
  string new_line="\n";
  return new_line+s;
}

//create_game ops get playername and create a game return game ID
string path_create_game(PARAMS){
  string name=data["name"];
  string resp="";
  if(name==""){
    resp.append("Content-Type: application/json\n\n");
    resp.append("{\"status\":\"error\",\"msg\":\"no name params\"}");
    return resp;
  }
  string player=name;
  string game_id=name.append("xxx2");
  resp.append("Set-Cookie: game_id=");
  resp.append(game_id);
  resp.append("\nSet-Cookie: player=");
  resp.append(player);
  resp.append("\nSet-Cookie: player_no=");
  resp.append("1");
  resp.append("\n");
  resp.append("Content-Type: application/json\n\n");
  resp.append("{\"status\":\"success\",\"game_id\":\"");
  resp.append(name);
  resp.append("\"}");
  string m="raw,";
  m+=game_id;
  m+=",";
  m+=player;
  send_msg(m);
  game_ids.insert(game_id);
  return resp;
}


//connect player_2
string path_connect(PARAMS){
  string game_id=data["game_id"];
  string player=data["player"];
  string resp="";
  resp.append("Set-Cookie: game_id=");
  resp.append(game_id);
  resp.append("\nSet-Cookie: player=");
  resp.append(player);
  resp.append("\nSet-Cookie: player_no=");
  resp.append("2");
  resp.append("\n");
  resp.append("Content-Type: application/json\n\n");
  if(game_ids.find(game_id)!=game_ids.end()){
    resp.append("{\"status\":\"success\"}");
    string m="raw,";
    m+=game_id;
    m+=",";
    m+=player;
    send_msg(m);
  }else{
    resp+="{\"status\":\"fail\",\"msg\":\"no_game_found\"}";
  }
  return resp;
}

string path_ws_url(PARAMS){
  string resp="Content-Type: application/json\n\n{\"ws_url\":\"";
  resp.append(WS_URL);
  resp.append("\"}");
  return resp;
}

//main path function
string process_req(string path,map<string,string> header,map<string,string> data){
  if(!path.compare("/")){
    return static_fast("index.html");
  }
  if(!path.compare("/create_game")){
    return path_create_game(header, data);
  }
  if(path.find("/static/")!=string::npos){
    return static_file(path);
  }
  if(!path.compare("/connect")){
    return path_connect(header,data);
  }
  if(!path.compare("/game_ui")){
    return static_html("game_ui.html");
  }
  if(!path.compare("/ws_url")){
    return path_ws_url(header,data);
  }
  return static_html("404.html");
}
