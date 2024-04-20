#include<iostream>
#include<cmath>

using namespace std;

int main(){
	
	int x, y, mdc, maior, menor;
	cin >> x >> y;
	
	if (x>=y){
		maior = x;
		menor = y;
	} else {
		maior = y;
		menor = x;
	}
	
	while ((maior%menor)!=0){
		mdc = maior%menor;
		maior = menor;
		menor = mdc;
	}
	
	cout << "O maior divisor comum = " << mdc << endl;
	
}

