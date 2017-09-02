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
    int move_count=0;
    int winner=0;

  public:
    game(string gid,string p1){
      this->game_id=gid;
      this->player_1=p1;
      this->player_2="";
      this->player_2_sock_fd=-1;
      this->player_1_sock_fd=-1;
      this->ready=false;
      this->turn=1;
      for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
          this->board[i][j]=0;
    }
    void display_game(){
      cout<<"------------------Game Info---------------------"<<endl;
      cout<<GRN<<"Game Id : "<<this->game_id<<RESET<<endl;
      cout<<YEL<<"Player 1 : "<<this->player_1<<"\tPlayer 2 : "<<this->player_2<<endl;
      if(this->winner==0){
        cout<<RED<<"DRAW GAME"<<RESET<<endl;
      }else if(this->winner ==1){
        cout<<RED<<"winner : "<<this->player_1<<RESET<<endl;
      }else{
        cout<<RED<<"Winner : "<<this->player_2<<RESET<<endl;
      }
      cout<<"-------------------------------------------------"<<endl;
    }
    bool valid(int x,int y)
    {
       if(x>=0 && y>=0 && x<=2 && y<=2)
       return 1;
       return 0;
    }
    int  is_win(int x,int y,int mark){
      int res=0;
      for(int x=0;x<=2;x++)
      {
          for(int y=0;y<=2;y++)
          {
            if(this->board[x][y]==mark)
            {
            int win=0;
		         if(valid(x-1,y+1) && valid(x-2,y+2) && this->board[x-1][y+1]==mark && this->board[x-2][y+2]==mark)
		            win=1;
		          if(valid(x-1,y) && valid(x-2,y) && this->board[x-1][y]==mark && this->board[x-2][y]==mark)
		         win=1;
		         if(valid(x-1,y-1) && valid(x-2,y-2) && this->board[x-1][y-1]==mark && this->board[x-2][y-2]==mark)
		          win=1;
		        if(valid(x,y-1) && valid(x,y-2) && this->board[x][y-1]==mark && this->board[x][y-2]==mark)
		        win=1;
		  if(valid(x+1,y-1) && valid(x+2,y-2) && this->board[x+1][y-1]==mark && this->board[x+2][y-2]==mark)
		  win=1;
		  if(valid(x+1,y) && valid(x+2,y) && this->board[x+1][y]==mark && this->board[x+2][y]==mark)
		  win=1;
		  if(valid(x+1,y+1) && valid(x+2,y+2) && this->board[x+1][y+1]==mark && this->board[x+2][y+2]==mark)
		  win=1;
		     if(valid(x,y+1) && valid(x,y+2) && this->board[x][y+1]==mark && this->board[x][y+2]==mark)
		  win=1;
      res=res|win;
    }
       }
  }
		  return res;
    }

    void update_sock_fd(string player,int fd){
      if(player.compare(this->player_1)==0){
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
        this->move_count++;
        if(this->move_count==9){
          if(is_win(x,y,move)){
            //turns max , winner
            this->winner=turn;
            display_game();
            return 2;
          }else{
            //turns max , draw game
            return 3;
          }
        }
        if(is_win(x,y,move)){
          //game win turns remaining
          this->winner=turn;
          display_game();
          return 2;
        }

        if(turn==1)
          turn=2;
        else
          turn=1;

        return 1;

      }else{
        return 0;
      }

    }

    void describe(){
      cout<<"Game id-> "<<this->game_id<<" p1-> "<<this->player_1<<" p2-> "<<this->player_2<<endl;
      cout<<"Sock_fd_1-> "<<this->player_1_sock_fd<<"Sock_fd_2-> "<<this->player_2_sock_fd<<endl;
    }

    string num2str(int x){
      stringstream ss;
      string str;
      ss << x;
      str = ss.str();
      return str;
    }

    string get_board(){
      string boardstr="";
      for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
          boardstr.append(num2str(this->board[i][j]));
          if(i!=2 || j!=2)
            boardstr.append(" ");
        }
      }
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

    int get_other_player_sock(string p){
      if(p.compare(this->player_1)==0)
        return this->player_2_sock_fd;
      else
        return this->player_1_sock_fd;
    }

    string get_game_info(){
      string m="p1,";
      m+=this->player_1;
      m+=",p2,";
      m+=this->player_2;
      return m;
    }
    string get_player(int x){
      if(x==1)
        return player_1;
      else
        return player_2;
    }

};
