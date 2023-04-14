#include "figure.h"

using namespace std;

    Figure::Figure(){
        pontos = vector<Ponto>();
        //color = Color::Color();
        figuras = vector<Figure>();
        modelFiles = vector<string>();
        transformacoes = Transformacao::Transformacao();
    }

    Figure::Figure(vector<Ponto> a, vector<string> b, vector<Figure> c, Transformacao d){
        pontos = a;
        modelFiles = b;
        figuras = c;
        transformacoes = d;
    }