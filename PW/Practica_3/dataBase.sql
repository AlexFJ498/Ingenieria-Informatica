CREATE DATABASE IF NOT EXISTS empresa;
USE empresa;

CREATE TABLE IF NOT EXISTS empleados (
	id int(11) NOT NULL,
	nombre varchar(255) DEFAULT NULL,
	apellidos varchar(255) DEFAULT NULL,
	edad int(3)  DEFAULT NULL,
	genero varchar(255) DEFAULT NULL,
	correo varchar(255) DEFAULT NULL,
	telefono int(11) DEFAULT NULL,
	imagen varchar(255) DEFAULT NULL,
	PRIMARY KEY (id)
);

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(1,'Maria Jesus','Luque Carmona',32,'Mujer','mariajesusluque@gmail.com',957293849,'mariajesus.jpg');

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(2,'Antonio','Almendros Marmol',22,'Hombre','antonio@gmail.com',957283895,'antonio.jpg');

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(3,'Jose Manuel','Fuerte Espejo',52,'Hombre','josemanuel@gmail.com',957528374,'josemanuel.jpg');

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(4,'Cristina','Jurado Gil de Montes',21,'Mujer','cristina@gmail.com',957129436,'cristina.jpg');

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(5,'Alejandro','Fuerte Jurado',20,'Hombre','alejandro@gmail.com',957193875,'alejandro.jpg');

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(6,'Fernando','Jurado Carmona',40,'Hombre','fernando@gmail.com',957190875,'fernando.jpg');

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(7,'Alfonso','Fuerte Medina',53,'Hombre','alfonso@gmail.com',957284963,'alfonso.jpg');

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(8,'Desiree','Castelos Carmona',21,'Mujer','desiree@gmail.com',957204953,'desiree.jpg');

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(9,'Luis Jose','Campos Broncano',20,'Hombre','luisjose@gmail.com',957239201,'luisjose.jpg');

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(10,'Daniel','Gaitan Gomez',20,'Hombre','daniel@gmail.com',957320583,'daniel.jpg');

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(11,'Rafaldo','Penaldo Luna',46,'Hombre','rafaldopenaldo@gmail.com',957193184,'rafaldo.jpg');

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(12,'Javier','Hernandez Campos',20,'Hombre','javier@gmail.com',957874329,'javier.jpg');

INSERT INTO empleados (id,nombre,apellidos,edad,genero,correo,telefono,imagen) VALUES
(13,'Veronica','Castro Penas',20,'Mujer','veronica@gmail.com',957049248,'veronica.jpg');