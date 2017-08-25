$(document).ready( function () {
  var ws = new WebSocket("ws://localhost:8001");

  var player_name=read_cookie("player");
  var game_id=read_cookie("game_id");

  ws.onopen=function(){
    var m="cmd,update_sock,game_id,"+game_id+",player,"+player_name;
    ws.send(m);
    m="cmd,board,game_id,"+game_id;
    ws.send(m);
  };


  ws.onmessage = function (evt)
  {
    var msg=evt.data;
    var cmd={};
    var ar=msg.split(',');
    for(var i=0;i<ar.length;i++){
      cmd[ar[i]]=ar[i+1];
      i++;
    }
    console.log(cmd);
    if(cmd["cmd"]=="oppo_move"){
      update_board(cmd["board"].split(" "));
    }
    if(cmd["cmd"]=="board_status"){
      update_board(cmd["board"].split(" "));
    }
  };

  $(".box").click(function(){

      var box=$(this).attr('id').substr(3);
      var x=Math.floor((box-1)/3);
      var y=(box%3+2)%3;
      var m="cmd,move,game_id,"+game_id+",player,"+player_name+",x,"+x+",y,"+y;
      ws.send(m);
      m="cmd,board,game_id,"+game_id;
      ws.send(m);
  });
});
function update_board(board){

  for(var i=1;i<=9;i++){
    var box=document.getElementById("box"+i)
    var sign="_";
    if (board[i-1]==1)
      sign="X";
    if(board[i-1]==2) {
      sign="O"
    }
    box.innerHTML=sign;
  }
}

//https://stackoverflow.com/a/10730417
function read_cookie(name) {
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++) {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1,c.length);
        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
    }
    return null;
}
