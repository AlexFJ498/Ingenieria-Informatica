<!DOCTYPE html>
<html>
<head>
	<title>Datos de empleado</title>
	<style>
		th, td{
    		padding: 15px;
    		text-align: left;
		}
		table tr:nth-child(even){
    		background-color: #eee;
		}
		table tr:nth-child(odd){
   			background-color: #fff;
		}
		table th{
    		background-color: black;
    		color: white;
		}
		a:link, a:visited {
   			background-color: #f44336;
    		color: white;
    		padding: 14px 25px;
    		text-align: center;
    		text-decoration: none;
    		display: inline-block;
		}
	</style>
</head>
<body style="background-image:url('background.jpg')">
<?php

	$conn = new mysqli('localhost','alejandro','alejandro','empresa');
	$sql = "SELECT * FROM empleados WHERE id=".$_GET["val"];
	$rows = $conn->query ($sql);
	if(!$rows)
		die ($conn->error);
	$row = $rows->fetch_assoc ();
	
	echo <<<_END
	<h1 style="text-align:center;color:white"><b>$row[nombre] $row[apellidos]</b></h1>
	<p style="font-size:25px;text-align:center;color:white"><b>Ficha completa</b></p>
	<a href="index.php">Volver a la pagina principal</a>
	<table style="margin: 0 auto;">
	<tr>
		<td rowspan="3"><img src=$row[imagen] alt="" style="width:150px;height:150px;"></td>
		<td width="70%"><b>Nombre: </b>$row[nombre]</td>
	</tr>
	<tr>
		<td><b>Apellidos: </b> $row[apellidos]</td>
	</tr>
	<tr>
		<td><b>Edad: </b> $row[edad]</td>
	</tr>
	<tr>
		<td colspan="2"><b>Correo: </b> $row[correo]</td>
	</tr>
	<tr>
		<td colspan="2"><b>Telefono: </b> $row[telefono]</td>
	</tr>
	</table>
_END
?>
</body>
</html>