<!DOCTYPE html>
<htm lang="en">
<head>
	<title>El Chiricirco</title>
</head>
<link rel="stylesheet" href="style.css">
<body style="background-image:url('background.jpg')">
<?php
	/*Incluye las funciones de consulta para la librería*/
	require_once('session.php');
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
_END;

	if(isset($_POST['sesion'])){
		if(strnatcasecmp($_POST['submitted'],"Cerrar sesion") == 0){
			session_destroy();
		}
		else{
				header('Location: /p2/authenticate.php');
		}	
	}

	if(isset($_POST['borrarTodo'])){
		$q->borrarTodosLosEmpleados();
	}

	if($logged){
		echo "Hola $name, está logeado como $username";
	}
	if($admin){
		echo " y es administrador";
		echo <<< _END
		    <div class="info">     
				<form method="post" action="index.php">
					 <input type="submit" name="borrarTodo" value="BORRAR TODOS LOS EMPLEADOS"/>	
				</form>
			</div>	
_END;
}	
	
	echo "<br";
	echo <<<_END
	    <div class="info">     
		<form method="post" action="index.php">
		     <input type="hidden" name="sesion" value=true>
			 <input type="submit" name="submitted" value="Iniciar sesion"/>			
			 <input type="submit" name="submitted" value="Cerrar sesion"/>
		</form>
		</div>
	<p style="font-size:25px;color:white">Lista de empleados</p>
	<a href="insertar.php" style="color:white">Insertar empleado</a>
	<table id="t01">
		<tr>
			<th>Nombre</th>
			<th>Apellidos</th>
			<th>Edad</th>
			<th>   </th>
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
					<td><a href="editar.php?val=$empleado[id]">Editar    |       
							<a href="borrar.php?val=$empleado[id]">|    Borrar </td>
				</tr>
_END;
		}
		echo "</table>";
?>
</body>
</html>