<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
	<meta http-equiv="content-type" content="text/html; charset=utf-8"/>
	<title></title>
	<meta name="generator" content="LibreOffice 5.3.1.2 (Linux)"/>
	<meta name="created" content="2017-09-03T12:36:14.655513939"/>
	<meta name="changed" content="2017-09-03T15:33:48.085329022"/>
	<style type="text/css">
		@page { margin: 2cm }
		p { margin-bottom: 0.25cm; line-height: 120% }
		a:link { so-language: zxx }
	</style>
</head>
<body lang="en-IN" dir="ltr">
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="7" style="font-size: 32pt">PROJECT
REPORT</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="7" style="font-size: 36pt">Tic
Tac Toe </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 22pt">Powered
by </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 22pt">C
Web Server</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 22pt">Web
Socket Server </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 22pt">HTML
Javascript Client</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">ARIJIT
MUKHERJEE</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">17305T002</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">HIMADRI
SHEKHAR BANDOPADHYA</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">173050004</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 26pt">CS
744 Course Project</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 26pt">Brief
Overview</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">Here
we built a simple realtime Multiplayer Tic Tac Toe game using C , C++
in the server side and HTML Javascript on the Clinet Side . A
Webserver in C is used to Serve the html , Javascript and CSS pages .
Multi threaded architecure is followed in the WebServer using the
Pthread Library in C . The Webserver is built from scratch using UNIX
Sockets which follow the HTTP 1.0 protocol . The realtime Game
between multiple players is achived using the modern websocket
protocol . We built a Websocket Server from scratch . The Client uses
Javascript and Jquery to communicate witht the webserver and
Websocket to communcate with the web socket server . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">The
game works in the following way,</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">	-
Player 1 creates a game genrates a game id</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">	-
Player 2 joins the game using the game id genreated by the player 1</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">	-
then both connect to the websocket server with game id and their
	username</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">	-
