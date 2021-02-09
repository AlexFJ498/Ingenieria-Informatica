<?php
    require_once('functions.php');

    function login($username, $password){
        if (strlen($username) <= 0) {
            return false;
        }
        if (strlen($password) <= 0) {
            return false;
        }

        $q = new LibreriaBaseDatos();
        if (empty($q->dbc)) {
            echo "<h3 align='center'>¡Error!: No se pudo establecer la conexión con la base de datos.</h3><br/>";
            die();
        }

        $checkUser = $q->checkUserAndPassword($username, $password);

        if (!$checkUser) {
            return false;
        } else {
            session_start();
            $userSessionInfo = $q->getUserSessionInfo($username);
            $_SESSION['username'] = $userSessionInfo['usuario'];
            $_SESSION['name'] = $userSessionInfo['nombre'];
			if($userSessionInfo['Admin'] == 0){
				$_SESSION['admin'] = true;
			}
			else{
				$_SESSION['admin'] = false;
			}
            $_SESSION['admin'] = $userSessionInfo['admin'];
            $_SESSION['check'] = hash('ripemd128', $_SERVER['REMOTE_ADDR'] . $_SERVER['HTTP_USER_AGENT']);
			$_SESSION['last_action'] = time();

            header('Location: /p2/index.php');
            return true;
        }

    }

?>

<!DOCTYPE html>
<html lang="es">

<?php

require_once('functions.php');

/* Create queries object */
$q = new LibreriaBaseDatos();
if(empty($q->dbc)){
    echo "<h3 align='center'>¡Error!: No se pudo establecer la conexión con la base de datos.</h3><br/>";
    die();
}

	$expireAfter = 30;
	if(isset($_POST['last_action'])){
		$secondsInactive = time() - $_SESSION['last_action'];
		$expireAfterSeconds = $expireAfter * 60;
	
		if($secondsInactive >= $expireAfterSeconds){
        session_unset();
        session_destroy();
    }
	}

/* Check if the login has been submitted */
if (isset($_POST['login'])){

    //Check if cancel button has been selected
    if(strnatcasecmp ( $_POST['submitted'] , "Cancelar") == 0){
        header('Location: /p2/index.php');
    }
    else{
        $check = true;

        $username = $_POST['username'];
        $password = $_POST['password'];

        $checkLogin = login($username, $password);

        if($checkLogin){
            header('Location: /p2/index.php');
        }
        else{
            header('Location: /authenticate.php?auth=false');
        }
    }
}

/* Check if login/password was incorrect */
if (isset($_GET['auth'])){
    if($_GET['auth'] == "false"){
        echo "<h3 align='center' style='color: red'>Username or password was incorrect.</h3><br>";
    }
}

/* Check is the user is going to be added */
if (isset($_POST['addUser'])){
    //Check if cancel button has been selected
    if(strnatcasecmp ( $_POST['submitted'] , "Cancelar") == 0){
        header('Location: /p2/index.php');
    }
    else{
        $check = true;

        //Get the new user values
        $user['username'] = $_POST['username'];
        $user['password'] = $_POST['password'];
        $user['confirmPassword'] = $_POST['confirmPassword'];

        if($user['password'] != $user['confirmPassword']){
            $check = false;
        }

        $user['name'] = $_POST['name'];
        $user['surname'] = $_POST['surname'];
        $user['email'] = $_POST['email'];
        $user['phone'] = $_POST['phone'];

        if(($_POST['admin'] == "Si") || ($_POST['admin'] == "Sí")){
            $user['admin'] = true;
        }
        else if($_POST['admin'] == "No"){
            $user['admin'] = 0;
        }
        else{
            $check = false;
        }

        $check = $q->checkNewUser($user);

        if($check){
            $status = $q->insertarUsuario($user);

            //If correctly added
            if($status){
                $checkLogin = login($user['username'], $user['password']);

                if($checkLogin){
                    header('Location: /p2/index.php');
                }
                else{
                   echo "erroor!";
                }
            }
            else{
                echo "<h3 align='center' style='color: red'>An error ocurred. Please try again.</h3><br>";
            }
        }else{
            echo "<h3 align='center' style='color: red'>Please check the fields and try again.</h3><br>";
        }


    }
}

echo <<<_END
    <head>
        <meta charset="UTF-8">
        <title>Biblioteca - Login</title>
    
        <link rel="stylesheet" href="/font-awesome-4.7.0/css/font-awesome.min.css">
        <link rel="stylesheet" type="text/css" href="/style.css">
</head>
_END;

?>

<body>

<?php


echo <<<_END
    <div class="info">     
        <form method="post" action="authenticate.php">
            <table align="center" style="margin: 0 auto;">
                <tr align="center" >
                    <th colspan="2"><h3>Login</h3></th>
                </tr>  
                <tr align="left" >
                    <td >Usuario</td>
                    <td ><input type="text" name="username" value=""></td>
                </tr>  
                <tr align="left" >
                    <td >Contraseña</td>
                    <td ><input type="password" name="password" value=""></td>
                </tr>  
                <tr align="center" >
                    <td colspan="2">
                        <input type="hidden" name="login" value=true>
                        <input type="submit" name="submitted" value="Aceptar"/>
                        <input type="submit" name="submitted" value="Cancelar"/>
                    </td>
                </tr>
            </table>
        </form>
    </div>
    
    <hr width=60% align="center"> 
    
    <div class="info">     
        <form method="post" action="authenticate.php">
            <table align="center" style="margin: 0 auto;">
                <tr align="center" >
                    <th colspan="2"><h3>Nuevo usuario</h3></th>
                </tr>  
                <tr align="left" >
                    <td >Usuario *</td>
                    <td ><input type="text" name="username""></td>
                </tr>  
                <tr align="left" >
                    <td >Contraseña *</td>
                    <td ><input type="password" name="password"></td>
                </tr>  
                <tr align="left" >
                    <td >Confirmar contraseña *</td>
                    <td ><input type="password" name="confirmPassword" value=""></td>
                </tr>  
                <tr align="left" >
                    <td >Nombre *</td>
                    <td ><input type="text" name="name""></td>
                </tr>  
                <tr align="left" >
                    <td >Apellidos</td>
                    <td ><input type="text" name="surname""></td>
                </tr>  
                <tr align="left" >
                    <td >e-mail *</td>
                    <td ><input type="text" name="email""></td>
                </tr> 
                <tr align="left" >
                    <td >Teléfono</td>
                    <td ><input type="text" name="phone""></td>
                </tr> 
                <tr align="center" >
                    <td colspan="2">
                        <input type="hidden" name="addUser" value=true>
                        <input type="hidden" name="admin" value=false>
                        <input type="submit" name="submitted" value="Aceptar"/>
                        <input type="submit" name="submitted" value="Cancelar"/>
                    </td>
                </tr>
            </table>
        </form>

    </div>

    
_END;


?>

