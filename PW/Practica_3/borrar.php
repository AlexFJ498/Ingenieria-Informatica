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
else{
	
	$id = $_GET["val"];
		
	$status = $q->borrarEmpleado($id);
		
	if($status){
	header('Location: /p2/index.php');
	}
	else{
		echo "Error!!";
	}
}
?>