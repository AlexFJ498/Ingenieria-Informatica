<?php

class LibreriaBaseDatos{
	//Username
	public $user = 'alejandro';
	
	//Password
	public $password = 'alejandro';

	//Database connection PDO object
	public $dbc;

	//Constructor. It connects to the database
	public function __construct(){
		$this->dbc = $this->dbconnect();
	}
	
	//Connect to the database and table library
	public function dbconnect(){
		$dbc = null;
		
		try{
		  	$dbc = new PDO('mysql:host=localhost;dbname=empresa', $this->user, $this->password);
		}catch(PDOException $e){
			echo "ERROR: " . $e->getMessage();
		}
  	return $dbc;
	}

	//Get an array with all objects
	public function getAllEmpleados(){
		$empleados = array();
		$i=0;
		$sentence = $this->dbc->prepare("SELECT * FROM empleados");
		if($sentence->execute()){
			while($row=$sentence->fetch()){
				$empleados[$i]=$row;
				$i++;
			}
		}
		return $empleados;
	}
	
	public function getAllUsuarios(){
		$usuarios = array();
		$i=0;
		$sentence = $this->dbc->prepare("SELECT *FROM usuarios");
		if($sentence->execute()){
			while($row=$sentence->fetch()){
				$usuarios[$i]=$row;
				$i++;
			}
		}
		return $usuarios;
	}
	
	public function getEmpleado($id){
		$i=0;
		$sentence = $this->dbc->prepare("SELECT * FROM empleados");
		if($sentence->execute()){
			while($row=$sentence->fetch()){
				if($row['id'] == $id){
					return $row;
				}
				$i++;
			}
		}
	}
	
	public function checkNewEmpleado($empleado){
		$empleados=$this->getAllEmpleados();
		if(in_array($empleado,$empleados)){
			//Si encuentra el empleado en la base de datos no se puede añadir porque ya existe
			return false;
		}
		return true;
	}
	
	public function checkNewUser($usuario){
		$usuarios=$this->getAllUsuarios();
		if(in_array($usuario,$usuarios)){
			return false;
		}
		return true;
	}
	
	public function checkUserAndPassword($username,$contrasena){
		$i=0;
		$sentence = $this->dbc->prepare("SELECT * FROM usuarios");
		if($sentence->execute()){
			while($row=$sentence->fetch()){
				if(($row['usuario'] == $username) ){
					if($row['contrasena'] == $contrasena){
						return true;
					}
				}
				$i++;
			}
		}
		return false;
	}
	
	public function insertarEmpleado($empleado){
		try{
			$id=$this->getNewId();
			$sql = "INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen,transporte) VALUES
						($id,'$empleado[nombre]','$empleado[apellidos]',$empleado[edad],'$empleado[genero]','$empleado[correo]',$empleado[telefono],'$empleado[imagen]','$empleado[transporte]')";
			$this->dbc->exec($sql);
			return true;
			}catch(PDOException $e){
				return false;
			}
	}
	
	public function insertarUsuario($usuario){
	try{
		$id=$this->getNewIdUser();
		$sql = "INSERT INTO usuarios (id,usuario,contrasena,nombre,apellidos,correo,telefono) VALUES
					($id,'$usuario[username]','$usuario[password]','$usuario[name]','$usuario[surname]','$usuario[email]',$usuario[phone])";
		$this->dbc->exec($sql);
		return true;
	}catch(PDOException $e){
		return false;
	}
	}
	
	public function getNewId(){
		$empleados = array();
		$i=0;
		$sentence = $this->dbc->prepare("SELECT * FROM empleados");
		if($sentence->execute()){
			while($row=$sentence->fetch()){
				$empleados[$i]=$row;
				$i++;
			}
		}
		$i++;
		return $i;
	}
	
	public function getNewIdUser(){
		$usuarios = array();
		$i=0;
		$sentence = $this->dbc->prepare("SELECT * FROM usuarios");
		if($sentence->execute()){
			while($row=$sentence->fetch()){
				$usuarios[$i]=$row;
				$i++;
			}
		}
		$i++;
		return $i;
	}
	
	public function borrarEmpleado($id){
		try{
			$sql = "DELETE FROM empleados WHERE id=$id";
			$this->dbc->exec($sql);
		}catch(PDOException $e){
			return false;
		}
			return true;
	}
	
	public function borrarTodosLosEmpleados(){
		try{
			$sql = "DELETE  FROM empleados";
			$this->dbc->exec($sql);
		}catch(PDOException $e){
			return false;
		}
		return true;
	}
	
	public function editarEmpleado($empleado, $oldID){
	try{
		$sql = "UPDATE empleados SET nombre='$empleado[nombre]', apellidos='$empleado[apellidos]', edad=$empleado[edad], genero='$empleado[genero],
																 correo='$empleado[correo], telefono=$empleado[telefono], imagen='$empleado[imagen], transporte='$empleado[transporte]'
																 WHERE id=$oldID";
															echo $sql;
		$this->dbc->exec($sql);
		return true;
	}catch(PDOException $e){
		return false;
	}
	}
	
	public function getUserSessionInfo($username){
		$i=0;
		$sentence = $this->dbc->prepare("SELECT * FROM usuarios");
		if($sentence->execute()){
			while($row=$sentence->fetch()){
				if($row['usuario'] == $username){
					return $row;
				}
				$i++;
			}
		}
	}
}
?>