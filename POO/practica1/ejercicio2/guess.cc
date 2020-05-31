#include <iostream>
#include <cstdlib>
#include <ctime>

//guess.cc

//A program that generates a random number between 1 and 10 and asks for a number to the user in order to indicate if it is bigger, smaller or equal to the first number.

int main(){
	int i,j,fin=0;
	
	srand(time(NULL));
	j=rand()%10+1;

	do{	
		std::cout<<"Introduce un número\n";
		std::cin>>i;

		if(i>j){
			std::cout<<i<<" es mayor que el numero aleatorio\n";
		}
		if(i<j){
			std::cout<<i<<" es menor que el numero aleatorio\n";
		}
		if(i==j){
			std::cout<<"Ha adivinado el numero. Fin de programa\n";
			fin=1;
		}
	}while(fin==0);
}
