#include <iostream>				// Ler N registros
#include <fstream>				// Aloca-los dinamicamente em um vetor
#include <cstring>				// Ordenar vetor pela chave (crescente)
using namespace std;			// Armazenar em arquivo binário escolhido pelo usuario
								// Realizar busca binaria de um nome a partir de uma chave, return -1 se não encontrar
struct dados
{
	string nome;
	int chave;
};

int divisor(int vetor[], int inicio, int final)
{
	int pivot = vetor[inicio];
	int i = inicio + 1;
	int j = final;
	int aux;
	while(i<=j)
	{
		if(vetor[i]<=pivot){i++;}
		else if(pivot<=vetor[j]){j--;}
		else
		{
			aux = vetor[i];
			vetor[i] = vetor[j];
			vetor[j] = aux;
			i++;
			j--;
		}
	}
	vetor[inicio] = vetor[j];
	vetor[j] = pivot;
	return j;
}


void quickSort(int vetor[], int pos_pivot, int final)
{
	int pos_novo_pivot;
	if(pos_pivot<final)
	{
		pos_novo_pivot = divisor(vetor, pos_pivot, final);
		quickSort(vetor, pos_pivot, pos_novo_pivot-1);
		quickSort(vetor, pos_novo_pivot+1, final);
	}
	
}

int main () 
{
	int N;
	cin >> N;							// coleto numero de registros
	dados* pessoa = new dados[N];		// alocação dinâmica de vetor de registros de N elementos
	for(int i = 0; i<N; i++)			// Coleta dos dados dos registros
	{
		cin >> pessoa[i].nome;
		cin >> pessoa[i].chave;
	}
	
	int vetorChave[N];
	string vetorNome[N];
	for(int i = 0; i<N; i++)			// Crio vetor de inteiros só com a chave
	{
		vetorChave[i] = pessoa[i].chave;
		vetorNome[i] = pessoa[i].nome;
	}
	
	for(int i = 0; i<N; i++){cout << vetorChave[i] << " ";}
	cout << endl;
	for(int i = 0; i<N; i++){cout << vetorNome[i] << " ";}
	cout << endl;
	
	quickSort(vetorChave, 0, N-1);										// Ordeno o vetor
	
	for(int i = 0; i<N; i++){cout << vetorChave[i] << " ";}
	cout << endl;
	
	
	for(int i = 0; i<N; i++)
	{
		cout << pessoa[i].chave << " " << pessoa[i].nome << endl;
		
	}
	cout << endl;
	
	string aux;
	for(int i = 0; i<N; i++)
    {
 	    for(int j = 0; j<N;j++)
  		{	
    		if(vetorChave[i] == pessoa[j].chave)				// vetorChave: 0 1 2 3 4
    		{
				aux = pessoa[i].nome;											// registros: 1 3 4 0 2
    			pessoa[i].nome = pessoa[j].nome;
    			pessoa[j].nome = aux;
			}
  		}
	}
	
	for(int i = 0; i<N; i++)
	{
		cout << pessoa[i].chave << " " << pessoa[i].nome << endl;
		
	}
	cout << endl;

//	int aux;
//	string nomeArq;						
//	cin >> nomeArq;								// Coleto nome do arquivo
//	ofstream Arq(nomeArq.c_str());				// Crio um arquivo com esse nome
//	for(int i = 0; i<N; i++)
//	{
//		aux = vetorChave[i];
//		Arq.write(,5);
//	}

	
	
	return 0;
}




