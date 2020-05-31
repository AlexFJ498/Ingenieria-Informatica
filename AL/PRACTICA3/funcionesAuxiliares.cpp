#include "funcionesAuxiliares.hpp"

void rellenarConjunto(Conjunto &c,int i){
	int num;
  srand (time(NULL));

	for (int n=0;n<i;n++){
		num=rand()%10000 + 1;
		c.insertarElemento(num);
	}

}

void kMenores(int iz ,int de,int n,int k,Conjunto &c,Conjunto &cAux,int &contador){
	contador++;
	int aux,i,j,x;
	i=iz;
	j=de;
	x=c.accederElemento((int)((iz+de)/2));

	do{
		while(c.accederElemento(i)<x){
			i++;
		}

		while(c.accederElemento(j)>x){
			j--;
		}
		if(i<=j){
			aux=c.accederElemento(i);
			c.modificarElemento(c.accederElemento(j),i);
			c.modificarElemento(aux,j);
			i++;
			j--;
		}
	}while (i<=j);

	if(k==i-1){
		std::cout<<"Ejercicio resuelto"<<std::endl;
		for(int aux=0;aux<k;aux++){
			cAux.insertarElemento(c.accederElemento(aux));
		}
	}
	else{
		if(k<i-1){
			kMenores(iz,j,n,k,c,cAux,contador);
		}
		else{
			kMenores(i,de,n,k,c,cAux,contador);
		}
	}
}

bool encontrarValor(std::vector<int> v,int val){
	for(unsigned int i=0;i<v.size();i++){
		if(v[i]==val){
			return true;
		}
	}
	return false;
}
