#include <iostream>

using namespace std;

int somatorio(int base){

	if(base==1){
		return 1;
	} else {
		return ((base^2) + somatorio(base-1));
	}
}
int main(){

	int valor=0;
	cin>> valor;
	cout<< somatorio(valor) << endl;

	return 0;
}
