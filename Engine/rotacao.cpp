#include "rotacao.h"

Rotacao::Rotacao(){
    ex = 0;
	ey = 0;
	ez = 0;
	angle = 0;	

};

Rotacao::Rotacao(float a, float b, float c, float d){
    ex = a;
	ey = b;
	ez = c;
	angle = d;
	
};