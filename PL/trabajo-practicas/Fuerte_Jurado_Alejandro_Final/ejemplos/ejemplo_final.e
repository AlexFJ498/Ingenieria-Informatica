#
  Asignatura:    Procesadores de Lenguajes

  Titulación:    Ingeniería Informática
  Especialidad:  Computación
  Curso:         Tercero
  Cuatrimestre:  Segundo

  Departamento:  Informática y Análisis Numérico
  Centro:        Escuela Politécnica Superior de Córdoba
  Universidad de Córdoba
 
  Curso académico: 2018 - 2019

  Fichero de ejemplo nº 5 para el intérprete de pseudocódigo en español: ipe.exe
#

@ Bienvenida

_borrar;

_lugar(10,10);

escribir_cadena('Introduce tu nombre --> ');

leer_cadena(nombre);

_borrar;
_lugar(10,10);

escribir_cadena(' Bienvenido/a << ');
ESCRIBIR_cadena(' >> al intérprete de pseudocódigo en español');
escribir_cadena(nombre);


_lugar(40,10);
escribir_CaDeNa('Pulsa una tecla para continuar');
leer_cadena( pausa);


repetir 

 @ Opciones disponibles

 _borrar;

 _lugar(10,10);
 escribir_cadena(' Factorial de un número --> 1 ');

 _lugar(11,10);
 escribir_cadena(' Máximo común divisor ----> 2 ');

 _lugar(12,10);
 escribir_cadena(' Sucesión de Fibonacci ---> 3 ');

 _lugar(13,10);
 escribir_cadena(' Potencia de un número ---> 4 ');

 _lugar(15,10);
 escribir_cadena(' Finalizar ---------------> 0 ');

 _lugar(18,10);
 escribir_cadena(' Elige una opcion ');

 leer(opcion);

 _borrar;

si (opcion  = 0) entonces       @ Fin del programa
	_lugar(10,10);
        escribir_cadena(nombre);
        escribir_cadena(': gracias por usar el intérprete');

si_no
	@ Factorial de un número
	si (opcion = 1) entonces
		_lugar(10,10);
		escribir_cadena(' Factorial de un numero  ');

                _lugar(11,10);
		escribir_cadena(' Introduce un numero entero ');
			leer(N);

        	factorial := 1;

       		para i desde 2 hasta N hacer
                	factorial := factorial * i;
       		fin_para;

        	@ Resultado
	       	_lugar(15,10);
		escribir_cadena(' El factorial de ');
		escribir(N);
		escribir_cadena(' es ');
		escribir(factorial);
    
   	@ Máximo común divisor
	si_no 
		si (opcion = 2) entonces
			_lugar(10,10);
			escribir_cadena(' Máximo común divisor de dos números ');

			_lugar(11,10);
                	escribir_cadena(' Algoritmo de Euclides ');

               		_lugar(12,10);
               		escribir_cadena(' Escribe el primer número ');
               		leer(a);

                 	_lugar(13,10);
                	escribir_cadena(' Escribe el segundo número ');
                  	leer(b);

                  	@ Se ordenan los números
			si (a < b) entonces 
				auxiliar := a;
				a := b;
				b := auxiliar;
			fin_si;

			@ Se guardan los valores originales
			A1 := a;
			B1 := b;

			@ Se aplica el método de Euclides	
			resto  := a _mod b;

			mientras (resto <> 0) hacer
				a :=  b;
				b := resto;
				resto := a _mod b;
			fin_mientras;
         
			@ Se muestra el resultado
			_lugar(15,10);
			escribir_cadena(' Máximo común divisor de ');
			escribir(A1);
			escribir_cadena(' y ');
			escribir(B1);
			escribir_cadena(' es ---> ');
			escribir(b);

		@ Sucesión de Fibonacci
		si_no
			si (opcion = 3) entonces
				_lugar(10,10);
				escribir_cadena(' Cálculo de la sucesión de Fibonacci ');
				escribir_cadena(' Cantidad de números que se desean calcular de la sucesión: ');
				leer(N);
				escribir_cadena(' Sucesión: ');

				a := 1;
				b := 1;
				escribir(a);
				escribir(b);

				para i desde 1 hasta N paso 1 hacer
					c := a + b;
					a := b;
					b := c;

					escribir(c);
				fin_para
			@ Potencia de un número
			si_no
				si (opcion = 4) entonces
					_lugar(10,10);
					escribir_cadena(' Cálculo de la potencia de un número ');
					escribir_cadena(' Introduzca un número: ');
					leer(N);
					escribir_cadena(' Introduzca la potencia: ');
					leer(pow);

					resultado := N ** pow;
					escribir_cadena(' El resultado es ');
					escribir(resultado);
	 			si_no  
					_lugar(15,10);
					escribir_cadena(' Opcion incorrecta ');
				fin_si
			fin_si
 		fin_si;   
  	fin_si;                 

  fin_si;                          

 _lugar(40,10); 
 escribir_cadena(' Pulse una tecla para continuar  --> \n');
 leer_cadena(pausa);
 
hasta (opcion = 0);             

@ Despedida final

_borrar;
_lugar(10,10);
escribir_cadena('El programa ha concluido');

