/* MergeSort Externo
 *
 * by Joukim, 2017 - Estrutura de Dados (GCC216)
 * Modificado por Bruno Schneider em dezembro de 2018.
 */

#include <iostream>
#include <fstream>
#include <cstdio> // para remover arquivos
#include <cstdlib>

using namespace std;

// estrutura a ser lida do arquivo
struct Dado {
    int chave1;
    int chave2;
    float valor1;
    char campo1[8];
    char campo2[20];
};

bool intercalaBloco(ifstream auxE[2], ofstream auxS[2], int passo, int saida) {
    // consideramos inicialmente que nÃ£o irÃ¡ fazer nenhuma intercalaÃ§Ã£o
    bool intercalou = false;
    Dado dados[2];
    // posiÃ§Ã£o relativa de leitura em cada um dos arquivos
    int pos[2] = {0,0};

    // variÃ¡vel para informar se os dados do arquivo sÃ£o vÃ¡lidos
    // (se foram lidos do arquivo de entrada e ainda nÃ£o gravados
    // no arquivo de saÃ­da)
    bool valido[2] = {false,false};

    // em cada passo de tamanho n lemos n dados de cada arquivo
    // e fazemos a intercalaÃ§Ã£o parcial em um novo bloco de
    // tamanho 2*n no arquivo de saÃ­da utilizado
    while ( (pos[0] + pos[1]) < (2 * passo) ) {
        // inicialmente verificamos se hÃ¡ dados para ler
        if ( (pos[0] < passo) and (not valido[0]) ) {
            // tentamos ler do arquivo, verificando se a leitura foi vÃ¡lida
            // leitura invÃ¡lida -> final de arquivo
            if ( auxE[0].read((char *) &dados[0], sizeof(Dado)) ) {
                // cout << "leu arq1: " << auxE[0].tellg() << endl;
                valido[0] = true;
            }
            else {
                // para encerrar o while e nÃ£o entrar no if novamente
                pos[0] = passo;
                // cout << "arq1 terminou" << endl;
            }
        }
        // repetimos o processo para o segundo arquivo
        if ( (pos[1] < passo) and (not valido[1]) ) {
            // tentamos ler do arquivo, verificando se a leitura foi vÃ¡lida
            // leitura invÃ¡lida -> final de arquivo
            if ( auxE[1].read((char *) &dados[1], sizeof(Dado)) ) {
                // cout << "leu arq2: " << auxE[1].tellg() << endl;
                valido[1] = true;
            } else {
                // para encerrar o while e nÃ£o entrar no if novamente
                pos[1] = passo;
                // cout << "arq2 terminou" << endl;
            }
        }

        // nesse momento temos dados lidos dos dois arquivos
        // a nÃ£o ser que um (ou ambos) tenham chegado ao fim

        // 1o caso, os dois dados sÃ£o vÃ¡lidos
        if ( valido[0] and valido[1] ) {
            // marca que intercalou
            intercalou = true;
            // gravamos o menor valor no arquivo de saida
            if (dados[0].chave1 <= dados[1].chave1) {
                auxS[saida].write((const char*) (&dados[0]), sizeof(Dado));
                // dado utilizado nÃ£o Ã© mais vÃ¡lido, avanÃ§a posiÃ§Ã£o
                valido[0] = false;
                pos[0]++;
            } else {
                auxS[saida].write((const char*) (&dados[1]), sizeof(Dado));
                // dado utilizado nÃ£o Ã© mais vÃ¡lido, avanÃ§a posiÃ§Ã£o
                valido[1] = false;
                pos[1]++;
            }
        }
        // 2o caso, apenas o primeiro dado Ã© vÃ¡lido
        else if ( valido[0] ) {
            // marca que intercalou
            intercalou = true;
            auxS[saida].write((const char*) (&dados[0]), sizeof(Dado));
            // dado utilizado nÃ£o Ã© mais vÃ¡lido, avanÃ§a posiÃ§Ã£o
            valido[0] = false;
            pos[0]++;
        }
        // 3o caso, apenas o segundo dado Ã© vÃ¡lido
        else if (valido[1] ) {
            // marca que intercalou
            intercalou = true;
            auxS[saida].write((const char*) (&dados[1]), sizeof(Dado));
            // dado utilizado nÃ£o Ã© mais vÃ¡lido, avanÃ§a posiÃ§Ã£o
            valido[1] = false;
            pos[1]++;
        }
        // se chegou aqui, termina o while na prÃ³xima iteraÃ§Ã£o
        else {
            // cout << "circulando, circulando... " << endl;
        }
    }
    return intercalou;
}


