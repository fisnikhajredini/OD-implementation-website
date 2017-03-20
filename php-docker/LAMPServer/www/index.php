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

?>
<html><body><table style=width:100%>
<tr><th>UDP</th>
<th>TCP</th></tr>
<?php
for($n=0;$n<3;$n++){
    $udpData = stream_socket_recvfrom($udpsock, 512, 0, $peer);
    $tcpData = fread($connection,512);
    echo "Here comes the ord: ";
    $tcpLen=strlen($tcpData);

    echo dechex(ord($tcpData[0]))." and ".dechex(ord($tcpData[0]));
    $UDP[]=$udpData; 
    $TCP[]=$tcpData;
    echo "<tr><td>  $UDP[$n] </td>";
    echo "<td>Message ".($n +1 )." :$TCP[$n] </td></tr>";
    // for($x=0;$x<2;$x++){
    //     echo ord($UDP[$n[$x]])
    // }
}
echo "</table></html></body>";
fclose($connection);
fclose($tcpsock);
fclose($udpsock);  
?>