#include "transform.h"

Transform::Transform(){
    translacao = Traslacao::Translacao();
    rotacao = Rotacao::Rotacao();
    escala = Escala::Escala();
}

Transform::Transform(Translacao a,Rotacao b,Escala c){
    translacao = a;
    rotacao = b;
    escala = c;
}