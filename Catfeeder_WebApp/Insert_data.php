<?php
	$link = mysql_connect('localhost','your username!!','your password!!')or die("ติดต่อฐานข้อมูลไม่ได้");
	mysql_select_db('your database!!',$link)or die("ติดต่อฐานข้อมูลไม่ได้");
    date_default_timezone_set('Asia/Bangkok');
    $date_cat = date('\วันที่ d/m/Y \เวลา H:i:s');
    $name= "ฟ้า"; 
    $query = "INSERT INTO cat (name_CAT,TimeText) VALUES ('$name','$date_cat')";
    mysql_query($query);
	mysql_close();			
?>