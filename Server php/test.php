<?php
error_reporting(~E_WARNING);

if(!($sock=socket_create(AF_INET, SOCK_DGRAM, 0)))
{
	$errorcode = socket_last_error();
	$errormsg = socket_strerror($errorcode);

	die("Couldnt create socket: [$errorcode] $errormsg \n");
}
echo "socket create OK";
if (!socket_bind($sock,"localhost",8879))
{
	$errorcode = socket_last_error();
	$errormsg = socket_strerror($errorcode);

	die("Couldnt bind socket: [$errorcode] $errormsg \n");
}
echo "socket bind OK";

// while(1)
// {
$remote_ip ='';
$remote_port=0;
	echo "waiting for data ... \n";
 	$r=socket_recvfrom($sock, $buf, 512 , 0 , $remote_ip , $remote_port);
 	echo "$remote_ip : $remote_port --". $buf;
// }

// socket_close($sock);
?>