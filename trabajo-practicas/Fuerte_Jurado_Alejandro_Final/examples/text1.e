# Programa que realiza el factorial
de un número #

leer(dato);

escribir dato;


si (dato < 0) entonces
	f := 0 ;
si_no
    i := dato;
    f := 1;

	@ Bucle repetir	
	repetir
        f := f * i;
        i := i - 1;
    hasta (i = 1)
fin_si

escribir f; 
