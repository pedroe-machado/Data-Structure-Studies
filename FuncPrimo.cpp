#include<iostream>

using namespace std;

bool primo(int num){
	if(num==1)
		return true;
		
	bool conclusao=true;
	int divisor=2;
	
	while((divisor<num) and conclusao){
		conclusao = (num%divisor!=0);
		divisor++;
	}
	return conclusao;
};
