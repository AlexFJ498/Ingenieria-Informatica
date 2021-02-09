<?php
    session_start();

    if(isset($_SESSION['username'])){
        $logged = true;
        $username = $_SESSION['username'];
        $name = $_SESSION['name'];
        $admin = $_SESSION['admin'];
    }
	else{
		$logged = false;
		$admin = false;
	}

?>
