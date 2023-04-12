#include "translacao.h"
#include "rotacao.h"
#include "escala.h"
#include "cor.h"

class Transform{
    Translacao translacao;
    Rotacao rotacao;
    Escala escala;

    public:
        Transform();
        Transform(Translacao a,Rotacao b,Escala c);

        Translacao getTranslacao()
        {return translacao;}
        void setTranslacao(Translacao a)
        {translacao = a:}

        Rotacao getRotacao()
        {return rotacao;}
        void setRotacao(Rotacao a)
        {rotacao = a;}

        Escala getEscala()
        {return escala;}
        void setEscala(Escala a)
        {escala = a;}
};