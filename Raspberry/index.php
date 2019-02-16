<!DOCTYPE HTML>
<html>
<head>
<title>ESP8266</title>
<meta http-equiv="Cache-Control" content="no-cache, no-store, must-revalidate" />
<meta http-equiv="Pragma" content="no-cache" />
<meta http-equiv="Expires" content="-1" />

<script>
window.onpageshow = function(event) 
{
    if (event.persisted) 
	{
        window.location.reload()
    }
}
</script>

</head>
<body>
<script>     
//setTimeout("location.reload();",30000);
</script>
<center>
<table>
<tr>
<td>
<button onclick="location.reload();">Odśwież</button>
</td>
<td>
<form  action="pietro.php" target="iframe_content">
<input type="submit" value="Piętro" />
</form>
</td>
<td>
<form method="post" action="parter.php" target="iframe_content">
<input type="submit" value="Parter" />
</form>
</td>
<td>
<form method="post" action="piwnica.php" target="iframe_content">
<input type="submit" value="Piwnica" />
</form>
</td>
<td>
<form  action="wykres.php?kolumna=1" target="iframe_content">
<input type="hidden" name="kolumna" value="1">
<input type="hidden" name="min" value="-1">
<input type="hidden" name="max" value="20">
<input type="submit" value="Czas cyklu" />
</form>
</td>
</tr>
</table>
</center>
<hr />
<iframe name="iframe_content"scrolling="no" width="100%"height="2000" frameborder="0" marginheight="0px" marginwidth="0px"  src="parter.php" ></iframe>

<!-- --------------------------------------------------------------------------------------------->

<!-- --------------------------------------------------------------------------------------------->
<hr />

<!-- --------------------------------------------------------------------------------------------->
<hr />

<!-- --------------------------------------------------------------------------------------------->

<!-- --------------------------------------------------------------------------------------------->
</body>
</html>