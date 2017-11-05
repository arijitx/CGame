$(document).ready( function () {
  $("#create_game").click(function(){
      var player_name=document.getElementById("player_name").value
      $.get("/create_game?name="+player_name, function(data, status){
        $("#game_id").text(data.game_id);
        setTimeout(function(){
          window.location = "/game_ui" },
          3000);
      });

  });

  $("#join_game").click(function(){
      var player_name=document.getElementById("player_name_joiner").value
      var game_id=document.getElementById("game_id_joiner").value
      //console.log("/connect?game_id="+game_id+"&player="+player_name);
      $.get("/connect?game_id="+game_id+"&player="+player_name, function(data, status){
        if(data.status=="success"){
          setTimeout(function(){
            window.location = "/game_ui" },
            3000);

        }else{
          alert(data.msg);
        }
      });
  });
});
