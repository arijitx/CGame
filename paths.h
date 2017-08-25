#define PARAMS map<string,string> header,map<string,string> data
#include<stdio.h>

#include <string>
#include <fstream>
#include <streambuf>

#include<bits/stdc++.h>

using namespace std;

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
  game* g=new game(game_id,player);
  game_array.insert(game_pair(game_id,g));
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
  return resp;
}

//get_game board
string path_board(PARAMS){
  string game_id=data["game_id"];
  string resp="";
  if(game_array.find(game_id) != game_array.end()){
    game* g=game_array[game_id];
    resp.append("Content-Type: application/json\n\n");
    resp.append("{\"status\":\"success\",\"board\":");
    resp.append(g->get_board());
    resp.append("}");
  }
  else{
    resp.append("Content-Type: application/json\n\n");
    resp.append("{\"status\":\"fail\",\"msg\":\"no game exits\"");
  }
  return resp;
}

//update_board
string path_update_board(PARAMS){
  string game_id=data["game_id"];
  string player=data["player"];
  string x=data["x"];
  string y=data["y"];
  game* g=game_array[game_id];
  string resp="Content-Type: application/json\n\n";
  int xi=atoi(x.c_str());
  int yi=atoi(y.c_str());
  int playeri=g->get_player_by_name(player);
  int retval=g->update_board(xi,yi,playeri);
  if(retval==1){
    resp.append("{\"status\":\"success\"}");
  }
  if(retval==-1){
    resp.append("{\"status\":\"fail\",\"msg\":\"not your turn\"}");
  }
  if(retval==0){
    resp.append("{\"status\":\"fail\",\"msg\":\"place already occupied\"}");
  }
  return resp;
}

//connect player_2
string path_connect(PARAMS){
  string game_id=data["game_id"];
  string player=data["player"];
  game *g=game_array[game_id];
  g->update_player_2(player);
  string resp="";
  resp.append("Set-Cookie: game_id=");
  resp.append(game_id);
  resp.append("\nSet-Cookie: player=");
  resp.append(player);
  resp.append("\nSet-Cookie: player_no=");
  resp.append("2");
  resp.append("\n");
  resp.append("Content-Type: application/json\n\n");
  resp.append("{\"status\":\"success\"}");
  return resp;
}

//main path function
string process_req(string path,map<string,string> header,map<string,string> data){
  if(!path.compare("/")){
    return static_html("index.html");
  }
  if(!path.compare("/create_game")){
    return path_create_game(header, data);
  }
  if(path.find("/static/")!=string::npos){
    return static_file(path);
  }
  if(!path.compare("/board")){
    return path_board(header, data);
  }
  if(!path.compare("/update_board")){
    return path_update_board(header,data);
  }
  if(!path.compare("/connect")){
    return path_connect(header,data);
  }
  if(!path.compare("/game_ui")){
    return static_html("game_ui.html");
  }
  return static_html("404.html");
}
