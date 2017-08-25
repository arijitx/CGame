
map<string,game*> game_array;
typedef std::pair<std::string, game*> game_pair;

map<string,string> process_msg(string msg){
  map<string,string> data;
  //constant char * to char * [ need to be fixed ]
  string key=strtok((char *)msg.c_str(),",");
  while(key.c_str()!=NULL){
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

string process(string msg){
  map<string,string> data;
  data=process_msg(msg);
  return "succes";
}

game join_game(string game_id){

}
