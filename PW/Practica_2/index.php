<!DOCTYPE html>
<htm lang="en">
<head>
	<title>El Chiricirco</title>

	<!--Tabla con bordes-->
	<style>
		table {
    		width:100%;
		}
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
		tr:hover {background-color:#f5f5f5;
	</style>	
</head>
<body style="background-image:url('background.jpg')">
<?php
	/*Incluye las funciones de consulta para la librería*/
	require_once('functions.php');
	
	/*Crea un nuevo objeto para llamar a las consultas*/
	$q = new LibreriaBaseDatos();
	
	/*Comprueba que se ha realizado bien la conexión a la base de datos*/
	if(empty($q->dbc)){
		echo "<h3 align='center'>¡Error!: No se pudo establecer la conexion con la base de datos.</h3><br/>";
		die();
	}
	
	echo <<<_END
	<h1 style="text-align:center;color:white">EL CHIRICIRCO</h1>
	<p style="font-size:25px;color:white">Lista de empleados</p>
	<table id="t01">
		<tr>
			<th>Nombre</th>
			<th>Apellidos</th>
			<th>Edad</th>
			<th>   </th>
		</tr>
_END;
		
		$empleados=$q->getAllEmpleados();
		foreach($empleados as $empleado){
			echo <<<_END
				<tr>
					<td>$empleado[nombre]</td>
					<td>$empleado[apellidos]</td>
					<td>$empleado[edad]</td>
					
					<td><a href="empleado.php?val=$empleado[id]">Ver mas detalles</td>
				</tr>
_END;
		}
		echo "</table>";
?>
</body>
</html>