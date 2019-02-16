<?php
//header( "Content-type: image/png" );

$kolumna = (isset($_GET['kolumna']) && !empty($_GET['kolumna']) ) ? $_GET['kolumna'] : 1;
$data = (isset($_GET['data']) && !empty($_GET['data']) ) ? $_GET['data'] : date("Y-m-d");
$step = (isset($_GET['step']) && !empty($_GET['step']) ) ? $_GET['step'] : 1;
$ildni = (isset($_GET['ildni']) && !empty($_GET['ildni']) ) ? $_GET['ildni'] : 1;

//echo"1<br>";
//Include the code
require_once 'plot/phplot.php';
//echo"2<br>";
//Define the object
$plot = new PHPlot(1300,600);
//echo"3<br>";
//Set titles
$plot->SetTitle("");
$plot->SetXTitle('Czas');
$plot->SetYTitle('');

$plot->SetNumXTicks(460);
$plot->SetPlotType('lines');
//echo"4<br>";

//Define some data
$example_data=[];
//echo"5<br>";
$tmp=str_getcsv($data,"-");
$rok=$tmp[0];
$miesiac=$tmp[1];
$dzien=$tmp[2];
$lines=array();
for($i=$dzien-(int)$ildni+1;$i<=$dzien;$i++)
{
	$data="".$rok."-".$miesiac."-".$i;
	$tmp=file("USB_DISK/".$data.".txt");
	foreach ($tmp as $line_num => $line) 
	//for($j=0;$j<=count($lines);i++)
		{
			array_push($lines,$line);
		}
		
	//echo $data."\n";
	//$tmp=;
	//foreach ($lines as $line_num => $line) 
	//{
	//	array_push($lines,file("USB_DISK/".$data.".txt"));
	//}
}


//$lines = file("USB_DISK/".$data.".txt");
//echo"6<br>";
$currentstep=0;
$tmp_min=9999999;
$tmp_max=-9999999;
foreach ($lines as $line_num => $line) 
{
	if ($currentstep>$step)
	{
		
		$liniacsv=str_getcsv($line,";");
		//echo $liniacsv[1]."\n";
		if ($tmp_min>(int)$liniacsv[(int)$kolumna]) 
		{
			$tmp_min=(int)$liniacsv[(int)$kolumna];
		}
		if ($tmp_max<(int)$liniacsv[(int)$kolumna]) 
		{
			$tmp_max=(int)$liniacsv[(int)$kolumna];
		}
		
		if($line_num==2 ||$line_num==(count($lines)-1) ||$line_num==(int)((count($lines)-1)/18) ||$line_num==(int)(((count($lines)-1)/18)*2) ||$line_num==(int)(((count($lines)-1)/18)*3) ||$line_num==(int)(((count($lines)-1)/18)*4) ||$line_num==(int)(((count($lines)-1)/18)*5) ||$line_num==(int)(((count($lines)-1)/18)*6) ||$line_num==(int)(((count($lines)-1)/18)*7) ||$line_num==(int)(((count($lines)-1)/18)*8) ||$line_num==(int)(((count($lines)-1)/18)*9) ||$line_num==(int)(((count($lines)-1)/18)*10) ||$line_num==(int)(((count($lines)-1)/18)*11) ||$line_num==(int)(((count($lines)-1)/18)*12) ||$line_num==(int)(((count($lines)-1)/18)*13) ||$line_num==(int)(((count($lines)-1)/18)*14) ||$line_num==(int)(((count($lines)-1)/18)*15) ||$line_num==(int)(((count($lines)-1)/18)*16) ||$line_num==(int)(((count($lines)-1)/18)*17) )
		{
			$tmp=$liniacsv[0];
			$tmp=str_getcsv($tmp,' ');
			array_push ($example_data,array($tmp[1],(float)$liniacsv[$kolumna]));
		}
		else
		{
			array_push ($example_data,array('',(float)$liniacsv[(int)$kolumna]));
		}
	}
	else 
	{
		$currentstep++;
	}
}
$min = (isset($_GET['min']) && !empty($_GET['min']) ) ? $_GET['min'] :$tmp_min-1;
$max = (isset($_GET['max']) && !empty($_GET['max']) ) ? $_GET['max'] :$tmp_max+1;

$plot->SetPlotAreaWorld(NULL,$min,NULL,$max );
$plot->SetDataValues($example_data);

//Turn off X axis ticks and labels because they get in the way:
//$plot->SetXTickLabelPos('none');
$plot->SetXTickPos('none');

//Draw it
$plot->DrawGraph();

?>