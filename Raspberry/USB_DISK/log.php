<?php 

$time_start = microtime(true); 

$data = date ("Y-m-d H:i:s");
$linia ="";

//Odczyt
$linia =(int)rtrim(file_get_contents("http://192.168.1.101/state?out=1"));			// Przed�u�acz g�ra wy 1
$linia =$linia.";".(int)rtrim(file_get_contents("http://192.168.1.101/state?out=2"));		// Przed�u�acz g�ra wy 2

$linia =$linia.";".(float)rtrim(file_get_contents("http://192.168.1.103/state?in=A"));		// Salonik g�ra czujnik temp
$linia =$linia.";".(float)rtrim(file_get_contents("http://192.168.1.102/state?in=A"));		// Salon czyjnik temp

//$linia =$linia.";".(int)rtrim(file_get_contents("http://192.168.1.101/state?out=1"));		// # Przed�u�acz wy 1
//$linia =$linia.";".(int)rtrim(file_get_contents("http://192.168.1.101/state?out=2"));		// # Przed�u�acz wy 2
//$linia =$linia.";".(int)rtrim(file_get_contents("http://192.168.1.100/state?in=2"));		// # 8 Moduł 100 DO 1
//Zapis

//file_get_contents("http://192.168.1.100/toggle?out1=1");				//Moduł 100 DO 1
//file_get_contents("http://192.168.1.100/toggle?out2=1");				//Moduł 100 DO 2

$execution_time = (microtime(true) - $time_start);
$linia=$data.";".$execution_time.";".$linia;

file_put_contents("USB_DISK/".date ("Y-m-d").".txt", $linia."\n", FILE_APPEND);

print $linia;

?>
