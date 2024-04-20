int  particiona(int v[], int c, int f) { // c = começo, f = fim
	int pivo = v[c], i = c + 1, j = f;
	while(i<= j){
		if (v[i] <= pivo) i++;
		else if (pivo <= v[j]) j--;
		else { // (v[i] > pivo) e (v[j] < pivo)
			swap (v[i], v[j]);
			i++;
			j--;
		}
	} // agora { == j+1
	v[c] = v[j];
	v[j] = pivo;
	return j; // retorna posição do pivo
}

void quicksort(int a[], int pos_pivo, int fim) {
	int pos_novo_pivo;
	if (pos_pivo < fim){
		pos_novo_pivo = particiona(a, pos_pivo, fim);
		quicksort(a, pos_pivo, pos_novo_pivo - 1);
		quicksort(a, pos_novo_pivo + 1, fim);
	}
}
