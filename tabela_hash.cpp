#include <iostream>
using namespace std;

class palavra{
    private:
        string pal;
        string significado;
        palavra* proxima;
    public:
        palavra();
        palavra(string pal, string significado);
        palavra* getProxima();
        void setProxima(palavra* pal);
        string getPalavra();
        string getSignificado();
};

palavra::palavra(){
    proxima = NULL;
}

palavra::palavra(string pal, string significado){
    this->pal = pal;
    this->significado = significado;
    this->proxima = NULL;
}

palavra* palavra::getProxima(){
    return proxima;
}

void palavra::setProxima(palavra* pal){
    proxima = pal;
}

string palavra::getPalavra(){
    return pal;
}

string palavra::getSignificado(){
    return significado;
}

class tabela{
    private:
        palavra** vetor;
        int tam;
        int pos(string pal);
        palavra* procurar(string pal);
    public:
        tabela(int tam);
        ~tabela();
        void incluir(string pal, string significado);
        void imprimir(string pal);
        
};

void tabela::imprimir(string  pal){
    palavra* aux = procurar(pal);
    if(aux == NULL){
        cout << "[" << pal << "]" << " => NULL" << endl;
    }else{
        cout << "[" << pal << "]" << " => " << aux->getSignificado() << endl;
    }
}

tabela::tabela(int tam){
    this->tam = tam;
    vetor = new palavra*[tam];
    for(int i = 0; i < tam; i++){
        vetor[i] = NULL;
    }
}

tabela::~tabela(){
    for(int i = 0; i < tam; i++){
        palavra *aux, *aux2;
        aux = vetor[i];
        while(aux->getProxima() != NULL){
            aux2 = aux->getProxima();
            delete aux;
            aux = aux2;
        }
        delete aux;
    }
}

int tabela::pos(string pal){
    return pal.length() % tam;
}

void tabela::incluir(string pal, string significado){
    int p = pos(pal);
    palavra* nova = new palavra(pal, significado);
    if(vetor[p] == NULL){
        vetor[p] = nova;
    }else{
        palavra* aux = vetor[p];
        while(aux->getProxima() != NULL){
            aux = aux->getProxima();
        }
        aux->setProxima(nova);
    }
}

palavra* tabela::procurar(string pal){
    int p = pos(pal);
    palavra* aux = vetor[p];

    if(aux != NULL){
        while((aux->getProxima() != NULL) and (aux->getPalavra() != pal)){
            aux = aux->getProxima();
        }
        if(aux->getPalavra() == pal){
            return aux;
        }else{
            return NULL;
        }
    }else{
        return NULL;
    }
    
}

int main(){
    tabela t(23);
    string pal;
    string sig;
    int n; 
    cin >> n; 
    for(int i = 0; i < n; i++){
        cin >> pal;
        cin.ignore();
        getline(cin, sig);
        t.incluir(pal, sig);
    }

    while(pal != "-1"){
        cin >> pal;
        if(pal != "-1")
            t.imprimir(pal);
    }
    return 0;
}