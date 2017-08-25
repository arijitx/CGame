
map<string,game*> game_array;
typedef std::pair<std::string, game*> game_pair;

void update_other_player(string m,int sock){
  string x=encode(m);
  send(sock,x.c_str(),strlen(x.c_str()),0);
}

map<string,string> process_msg(string msg){
  map<string,string> data;
  //constant char * to char * [ need to be fixed ]
  char* key=strtok((char *)msg.c_str(),",");
  while(key!=NULL){
    data[key]=strtok(NULL,",");
    key=strtok(NULL,",");
  }
  return data;
}

string handle_raw_msg(char * req){
  string m=strtok(req,",");
  string gid=strtok(NULL,",");
  string p_id=strtok(NULL,",");
  if(game_array.find(gid)!=game_array.end()){
    game_array[gid]->update_player_2(p_id);
  }else{
    game* g=new game(gid,p_id);
    game_array.insert(game_pair(gid,g));
  }
  return "success";
}

string process(string msg,int sock){
  map<string,string> data;
  data=process_msg(msg);
  //update_sock
  if(data["cmd"].compare("update_sock")==0){
    game_array[data["game_id"]]->update_sock_fd(data["player"],sock);
    game_array[data["game_id"]]->describe();
    return "update sock success";
  }
  //move
  if(data["cmd"].compare("move")==0){
    int p_no=game_array[data["game_id"]]->get_player_by_name(data["player"]);
    int ret=game_array[data["game_id"]]->update_board(stoi(data["x"]),stoi(data["y"]),p_no);
    if(ret==1){
      string m="cmd,oppo_move,board,";
      m+=game_array[data["game_id"]]->get_board();
      update_other_player(m,game_array[data["game_id"]]->get_other_player_sock(data["player"]));
      return "success";
    }
    if(ret==-1)
      return "not your turn";
    if(ret==0)
      return "invalid move";
  }
  //board
  if(data["cmd"].compare("board")==0){
    string m="cmd,board_status,board,";
    m+=game_array[data["game_id"]]->get_board();
    return m;
  }
  return "status,failure,msg,cmd_not_found";
}
