<!DOCTYPE html>
<html>
<head>
	<title>Cat Feeder</title>    
	<meta http-equiv = "content-Type" content="text/html;charset=utf-8">
	<meta name = "viewport" content = "width=device-width,initial-scale=1">
	<link rel = "stylesheet" type = "text/css" href="CSS/jquery.mobile-1.4.5.min.css">
	<script src = "jquery-1.11.3.min.js"></script>
	<script src = "jquery.mobile-1.4.5.min.js"></script>
	<link href="CSS/style.css" rel="stylesheet">  
	<script src="js/mqttws31.js" type="text/javascript"></script>		
	<script type="text/javascript">
        var clientId = "ws" + Math.random();
					
        // Create a client instance
         client = new Paho.MQTT.Client("m11.cloudmqtt.com", 30277, clientId);

        // set callback handlers
        client.onConnectionLost = onConnectionLost;
        client.onMessageArrived = onMessageArrived;

        // connect the client
        var options = {
          useSSL: true,
          userName: "your username!!",
          password: "your password!!",
          onSuccess:onConnect,
          onFailure:doFail
        };

         // connect the client
        client.connect(options);

        // called when the client connects
        function onConnect() {
            // Once a connection has been made, make a subscription and send a message.
            console.log("onConnect");
           //alert("connected");
            client.subscribe("/BT1");
        }

        function doFail(e){
          console.log(e);
        }

        // called when the client loses its connection
        function onConnectionLost(responseObject) {
         if (responseObject.errorCode !== 0) {
           console.log("onConnectionLost:"+responseObject.errorMessage);
         }
        }

        // called when a message arrives

        function onMessageArrived(message) {           
            var data = "Sharp";
            data = message.payloadString;
            var StatusCat = document.getElementById("StatusCat");		
            StatusCat.innerHTML = data;	
			
			if(data=="eat"){
				$.ajax(
				   {					  
					  url:'Insert_data.php',					  			
				   }
				);
				location.reload();
				
			}
			else{
				data = "Sharp";
			}
			data = "Sharp";
                        location.reload();
                        var delayMillis = 1000; //1 second	
			setTimeout(function() {
		        //your code to be executed after 1 second
		        }, delayMillis);
                        location.reload();			
		}	
		function sendMsg()
		{
			var x = document.getElementById("token_text").value;			
			command = new Paho.MQTT.Message(x);
			command.destinationName = "/TOKEN";
			client.send(command);
			alert("เปลี่ยนปลายทางการแจ้งเตือนสำเร็จ !!");
			location.reload();			
		}
		
		function sendMsg2()
		{			
			command = new Paho.MQTT.Message("GETFOOD");
			command.destinationName = "/TOKEN";
			client.send(command);
			alert("ให้อาหารเจ้าเหมียวแล้ว !!");					
		}
		
    </script>
	<style type="text/css">		
		body {
			background: url(BG_sharp.jpg) no-repeat center center fixed;
			-webkit-background-size: cover;
			-moz-background-size: cover;
			-o-background-size: cover;
			background-size: cover;
		}
		.ui-page 
		{
			background: transparent;
		}
		.ui-content
		{
			background: transparent;
		}
	</style>

	<style>
		img{ max-width:100%; border:none;}
		.pic{ float:center; width:95%; margin:2% 0%;}
	</style>

	<style>
		.dropbtn {
		    background-color: #4CAF50;
		    color: white;
		    padding: 16px;
		    font-size: 16px;
		    border: none;
		    cursor: pointer;
		}

		.dropbtn:hover, .dropbtn:focus {
		    background-color: #3e8e41;
		}

		.dropdown {
		    position: relative;
		    display: inline-block;
		}

		.dropdown-content {
		    display: none;
		    position: absolute;
		    background-color: #f9f9f9;
		    min-width: 160px;
		    overflow: auto;
		    box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
		}

		.dropdown-content a {
		    color: black;
		    padding: 12px 16px;
		    text-decoration: none;
		    display: block;
		}

		.dropdown a:hover {background-color: #99FF99}

		.show {display:block;}
	</style>
	
</head>
<body>			
	<div data-role="page" id="ShowData">
		<div data-role="header" data-theme="b" data-position="fixed">
			<h4>Cat Feeder</h4>
		</div>
				
		<center><P><FONT FACE = "Comic Sans MS" COLOR=#FF0000><b><span id="StatusCat">(´・ω・`) </span>
		</b></FONT></P></center>

                <a href="https://notify-bot.line.me/th/">รับรหัส  Line Token คลิ๊ก</a><br></br>
		
		<label for="token_text"><B>LINE TOKEN :</B></label>
		<input data-clear-btn="true" name="Token" id="token_text" value="" type="text" placeholder="Input your Line token">
		<center><button  class="ui-shadow ui-btn-inline ui-nodisc-icon ui-alt-icon ui-btn ui-corner-all" onclick="sendMsg()" ><FONT Color = Green>  ยืนยันรหัสเพื่อเชื่อมต่อไลน์  </FONT></button></center>
		
			
		<div data-role="content"><br>
			
			<center>
				<?php
					$link = mysql_connect('localhost','your username!!','your password!!')or die("ติดต่อฐานข้อมูลไม่ได้");
	                mysql_select_db('your database!!',$link)or die("ติดต่อฐานข้อมูลไม่ได้");
					$result = mysql_query('SELECT Auto_PK_CAT,TimeText
					FROM cat
					ORDER BY TimeCatFeeding_CAT');
									
					if(!$result){
						die('Invalid query:'. mysql_error());						
					}
					echo "<div style ='font:18px/35px Arial,tahoma,sans-serif;color:#ff0000'> จำนวนครั้งการให้อาหารเจ้าเหมียว คือ   ".mysql_num_rows($result)." ครั้ง<br> </div>";
                                     
				?>
                                      <button  class="ui-shadow ui-btn-inline ui-nodisc-icon ui-alt-icon ui-btn ui-corner-all" onclick="sendMsg2()" ><FONT Color = Green>  กดเพื่อให้อาหารเจ้าเหมียวทันที 1 ครั้ง  </FONT></button>
			</center>
			<table data-role = "table" data-mode = "columntoggle" id="my_table2" class = "ui-body-a ui-shadow ui-responsive table-strip" data-column-btn-text="แสดงคอลัมน์" data-column-popup-theme="a" data-column-btn-theme="b">
				<thead>
					<tr bgcolor = #54FF9F>
						<th data-priority = 1>ครั้งที่</th>
						<th data-priority = 1>เวลาที่เจ้าเหมียวมากินอาหาร</th>
					</tr>
				</thead>
				<tbody>
					<?
						while($row=mysql_fetch_assoc($result)){
							?>
							<tr>
								<td><? echo $row['Auto_PK_CAT'];?></td>
								<td><? echo $row['TimeText'];?></td>
							</tr>
							<?
						}
						mysql_close($link);
					?>
				</tbody>		
			</table>

		<input id = "btnSubmit" type="submit" value="ล้างประวัติ"/>
		
		<script>
			$(document).ready(function(){
				$("#btnSubmit").click(function(){
					$.ajax({url: "truncate.php", success: function(result){
						$("#div1").html(result);
					}});
					location.reload();
					location.reload();
				});
			});
			
		</script>
			
		</div>
		<div data-role="footer" data-theme ="b" data-position="fixed">
			<h4> Cat Feeder by Danuphat Gravitech </h4>
			<div data-role = "navbar">
				<ul>
					<li><a href = "https://gravitechthai.com/" data-icon="search" >Go to the website Gravitech.com</a></li>
				</ul>
			</div>
		</div>
	</div>			
</body>
</html>
