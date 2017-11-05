$(document).ready( function () {
  $.get("/ws_url", function(data, status){
    console.log(data);
    url=data.ws_url;
    var ws = new WebSocket(url);

    var player_name=read_cookie("player");
    var game_id=read_cookie("game_id");
    console.log(game_id);
    $('#player_name').text(player_name);

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
        if(cmd["turn"]=="1"){
          $("#p1_turn").show();
          $("#p2_turn").hide();
        }else{
          $("#p1_turn").hide();
          $("#p2_turn").show();
        }
      }
      if(cmd["cmd"]=="board_status"){
        update_board(cmd["board"].split(" "));
        if(cmd["turn"]=="1"){
          $("#p1_turn").show();
          $("#p2_turn").hide();
        }else{
          $("#p1_turn").hide();
          $("#p2_turn").show();
        }
      }
      if(cmd["cmd"]=="game_end"){
        ws.close();
        alert(cmd["msg"]);

        window.location = "/"
      }
      if(cmd["status"]=="success"){
        if(cmd["msg"]=="update_sock_success"){
          if(cmd["p1"]!=""){
            $('#p1').text(cmd["p1"]);
          }
          if(cmd["p2"]!=""){
            $('#p2').text(cmd["p2"]);
          }
        }
      }
      if(cmd["cmd"]=="update_game_info"){
        if(cmd["p2"]!=""){
          $('#p2').text(cmd["p2"]);
        }
      }
      if(cmd["status"]=="err"){
        alert(cmd.msg);
      }
      if(cmd["cmd"]=="success" && cmd["msg"]=="update_sock_success"){

      }
    };
    $(".box").click(function(){
        var player_name=read_cookie("player");
        var game_id=read_cookie("game_id");
        var box=$(this).attr('id').substr(3);
        var x=Math.floor((box-1)/3);
        var y=(box%3+2)%3;
        var m="cmd,move,game_id,"+game_id+",player,"+player_name+",x,"+x+",y,"+y;
        ws.send(m);
        m="cmd,board,game_id,"+game_id;
        ws.send(m);
    });
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
