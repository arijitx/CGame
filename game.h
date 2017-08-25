#include<bits/stdc++.h>
#include<string>

using namespace std;

class game{
  private:
    string game_id;
    string player_1;
    int player_1_sock_fd;
    string player_2;
    int player_2_sock_fd;
    bool ready;
    int turn;
    int board[3][3];

  public:
    game(string gid,string p1){
      this->game_id=gid;
      this->player_1=p1;
      this->ready=false;
      this->turn=1;
      for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
          this->board[i][j]=0;
    }

    void update_sock_fd(string player,int fd){
      if(player.compare(this->player_1)){
        this->player_1_sock_fd=fd;
      }else{
        this->player_2_sock_fd=fd;
      }

    }

    void update_player_2(string p2){
      this->player_2=p2;
      this->ready=true;
    }
    int update_board(int x,int y,int move){
      if(move!=this->turn)
        return -1;
      if(this->board[x][y]==0){
        this->board[x][y]=move;
        if(turn==1)
          turn=2;
        else
          turn=1;
        return 1;
      }else{
        //invalid move
        return 0;
      }
    }
    string num2str(int x){
      stringstream ss;
      string str;
      ss << x;
      str = ss.str();
      return str;
    }
    string get_board(){
      string boardstr="[";
      for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
          boardstr.append(num2str(this->board[i][j]));
          if(i!=2 || j!=2)
            boardstr.append(",");
        }
      }
      boardstr.append("]");
      return boardstr;
    }

    string get_game_id(){
      return this->game_id;
    }

    int get_turn(){
      return this->turn;
    }

    int get_player_by_name(string p){
      if(!p.compare(this->player_1))
        return 1;
      if(!p.compare(this->player_2))
        return 2;
      return 0;
    }

    string get_player(int x){
      if(x==1)
        return player_1;
      else
        return player_2;
    }

};
