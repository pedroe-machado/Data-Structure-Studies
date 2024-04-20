#include<iostream>
#include<cstdlib>

using namespace std;

class noh {
	friend class fila;
        private:
            string mDado; 
            noh* mProx;
        public:
            noh(string info){
                mDado = info;
                mProx = NULL;
            }
            ~noh(){
                mProx = NULL;
                delete mProx;
            }
};

class fila{
	friend class noh;
	private:
		unsigned mTamanho;
		noh* mInicio;
		noh* mFim;
	public:
		fila();
		~fila();
		void insere(string nome);
		string retira();
		void limpafila();
		bool vazia();
};

fila::fila(){
	mInicio = NULL;
	mFim = NULL;
	mTamanho = 0;
}

fila::~fila(){
	limpafila();
}
void fila::insere(string info){
	noh* novo = new noh(info);
	
	mFim->mProx = novo;
	mFim = novo;
	mTamanho++;
}
string fila::retira(){
	string info = mInicio->mDado;
	noh* temp = mInicio;
	mInicio = mInicio->mProx;
	delete temp;
	mTamanho--;
	return info;
}
bool fila::vazia(){
	return (mTamanho==0);
}
		
void fila::limpafila(){
	while(mTamanho>0){
		retira();
	};
}
