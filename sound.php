<?php

$peaks = $_POST['peaks'];
$db_val = $_POST['db_val'];
$today = date("Y-m-d H:i:s");
$record = $today . ", Peaks: " . $peaks . ", Max dB Value: " . $db_val . "\n";

$file = "project.log";	//specify log file name
if(file_exists($file))
	$fp = fopen($file, "a");	//open file in append
else
	$fp = fopen($file, "w");	//else open in write
fwrite($fp, $record);
fclose($fp);
echo "sent from server\n";

?>

