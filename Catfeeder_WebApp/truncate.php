<?php
							$host="localhost";
							$username="your username!!";
							$pass_word="your password!!";
							$db="your database!!";
							$Conn=mysql_connect($host,$username,$pass_word) or die("ติดต่อฐานข้อมูลไม่ได้");
							mysql_select_db($db) or die("ติดต่อฐานข้อมูลไม่ได้");

							$strSQL ="DELETE FROM cat";
							$strQuery=mysql_db_query($db, $strSQL);
																		
							mysql_close();
														
							$link = mysql_connect('localhost','your username!!','your password!!')or die("ติดต่อฐานข้อมูลไม่ได้");
	                        mysql_select_db('your database!!',$link)or die("ติดต่อฐานข้อมูลไม่ได้");
							$result = mysql_query('ALTER TABLE cat AUTO_INCREMENT = 1');
																			
							mysql_close();
												
?>



