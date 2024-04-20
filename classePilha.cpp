#include<iostream>
#include<cstdlib>

using namespace std;

class noh{
	friend class pilha;
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

class pilha{
	friend class noh;
	private:
		unsigned mTamanho;
		noh* mTopo;
	public:
		pilha();
		~pilha();
		void insere(int valor);
		int retira();
		void limpaPilha();
		bool vazia();
		int espia();
};

pilha::pilha(){
	mTopo = NULL;
	mTamanho = 0;
}

pilha::~pilha(){
	limpaPilha();
}
void pilha::insere(int valor){
	noh* novo = new noh(valor);
	novo->mProx = mTopo;
	mTopo = novo;
	mTamanho++;
}
int pilha::retira(){
	int valor = mTopo->mValor;
	noh* temp = mTopo;
	mTopo = mTopo->mProx;
	delete temp;
	mTamanho--;
	return valor;
}
bool pilha::vazia(){
	return (mTamanho==0);
}
int pilha::espia(){
	return mTopo->mValor;
}
		
void pilha::limpaPilha(){
	while(not vazia()){
		retira();
	}
}
