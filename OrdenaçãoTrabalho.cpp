#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

using namespace std;

bool intercalaBloco(ifstream auxE[2], ofstream auxS[2], int passo, int saida) {
    //consideramos inicialmente que não irá fazer nenhuma intercalação
    bool intercalou = false;
    int valor[2];
    //posicao relativa de leitura em cada um dos arquivos
    int pos[2] = {0,0};
    //variável para informar se os dados do arquivo são válidos
    //(se foram lidos do arquivo de entrada e ainda não gravados no arquivo de saida) 
    bool valido[2] = {false, false};
     //em cada passo de tamanho n lemos n dados de cada arquivo
    //e fazemos a intercalação parcial em um novo bloco de tamanho 2*n 
    //no arquivo de saída utilizado
    while((pos[0] + pos[1]) < (2 * passo)) {
        //inicialmente verificamos de há dados para ler
        if((pos[0] < passo) and (not valido[0])) {
            //tentamos ler do arquivo, verificando se a leitura foi válida
            //leitura inválida -> final de arquivo
            if(auxE[0].read((char*) &valor[0], sizeof(int))) {
                //cout << "leuarq1: " << auxE[0].tellg() << endl;
                valido[0] = true;
            } else {
                //para encerrar o while e não entrar no if novamente
                pos[0] = passo;
                //cout << "arq1 terminou" << endl;
            }
        }
        //repetimos o processo para o segundo arquivo
        if((pos[1] < passo) and (not valido[1])) {
            //tentamos ler do arquivo, verificando se a leitura foi válida
            //leitura inválida -> final de arquivo
            if(auxE[1].read((char*) &valor[1], sizeof(int))) {
                //cout << "leuarq1: " << auxE[0].tellg() << endl;
                valido[1] = true;
            } else {
                //para encerrar o while e não entrar no if novamente
                pos[1] = passo;
                //cout << "arq2 terminou" << endl;
            }
        }
        //nesse momento temos dados lidos dois arquivos
        //a não ser que um (ou ambos) tenham chegado ao fim
        //1º caso, os dois são válidos
        if(valido[0] and valido[1]) {
            //marca que intercalou
            intercalou = true;
            //gravamos o menor valor no arquivo de saida
            if(valor[0] >=valor[1]) {
                auxS[saida].write((const char*) (&valor[0]), sizeof(int));
                //dado utilizado não é mais válido, avança posição
                valido[0] = false;
                pos[0]++;
            } else {
                auxS[saida].write((const char*) (&valor[1]), sizeof(int));
                //dado utlizado não é mais válido, avança posição
                valido[1] = false;
                pos[1]++;
            }
        }
        //2º caso, apenas o primeiro dado é válido
        else if(valido[0]) {
            //marca que intercalou
            intercalou = true;
            auxS[saida].write((const char*) (&valor[0]), sizeof(int));
            //dado utilizado não é mais válido, avança posição
            valido[0] = false;
            pos[0]++;
        }
        //3º caso, apenas o segundo é valido
        else if(valido[1]) {
            //marca que intercalou
            intercalou = true;
            auxS[saida].write((const char*) (&valor[1]), sizeof(int));
            //dado utilizado não é mais válido, avança posição
            valido[1] = false;
            pos[1]++;
        }
        //se chegou aqui, termina o while na próxima iteração
        else {
            //cout << "circulando, circulando..." << endl;
        }
    } 
    return intercalou;
}

