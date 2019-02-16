<!DOCTYPE HTML>
<html>
<head>
<title>ESP8266</title>
<meta http-equiv="Cache-Control" content="no-cache, no-store, must-revalidate" />
<meta http-equiv="Pragma" content="no-cache" />
<meta http-equiv="Expires" content="-1" />

</head>
<body>

<form action="wykres.php">
<center>
<table>
<tr>
	<td>
		Max: 
	</td>
	<td>
		<input type="number" min="-50" max="100" name="max" value="<?php echo (isset($_GET['max']) && !empty($_GET['max']) ) ? $_GET['max'] : 22;?>">
	</td>	
	<td>
		Min: 
	</td>
	<td>
		<input type="number" min="-50" max="100" name="min" value="<?php echo (isset($_GET['min']) && !empty($_GET['min']) ) ? $_GET['min'] : 13;?>">
	</td>
	<td>
		Kolumna: 
	</td>
	<td>
		<input type="number" min="1" max="100" name="kolumna" value="<?php echo (isset($_GET['kolumna']) && !empty($_GET['kolumna']) ) ? $_GET['kolumna'] : 2;?>">
	</td>
	<td>
		Ilość Dni: 
	</td>
	<td>
		<input type="number" min="1" max="10" name="ildni" value="<?php echo (isset($_GET['ildni']) && !empty($_GET['ildni']) ) ? $_GET['ildni'] : 1;?>">
	</td>
<tr>
</tr>
	<td>
		Rok:
	</td>
	<td>  
		<input type="number" min="2017" max="2050" name="rok" value="<?php echo (isset($_GET['rok']) && !empty($_GET['rok']) ) ? $_GET['rok'] : date("Y");?>">
	</td>
	<td>
	Miesiąc: 
	</td>
	<td>
		<input type="number" min="01" max="12" name="miesiac" value="<?php echo (isset($_GET['miesiac']) && !empty($_GET['miesiac']) ) ? $_GET['miesiac'] : date("m");?>">
	</td>
	<td>
	Dzień: 
	</td>
	<td>
		<input type="number" min="01" max="31" name="dzien" value="<?php echo(isset($_GET['dzien']) && !empty($_GET['dzien']) ) ? $_GET['dzien'] : date("d");?>">
	</td>
	<td>
	</td>
	<td>
		<input type="submit" value="Wyślij">
	</td>
</tr>
</table>
</center>
</form>

<?php
$min = (isset($_GET['min']) ) ? $_GET['min'] : 13; //&& !empty($_GET['min']
$max = (isset($_GET['max']) && !empty($_GET['max']) ) ? $_GET['max'] : 22;
$kolumna = (isset($_GET['kolumna']) && !empty($_GET['kolumna']) ) ? $_GET['kolumna'] : 2;
$ildni = (isset($_GET['ildni']) && !empty($_GET['ildni']) ) ? $_GET['ildni'] : 1;
$rok = (isset($_GET['rok']) && !empty($_GET['rok']) ) ? $_GET['rok'] : date("Y");
$miesiac = (isset($_GET['miesiac']) && !empty($_GET['miesiac']) ) ? $_GET['miesiac'] : date("m");
if(strlen($miesiac)==1)
	$miesiac="0".$miesiac;
$dzien = (isset($_GET['dzien']) && !empty($_GET['dzien']) ) ? $_GET['dzien'] : date("d");
if(strlen($dzien)==1)
	$dzien="0".$dzien;
//Include the code
echo "<center><img src=\"plot.php?min=".$min."&max=".$max."&kolumna=".$kolumna."&ildni=".$ildni."&data=".$rok."-".$miesiac."-".$dzien."\"></center>";


?>
</body>
</html>