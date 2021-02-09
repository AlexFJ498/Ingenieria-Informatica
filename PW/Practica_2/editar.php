<!DOCTYPE html>
<?php
require_once('session.php');
require_once('functions.php');

/*Create queries object*/
$q = new LibreriaBaseDatos();
if(empty($q->dbc)){
	echo "<h3 align='center'> ¡Error!: No se pudo establecer la conexion con la base de datos.</h3><br/>";
	die();
}

if(!$logged){
	header('Location: /p2/authenticate.php');
}

	$id = $_GET['val'];

if(isset($_POST['editar'])){
	//Check if cancel button has been selected
	if(strnatcasecmp($_POST['submitted'],"Cancelar") == 0){
		header('Location: /p2/index.php');
	}
	else{		
		//Get the new values
		$empleado['nombre'] = $_POST['nombre'];
		$empleado['apellidos'] = $_POST['apellidos'];
		$empleado['edad'] = $_POST['edad'];
		$empleado['genero'] = $_POST['genero'];
		$empleado['correo'] = $_POST['correo'];
		$empleado['telefono'] = $_POST['telefono'];
		$empleado['imagen'] = $_POST['imagen'];
		$empleado['transporte'] = $_POST['transporte'];
		$oldID= $_POST_['identif'];
		echo  $_POST['nombre'];
		echo $_POST_['identif'];
			$status = $q->editarEmpleado($empleado,$oldID);
			
			//If correctly added, go to main page
			if($status){
				//header('Location: /p2/index.php');
			}
			else{
				echo "h3 align='center' style='color: red'>An error ocurred. Please try again.</h3><br>";
			}
	}
}

$empleado= $q->getEmpleado($id);

echo <<<_END
	<head>
		<meta charset="UTF-8">
		<title>Editar empleado empleado</title>
		
		<link rel="stylesheet" href="style.css">
	</head>
_END;

?>

<body style="background-image:url('background.jpg')">
<?php
	/*Print the information*/
	echo <<<_END
	<div class="info">
		<form method="post" action="editar.php">
			<table align="center" style="margin: 0 auto;">
				<tr align="center" >
					<th colspan="2"><h3>Editar empleado</h3></th>
				</tr>
				<tr align="left" >
					<td>Nombre</td>
					<td> <input type="text" name="nombre" value=$empleado[nombre]></td>
				</tr>
				<tr align="left" >
					<td>Apellidos</td>
					<td> <input type="text" name="apellidos" value=$empleado[apellidos]></td>
				</tr>
				<tr align="left" >
					<td>Edad</td>
					<td> <input type="text" name="edad"value=$empleado[edad] ></td>
				</tr>
				<tr align="left" >
					<td>Genero</td>
					<td> <input type="radio" name="genero" value="Mujer">Mujer
							 <input type="radio" name="genero" value="Hombre">Hombre
							 <input type="radio" name="genero" value="Otro">Otro
					</td>
				</tr>
				<tr align="left" >
					<td>Correo</td>
					<td> <input type="text" name="correo" value=$empleado[correo]></td>
				</tr>
				<tr align="left" >
					<td>Telefono</td>
					<td> <input type="text" name="telefono" value=$empleado[telefono] ></td>
				</tr>
				<tr align="left" >
					<td>Imagen</td>
					<td> <input type="text" name="imagen" $empleado[imagen]></td>
				</tr>
				<tr align="left" >
					<td>Transporte/s preferido/s</td>
					<td> <input type="checkbox" name="transporte" value="Coche"> Coche<br>
							 <input type="checkbox" name="transporte" value="Bicicleta"> Bicicleta<br>
							 <input type="checkbox" name="transporte"  value="Autobús"> Autobús<br>
							 <input type="checkbox" name="transporte"value="Andando" > Andando<br>
					</td>
				</tr>
				<tr align="center" >
					<td colspan="2">
						<input type="hidden" name="editar" value=true>
						<input type="hidden" name="identif" value=$id/>
						<input type="submit" name="submitted" value="Aceptar"/>
						<input type="submit" name="submitted" value="Cancelar"/>
					</td>
				</tr>
			</table>
		</form>
	</div>
_END;
?>
</body>