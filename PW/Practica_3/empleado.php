<!DOCTYPE html>
<html>
<head>
	<title>Datos de empleado</title>
	<link rel="stylesheet" href="style_empleado.css">
</head>
<body style="background-image:url('background.jpg')">
<?php
	
	require_once('functions.php');

	/*Create queries object*/
	$q = new LibreriaBaseDatos();
	if(empty($q->dbc)){
	echo "<h3 align='center'> ¡Error!: No se pudo establecer la conexion con la base de datos.</h3><br/>";
	die();
	}
	
	$id = $_GET["val"];
	$row = $q->getEmpleado($id);
	
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
		<td colspan="2"><b>Genero: </b> $row[genero]</td>
	</tr>
	<tr>
		<td colspan="2"><b>Correo: </b> $row[correo]</td>
	</tr>
	<tr>
		<td colspan="2"><b>Telefono: </b> $row[telefono]</td>
	</tr>
	<tr>
		<td colspan="2"><b>Transporte preferido: </b> $row[transporte]</td>
	</table>
_END
?>
</body>
</html>