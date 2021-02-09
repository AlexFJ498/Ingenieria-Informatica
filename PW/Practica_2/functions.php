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
	
	//Get an array with the age of an specific employee
	public function getEdad($empleado){
		$edad= array();
		$i=0;
		
		$sentence = $this->dbc->prepare("SELECT * FROM empleados WHERE edad = ?");
		
		if($sentence->execute(array($empleado))){
			while ($row = $sentence->fetch()){
				$edad[$i] = $row;
				
				if($row['avaiable'])
					$edad[$i]['available'] = "Si";
				else
					$edad[$i]['available'] = "No";
					
				$i++;
			}
		}
		return $edad;
	}
	
	//Get an array with the name of an specific employee
	public function getNombre($empleado){
		$nombre= array();
		$i=0;
		
		$sentence = $this->dbc->prepare("SELECT * FROM empleados WHERE nombre = ?");
		
		if($sentence->execute(array($empleado))){
			while ($row = $sentence->fetch()){
				$nombre[$i] = $row;
				
				if($row['avaiable'])
					$nombre[$i]['available'] = "Si";
				else
					$nombre[$i]['available'] = "No";
					
				$i++;
			}
		}
		return $nombre;
	}
	
	//Get an array with the apellidos of an specific employee
	public function getApellidos($empleado){
		$apellidos= array();
		$i=0;
		
		$sentence = $this->dbc->prepare("SELECT * FROM empleados WHERE apellidos = ?");
		
		if($sentence->execute(array($empleado))){
			while ($row = $sentence->fetch()){
				$apellidos[$i] = $row;
				
				if($row['avaiable'])
					$apellidos[$i]['available'] = "Si";
				else
					$apellidos[$i]['available'] = "No";
					
				$i++;
			}
		}
		return $apellidos;
	}
	
	//Get an array with the genre of an specific employee
	public function getGenero($empleado){
		$genero= array();
		$i=0;
		
		$sentence = $this->dbc->prepare("SELECT * FROM empleados WHERE genero = ?");
		
		if($sentence->execute(array($empleado))){
			while ($row = $sentence->fetch()){
				$genero[$i] = $row;
				
				if($row['avaiable'])
					$genero[$i]['available'] = "Si";
				else
					$genero[$i]['available'] = "No";
					
				$i++;
			}
		}
		return $genero;
	}
	
	//Get an array with the e-mail of an specific employee
	public function getCorreo($empleado){
		$correo= array();
		$i=0;
		
		$sentence = $this->dbc->prepare("SELECT * FROM empleados WHERE correo = ?");
		
		if($sentence->execute(array($empleado))){
			while ($row = $sentence->fetch()){
				$correo[$i] = $row;
				
				if($row['avaiable'])
					$correo[$i]['available'] = "Si";
				else
					$correo[$i]['available'] = "No";
					
				$i++;
			}
		}
		return $correo;
	}
	
	//Get an array with the telephone of an specific employee
	public function getTelefono($empleado){
		$telefono= array();
		$i=0;
		
		$sentence = $this->dbc->prepare("SELECT * FROM empleados WHERE telefono = ?");
		
		if($sentence->execute(array($empleado))){
			while ($row = $sentence->fetch()){
				$telefono[$i] = $row;
				
				if($row['avaiable'])
					$telefono[$i]['available'] = "Si";
				else
					$telefono[$i]['available'] = "No";
					
				$i++;
			}
		}
		return $telefono;
	}
}
?>