then the game is played over the websocket server</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">	-
when the game is ended the result is issued to all the clinets and
they are 	disconnected from the websocket server .</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 26pt">Application
Workflow</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="readme.MD_html_81dc3481fe67bf98.png" name="Image1" align="left" width="643" height="831" border="0"/>
<br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="5" style="font-size: 18pt">Running
Web Server and Web Socket Server</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="readme.MD_html_650f416f83953709.png" name="Image3" align="left" width="532" height="364" border="0"/>
<font face="Ubuntu Condensed"><font size="6" style="font-size: 26pt">		<font size="4" style="font-size: 16pt">Starting
Web Server from terminal</font></font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="readme.MD_html_e7e5f4fd8485c3cf.png" name="Image2" align="left" width="531" height="361" border="0"/>
<br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 26pt">		<font size="4" style="font-size: 16pt">Starting
Web Socket Server from terminal</font></font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="5" style="font-size: 20pt">Client
Side</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="readme.MD_html_69637b0a226a636d.png" name="Image4" align="left" width="589" height="325" border="0"/>
<font face="Ubuntu Condensed"><font size="5" style="font-size: 18pt">	</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="5" style="font-size: 18pt"><font size="4" style="font-size: 14pt">	Client
Side Home Page</font></font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="5" style="font-size: 18pt"><font size="4" style="font-size: 14pt">	</font></font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="readme.MD_html_665cdca87efa3ce9.png" name="Image5" align="left" width="591" height="324" border="0"/>
<font face="Ubuntu Condensed"><font size="5" style="font-size: 18pt"><font size="4" style="font-size: 14pt">	</font></font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="5" style="font-size: 18pt"><font size="4" style="font-size: 14pt">	</font></font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="5" style="font-size: 18pt"><font size="4" style="font-size: 14pt">	Player
1 Creates Game and Gets Game Id</font></font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="readme.MD_html_e0bfa5d368c93be5.png" name="Image6" align="left" width="623" height="346" border="0"/>
<br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="5" style="font-size: 18pt"><font size="4" style="font-size: 14pt">	Player
1 Waiting while player to connecting to game with game id and
username</font></font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="readme.MD_html_5c9fef0cbfceafdc.png" name="Image7" align="left" width="643" height="354" border="0"/>
<font face="Ubuntu Condensed"><font size="5" style="font-size: 18pt"><font size="4" style="font-size: 14pt">	</font></font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="5" style="font-size: 18pt"><font size="4" style="font-size: 14pt">	Both
Player Joins and Starts Playing the Game </font></font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="readme.MD_html_1cc48a81d0f5466c.png" name="Image8" align="left" width="643" height="354" border="0"/>
<br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="5" style="font-size: 18pt"><font size="4" style="font-size: 14pt">	Game
is ended when either one of them wins or out of move .</font></font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="readme.MD_html_46e97950306bdbb8.png" name="Image9" align="left" width="643" height="366" border="0"/>
<br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="5" style="font-size: 18pt"><font size="4" style="font-size: 14pt">The
Log of Game and HTTP requests Served displayed on the terminal</font></font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 26pt">Architecture</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="readme.MD_html_6c5438b0074f29ba.png" name="Image10" align="left" width="643" height="601" border="0"/>
<img src="readme.MD_html_ad6150a73132ae79.png" name="Image11" align="left" width="348" height="114" border="0"/>
<font face="Ubuntu Condensed"><font size="6" style="font-size: 26pt"><font size="5" style="font-size: 18pt">The
Static Folder Contains the HTML , CSS and Javascript Files which are
served on request by the web server</font></font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 26pt">How
it Works</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 26pt">Webserver
</font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">The
webserver creates a socket and binds it to a given port , now when
from browser we send a http request the server returns either HTML
file or JSON response , to efficiently handle a http request the
server first reads the HTTP request from the client , then the HTTP
module decodes the raw request and fetches the REQ_TYPE , REQ_URL ,
REQ_HEADER and REQ_DATA inside a HTTP object . When the request url
is fetched the PATH module maps function for each url like any modern
webserver . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="readme.MD_html_b173e3746337e3e0.png" name="Image12" align="left" width="630" height="445" border="0"/>
<br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">Http
Requests are served independently of each other , each connection is
treated as an individual connection , Sessions are implemented using
cookies , but HTTP protocol is non persistant . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">Now
each function takes the header and data and processes the request and
returns a string as response , which is then sent back the client ,
the reponse can be a HTML file or a JSON message . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">HTTP
module process the raw HTTP request and separates header and data ,
both header and Data are stored in a C++ STL map . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">The
server serves index.html when the endpoint is / .</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">The
server serves files in the /static end point which includes html ,
css and Javscript files . If the endpoint is not given it serves the
404.html .</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">The
/ws_url serves the url of the websocket server as a json object .</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">Now
to create a Game the player 1 sends request with Player name to the
/create_game end point and the server returns the game id to user as
json encoded message .</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">Now
to join a Game the player 2 sends request with Player name and Game
Id to the endpoint /connect , if the game id exists the player is
sent a status with success as a json encoded message.</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">Now
upon receiving this /create_game  request the Webserver sends a
message to the Websocket server to create game for player 1 with a
given game id and for /connect request the web server sends a request
to the websocket server to add player 2 with given player name to
game with given game id . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 26pt">How
it Works</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 26pt">Web
Socket Server</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">The
Web Socket Protocol allows the server and the client to have a
persistent connection and binds an UNIX socket to a Javascript
WebSocket , building a dedicated connection between the client and
server , thus ensures a realtime communcation without burdening the
server with polling from the client . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">Intially
the Websocket connection starts in a HTTP protocol , a Web Socket
Secret Key is sent to the server and Server process the key ,
Initially the key is concatinated with a Magic Key , and SHA1 hash of
the concatinated string is genrated , then the SHA1 hash is base64
enocoded and sent to the client . If the process is done properly a
connection is established between the server and the client and the
websocket handshake is complement , we used <a href="https://github.com/alexhultman/libwshandshake">this</a>
to perform the websocket handshake . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">After
the Handshake is complement still the client sends data encoded in a
frame and masked using specific masking key , and the server should
also decode the data in such frames so that the client can read . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">We
implemented our own Websocket server and encode decode using this
<a href="https://developer.mozilla.org/en-US/docs/Web/API/WebSockets_API/Writing_WebSocket_servers">documentation</a>
. </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">Now
when the websocket server received message to create a game from the
webserver the websocket server creates a game object with given game
id and given player 1 name , and puts it in a map with game id as key
.</font></font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">Now
the object has lot of functions which allows to manipulate and update
moves in the game . The game object saves the game state and
implements additional functions for the game . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">Module
WS Util implements the encode and decode operations for Websocket
frame . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">LibWSHandhake
implements the handshake for WebSocket . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">Upon
recieving instructions from the client the Process_game module
updates the game object or the game state accordingly and sends both
client the updated Game state . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="4" style="font-size: 16pt">When
the Game ends either with an winner or a draw the end event is passed
to the both connected clients and both of them are disconnected from
the server . </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Ubuntu Condensed"><font size="6" style="font-size: 22pt">In
simple , the webserver serves the html , js and css contents and
creates and adds player to an game , and the web socket server
facilitates the real time game. </font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
</body>
</html>