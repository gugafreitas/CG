#include "transformacao.h"

using namespace std;

    Transformacao::Transformacao(){
        translacaoX = 0;
        translacaoY = 0;
        translacaoZ = 0;
        rotacaoX = 0;
        rotacaoY = 0;
        rotacaoZ = 0;
        rotacaoAngle = 0;
        escalaX = 1;
        escalaY = 1;
        escalaZ = 1;
    }

    Transformacao::Transformacao(float a,float b,float c,float d,float e,float f,float g,float h,float i,float j){
        translacaoX = a;
        translacaoY = b;
        translacaoZ = c;
        rotacaoX = d;
        rotacaoX = e;
        rotacaoX = f;
        rotacaoAngle = g;
        escalaX = h;
        escalaY = i;
        escalaZ = j;
    }