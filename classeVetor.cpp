#include<iostream>
#include<cstdlib>

using namespace std;

class vetor{
	private:
		int mTamanho;
		int* mDados;
	public:
		vetor(int tam);
		~vetor();
		void preencher();
		void imprimir();
		int tamanho();
		int& operator[](int posicao);
};

vetor::vetor(int tam){
	mTamanho = tam;
	mDados = new int[tam];
}

vetor::~vetor(){
	delete[] mDados;
	mTamanho = 0;
}

void vetor::preencher(){
	for (int i = 0; i < mTamanho; i++){
		cin>> mDados[i];
	}	
}

void vetor::imprimir(){
	for (int i = 0; i < mTamanho; i++){
		cout<< mDados[i] << " " << endl;
	}
}

int vetor::tamanho(){
	return mTamanho;
}

int& vetor::operator[](int posicao){
	if((posicao>=0) and (posicao<tamanho))
		return mDados[posicao];
	else {
		cerr << "erro: posicao invalida!" << endl;
		exit(EXIT_FAILURE);
		return mDados[0];
	}
}

int main(){
	
	vetor V[]
	return 0;	
};
