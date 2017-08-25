$(document).ready( function () {
  setInterval(function() {
    $.get("/board?game_id="+game_id,function(data,status){
      update_board(data.board);
    });
  }, 1000);
  var game_id=read_cookie("game_id");
  $.get("/board?game_id="+game_id,function(data,status){
    update_board(data.board);
  });

  $(".box").click(function(){
      var player_name=read_cookie("player");
      var game_id=read_cookie("game_id");
      var box=$(this).attr('id').substr(3);
      var x=Math.floor((box-1)/3);
      var y=(box%3+2)%3;
      console.log(x+" "+y);
      $.get("/update_board?player="+player_name+"&x="+x+"&y="+y+"&game_id="+game_id, function(data, status){
        if(data.status=="success"){
          $.get("/board?game_id="+game_id,function(data,status){
            update_board(data.board);
          });
        }else{
          alert(data.msg);
        }
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
