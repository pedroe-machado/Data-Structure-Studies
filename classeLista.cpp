#include<iostream>
using namespace std;

class noh{
	friend class lista;
	private:
		int mValor;
		noh* mProx;
	public:
		noh(int valor);
};
noh::noh(int valor){
	mValor = valor;
	mProx = NULL;
}
class lista{
	private:
		noh* inicio;
		noh* fim;
		unsigned mTam;
	public:
		lista();
		~lista();
		void imprimir();
		void remove(int pos);
		void insereInicio(int valor);
		void insereFim(int valor);
		void inserePos(int valor, int pos);
		bool vazia();
		int busca(int valor);
};
lista::lista(){
	inicio = NULL;
	fim = NULL;
	mTam = 0;
}
lista::~lista(){
	
}
void lista::imprimir(){
	noh* aux = inicio;
	while (aux!=NULL){
		cout << aux->mValor << " ";
		aux = aux->mProx;
	}
}
void lista::insereInicio(int valor){
	noh* novo = new noh(valor);
	if (vazia()){
		inicio = novo;
		fim = novo;
		novo->mProx = NULL;
	} else {
		novo->mProx = inicio;
		inicio = novo;
	}
	mTam++;
}
void lista::insereFim(int valor){
	noh* novo = new noh(valor);
	if (vazia()){
		inicio = novo;
		fim = novo;
		novo->mProx = NULL;
	} else {
		fim->mProx = novo;
		fim = novo;
	}
	mTam++;
}
void lista::inserePos(int valor, int pos){
	if (pos==0){
		insereInicio(valor);
	} else if (pos==mTam-1){
		insereFim(valor);
	} else {
		noh* novo = new noh(valor);
		noh* aux = inicio;
		int posAux=0;
		while (posAux<(pos-1)){
			aux = aux->mProx;
			posAux++;
		}
		novo->mProx = aux->mProx;
		aux->mProx = novo;
		mTam++;
	}
}
bool lista::vazia(){
	return (mTam==0);
}
int lista::busca(int valor){
	noh* aux = inicio;
	int pos=0;
	while (aux!=NULL and aux->mValor!=valor){
		aux = aux->mProx;
		pos++;
	}
	if (aux!=NULL){
		return pos;
	} else {
		cout << "não encontrado" << endl;
		return -1;
	}
}

void lista::remove(int pos){
	if(not vazia()){
		if(pos>=0 and pos<mTam){
			if (pos==0){
				noh* aux = inicio;
				inicio = aux->mProx;
				delete aux;
				mTam--;
				if(vazia()){
					fim = NULL;
				}
			} else if (pos==mTam-1){
				noh* aux = inicio;
				while (aux->mProx != NULL){
					aux = aux->mProx;
				}
				delete(aux->mProx);
				mTam--;
				aux->mProx = NULL;
				fim = aux;
			} else {
				noh* anterior;
				noh* aux = inicio;
				int posAux=0;
				while (posAux<(pos)){
					anterior = aux;
					aux = aux->mProx;
					posAux++;
				}
				anterior->mProx = aux->mProx;
				delete aux;
				mTam--;
			}
		} else cout<< "posicão inválida" << endl;
	} else cout<< "lista vazia" <<endl;
}