void mergeexterno(ifstream &arqEntrada, ofstream &arqSaida) {
    ofstream arqB1 ("arqB1.dat");
    ofstream arqB2 ("arqB2.dat");

    if ( (not arqB1) or (not arqB2) ) {
        cerr << "Arquivos auxiliares nÃ£o puderam ser abertos" << endl;
        exit(EXIT_FAILURE);
    }

    Dado umDado;

    // posicionando ponteiro de leitura no final do arquivo
    arqEntrada.seekg(0, ios::end);
    // obtendo a posiÃ§Ã£o final do arquivo
    int tamanho = int(arqEntrada.tellg());
    // dado o tamanho do arquivo, sabe-se quantos registros no arquivo
    int numRegistros = int(tamanho / sizeof(Dado));
    // metade do nÃºmero de registros (arredondado para cima)
    int metade = int((numRegistros/2.0) + 0.5);

    // posicionando ponteiro de leitura no inÃ­cio do arquivo
    arqEntrada.seekg(0, ios::beg);

    // copiando os dados para dois arquivos auxiliares
    for (int i = 0; i < metade; i++) {
        arqEntrada.read((char *) &umDado, sizeof(Dado));
        arqB1.write((char *) &umDado, sizeof(Dado));
    }
    for (int i = metade; i < numRegistros; i++) {
        arqEntrada.read((char *) &umDado, sizeof(Dado));
        arqB2.write((char *) &umDado, sizeof(Dado));
    }

    // finalizaÃ§Ã£o da primeira etapa
    arqB1.close();
    arqB2.close();
    arqEntrada.close();

    // arquivos auxiliares
    ifstream auxEntrada[2];
    ofstream auxSaida[2];

    // variÃ¡veis de controle
    int passo = 1;
    bool ida = true;
    bool ultimo[2];

    // laÃ§o principal
    while (passo <= numRegistros) {
        if (ida) {
            auxEntrada[0].open("arqB1.dat");
            auxEntrada[1].open("arqB2.dat");
            auxSaida[0].open("arqC1.dat");
            auxSaida[1].open("arqC2.dat");
        } else {
            auxEntrada[0].open("arqC1.dat");
            auxEntrada[1].open("arqC2.dat");
            auxSaida[0].open("arqB1.dat");
            auxSaida[1].open("arqB2.dat");
        }

        if ( (not auxEntrada[0])
              or (not auxEntrada[1])
              or (not auxSaida[0])
              or (not auxSaida[1]) ) {
            cerr << "Arquivos auxiliares nÃ£o puderam ser abertos" << endl;
            exit(EXIT_FAILURE);
        }
        // enquanto nÃ£o chegar ao final dos arquivos de entrada
        // vai intercalando os blocos
        while ((not auxEntrada[0].eof()) and (not auxEntrada[1].eof())) {
            ultimo[0] = intercalaBloco(auxEntrada, auxSaida, passo, 0);
            ultimo[1] = intercalaBloco(auxEntrada, auxSaida, passo, 1);
        }

        // fecha arquivos para permitir troca (escrita <-> leitura)
        // na prÃ³xima iteraÃ§Ã£o
        auxEntrada[0].close();
        auxEntrada[1].close();
        auxSaida[0].close();
        auxSaida[1].close();

        // prepara prÃ³xima iteraÃ§Ã£o, invertendo arquivos
        // e dobrando tamanho do passo
        ida = not(ida);
        passo *= 2;

    }

    // merge terminado, agora lemos do arquivo auxiliar
    // para arquivo de saÃ­da
    ifstream auxEnt;

    // identifica o arquivo auxiliar com dados ordenados
    if (ida) {
        if (ultimo[0]) {
            auxEnt.open("arqB1.dat");
        } else {
            auxEnt.open("arqB2.dat");
        }
    } else {
        if (ultimo[0]) {
            auxEnt.open("arqC1.dat");
        } else {
            auxEnt.open("arqC2.dat");
        }
    }

    if (not auxEnt) {
        cerr << "Arquivos auxiliar nÃ£o pode ser aberto" << endl;
        exit(EXIT_FAILURE);
    }

    while (auxEnt.read((char*) (&umDado), sizeof(Dado)) ) {
        arqSaida.write((const char*) (&umDado), sizeof(Dado));
    }

    auxEnt.close();

    // cereja do bolo: apagar arquivos auxiliares
    remove("arqB1.dat");
    remove("arqB2.dat");
    remove("arqC1.dat");
    remove("arqC2.dat");
}




int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso:" << endl;
        cerr << argv[0] << " arquivoEntrada arquivoSaida" << endl;
        exit(EXIT_FAILURE);
    }
    ifstream entrada(argv[1]);
    ofstream saida(argv[2]);

    if (not entrada) {
        cerr << "Arquivo de entrada nÃ£o pode ser aberto" << endl;
        exit(EXIT_FAILURE);
    }
    if (not saida) {
        cerr << "Arquivo de saÃ­da nÃ£o pode ser aberto" << endl;
        exit(EXIT_FAILURE);
    }

    mergeexterno(entrada,saida);

    entrada.close();
    saida.close();
}