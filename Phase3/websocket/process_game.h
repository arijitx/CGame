
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
  return "status,success";
}

string process(string msg,int sock,string* pname){
  map<string,string> data;
  data=process_msg(msg);
  //update_sock
  if(data["cmd"].compare("update_sock")==0){
    game_array[data["game_id"]]->update_sock_fd(data["player"],sock);
    if(game_array[data["game_id"]]->get_player_by_name(data["player"])==2){
      int s=game_array[data["game_id"]]->get_other_player_sock(data["player"]);
      string m="cmd,update_game_info,msg,other_player_conn,";
      m+=game_array[data["game_id"]]->get_game_info();
      update_other_player(m,s);
    }
    cout<<data["player"]<<"  "<<GRN<<"Connected"<<RESET<<" to Game : "<<data["game_id"]<<endl;
    // game_array[data["game_id"]]->describe();
    string x="status,success,msg,update_sock_success,";
    x+=game_array[data["game_id"]]->get_game_info();
    *pname=data["player"];
    return x;
  }
  //move
  if(data["cmd"].compare("move")==0){
    int p_no=game_array[data["game_id"]]->get_player_by_name(data["player"]);
    int ret=game_array[data["game_id"]]->update_board(stoi(data["x"]),stoi(data["y"]),p_no);
    if(ret==1){
      string m="cmd,oppo_move,board,";
      m+=game_array[data["game_id"]]->get_board();
      m+=",turn,";
      m+=game_array[data["game_id"]]->get_turn()+48;
      update_other_player(m,game_array[data["game_id"]]->get_other_player_sock(data["player"]));
      return "status,success";
    }
    if(ret==2 || ret ==3){
      string m="cmd,game_end,msg,";
      if(ret==3)
        m+="draw_game";
      if(ret==2)
        m+="you_lose";
      update_other_player(m,game_array[data["game_id"]]->get_other_player_sock(data["player"]));
      string x="cmd,game_end,msg,";
      if(ret==3)
        x+="draw_game";
      if(ret==2)
        x+="you_win";
      return x;
    }
    if(ret==-1)
      return "status,err,msg,not your turn";
    if(ret==0)
      return "status,err,msg,invalid move";
  }
  //board
  if(data["cmd"].compare("board")==0){
    string m="cmd,board_status,board,";
    m+=game_array[data["game_id"]]->get_board();
    m+=",turn,";
    m+=game_array[data["game_id"]]->get_turn()+48;
    return m;
  }
  return "status,failure,msg,cmd_not_found";
}
