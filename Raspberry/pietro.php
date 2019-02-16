<div style="
			position: relative;
			margin: 0 auto;
			width: 900px;
			<!--height: 1000px;-->
			border: 1px solid black;
			">
			<a href="">
			<img src="pietro.png" width="1000px" ismap>
			</a>
			<!--------------------------------------------------------------------------------------------------------->
			<div style="           
				position: absolute;
				left:     190px;
				top:    95px;
				border: 0px solid black;
				"
			>
			 <form action="http://192.168.1.101/toggle">
				<input type='hidden' name='out1' value='1' />
				<input type='submit' value='Switch' />
			</form>
			</div>
			<!--------------------------------------------------------------------------------------------------------->
			<a href="wykres.php?kolumna=2&min=0&max=1">
			<div style="           
				position: absolute;
				left:     265px;
				top:    97px;
				border: 0px solid black;
				"
			>
			 
			 <iframe scrolling="no" width="20px"height="20px" frameborder="0" marginheight="0px" marginwidth="0px"  src="http://192.168.1.101/picstate?out=1"></iframe>
			H</div>
			</a>
			<!--------------------------------------------------------------------------------------------------------->
			<div style="           
				position: absolute;
				left:     190px;
				top:    120px;
				border: 0px solid black;
				"
			>
			 <form action="http://192.168.1.101/toggle">
				<input type='hidden' name='out2' value='1' />
				<input type='submit' value='Switch' />
			</form>
			</div>
			<!--------------------------------------------------------------------------------------------------------->
			<a href="wykres.php?kolumna=3&min=0&max=1">
			<div style="           
				position: absolute;
				left:     265px;
				top:    122px;
				border: 0px solid black;
				"
			>
			 
			 <iframe scrolling="no" width="20px"height="20px" frameborder="0" marginheight="0px" marginwidth="0px"  src="http://192.168.1.101/picstate?out=2"></iframe>
			H</div>
			</a>
			<!--------------------------------------------------------------------------------------------------------->
			<a href="wykres.php?kolumna=4&min=12&max=22">
			<div style="           
						position: absolute;
						left:     230px;
						top:    200px;
						border: 0px solid black;
						"
			>
			 
			 <iframe scrolling="no" width="50px"height="14px" frameborder="0" marginheight="0px" marginwidth="0px"  src="http://192.168.1.103/state?in=A"></iframe>&#176 C
			</div>
			</a>
			<!--------------------------------------------------------------------------------------------------------->
	
</div>	