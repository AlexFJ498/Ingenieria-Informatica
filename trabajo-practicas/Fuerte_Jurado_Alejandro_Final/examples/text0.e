# Programa que realiza el factorial
de un número #

leer(dato);

escribir dato;

si (dato < 0) entonces
	f := 0 ;
si_no
    i := dato;
    f := 1;
	
	@ Bucle mientras
	mientras (i > 1) hacer
        f := f * i;
        i := i - 1;
    fin_mientras
fin_si

escribir f; 
