<?php
//=========================================//
// THE SETUP
if (false ===($tcpsock = stream_socket_server("tcp://127.0.0.1:8876",$errorno,$errstr)))
	echo"tcp socket failed : $errstr($errorno)\n";

if(false ===($connection = stream_socket_accept($tcpsock))) 
	echo "tcp accept failed!\n";

if (false ===($udpsock = stream_socket_server("udp://127.0.0.1:8876",$errorno,$errstr,STREAM_SERVER_BIND)))
	echo"$errstr($errorno)\n";



//=================================//
//messages

$UDP=array();
$TCP=array();

echo "<html><body><table style=width:100%>";
echo "<tr><th>UDP</th>";
echo "<th>TCP</th></tr>";
for($n=0;$n<3;$n++){
	$adder=1;
	$udpData = stream_socket_recvfrom($udpsock, 512, 0, $peer);
	$tcpData = fread($connection,512);
	$UDP[]=$udpData;
	$TCP[]=$tcpData;
	$adder = $n+ $adder;
	echo "<tr><td>  $UDP[$n] </td>";
	echo "<td>Message $adder :$TCP[$n] </td></tr>";
}
echo "</table></html></body>";
fclose($connection);
fclose($tcpsock);
fclose($udpsock);  
?>