void mergeExterno(ifstream &arqEntrada, ofstream &arqSaida) {
    ofstream arqB1("arqB1.dat",ios::binary);
    ofstream arqB2("arqB2.dat",ios::binary);
    if((not arqB1) or (not arqB2)) {
        cerr << "Arquivos auxiliares não puderam ser abertos" << endl;
        exit(EXIT_FAILURE);
    }
    //posicionando ponteiro de leitura no final do arquivo
    arqEntrada.seekg(0, arqEntrada.end);
    //pegando o tamanho do arquivo
    int tamanho = arqEntrada.tellg();
    //atualizando o valor de bits para decimal
    tamanho /= 4;
    //metade do tamanho pra dividir os numeros metade pra
    //cada arquivo auxiliar
    int metade = (tamanho / 2.0) - 0.5;
    //variavel para armazenar os numeros lidos do arquivo de entrada/auxiliares
    //e para escrever no arquivo de saida/auxiliares
    int valor;
    //posicionando ponteiro de leitura no inicio
    arqEntrada.seekg(0,ios::beg);
    //lendo a primeira metade dos numeros e escrevendo no arquivo1
    for(int i = 0; i < metade; i++) {
        arqEntrada.read((char *) (&valor), sizeof(int));
        arqB1.write((char *) (&valor), sizeof(int));
    }
    //lendo a segunda metade dos numeros e escrevendo no arquivo2
    for (int i = metade; i < tamanho; i++) {
        arqEntrada.read((char *) (&valor), sizeof(int));
        arqB2.write((char *) (&valor), sizeof(int));
    }
    //processo encerrado, fechando os arquivos
    arqB1.close();
    arqB2.close();
    arqEntrada.close();
     //arquivos auxiliares
    ifstream auxEntrada[2];
    ofstream auxSaida[2];
    //variáveis de controle
    int passo = 1;
    bool ida = true;
    bool ultimo[2];
    //laço principal
    while(passo <= tamanho) {
        if(ida) {
            auxEntrada[0].open("arqB1.dat",ios::binary);
            auxEntrada[1].open("arqB2.dat",ios::binary);
            auxSaida[0].open("arqC1.dat",ios::binary);
            auxSaida[1].open("arqC2.dat",ios::binary);
        } else {
            auxEntrada[0].open("arqC1.dat",ios::binary);
            auxEntrada[1].open("arqC2.dat",ios::binary);
            auxSaida[0].open("arqB1.dat",ios::binary);
            auxSaida[1].open("arqB2.dat",ios::binary);
        }
        if((not auxEntrada[0]) or (not auxEntrada[1]) or (not auxSaida[0]) or (not auxSaida[1])) {
            cerr << "Arquivos auxiliares não puderam ser abertos" << endl;
            exit(EXIT_FAILURE);
        }
        //enquanto não chegar ao final dos arquivos de entrada
        //vai intercalando os blocos
        while((not auxEntrada[0].eof()) and (not auxEntrada[1].eof())) {
            ultimo[0] = intercalaBloco(auxEntrada, auxSaida, passo, 0);
            ultimo[1] = intercalaBloco(auxEntrada, auxSaida, passo, 1);
        }
        //fecha arquivos para permitir troca (escrita <-> leitura) na próxima iteração
        auxEntrada[0].close();
        auxEntrada[1].close();
        auxSaida[0].close();
        auxSaida[1].close();            
        //prepara próxima iteração, invertendo arquivos e dobrando tamanho do passo
        ida = not(ida);
        passo *= 2;
    }
    //merge terminado, agora lemos do arquivo auxiliar para arquivo de saída
    ifstream auxEnt;
    //identifica o arquivo auxiliar com dados ordenados
    if(ida) {
        if(ultimo[0]) {
            auxEnt.open("arqB1.dat",ios::binary);
        } else {
            auxEnt.open("arqB2.dat",ios::binary);
        }
    } else {
        if(ultimo[0]) {
            auxEnt.open("arqC1.dat",ios::binary);
        } else {
            auxEnt.open("arqC2.dat",ios::binary);
        }
    }
    if(not auxEnt) {
        cerr << "Arquivos auxiliares não puderam ser abertos" << endl;
        exit(EXIT_FAILURE);
    }
    while(auxEnt.read((char *) (&valor), sizeof(int))) {
        arqSaida.write((const char*) (&valor), sizeof(int));
    }
    auxEnt.close();
    //cereja do bolo: apagar arquivos auxiliares
    remove("arqB1.dat");
    remove("arqB2.dat");
    remove("arqC1.dat");
    remove("arqC2.dat");
}

int main() {
    //Arquivo para ser ordenado
    ifstream entrada("Ordenar.dat",ios::binary);
    //Arquivo onde vai ser salvo os dados ordenados
    ofstream saida("arquivoOrdenado.dat",ios::binary);
    if(not entrada) {
        cerr << "Arquivo de entrada não pode ser aberto" << endl;
        exit(EXIT_FAILURE);
    }
    if(not saida) {
        cerr << "Arquivo de saída não pode ser aberto" << endl;
        exit(EXIT_FAILURE);
    }
    mergeExterno(entrada, saida);
    entrada.close();
    saida.close();
    
    //Testando se os dados foram ordenados corretamente
    //lendo do arquivo e imprimindo
    ifstream Leitura("arquivoOrdenado.dat",ios::binary);
    Leitura.seekg(0, Leitura.end);
    int tam = Leitura.tellg();
    tam /= 4;
    int* valores = new int[tam];
    Leitura.seekg(0, Leitura.beg);
    Leitura.read((char *) (valores), tam * sizeof(int));
    Leitura.close();
    for (int i = 0; i < tam; i++) {
        cout << valores[i] << endl;
    }
    
   return 0;
}
