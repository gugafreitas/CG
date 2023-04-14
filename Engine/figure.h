#include "ponto.h"
#include "transformacao.h"
#include <string>
#include <vector>


using namespace std;

class Figure{
    vector<Ponto> pontos;
    //Color color;
    vector<string> modelFiles;
    vector<Figure> figuras;
    Transformacao transformacoes;

    public:
        Figure();
        Figure(vector<Ponto>, vector<string>,vector<Figure>,Transformacao);

        vector<Ponto> getPontos()
        {return pontos;}
        void setPontos(vector<Ponto> a)
        {pontos = a;}
        void addPonto(Ponto a)
        {pontos.push_back(a);}

        vector<string> getModelFiles()
        {return modelFiles;}
        void setModelFiles(vector<string> a)
        {modelFiles = a;}
        void addModelFile(string a)
        {modelFiles.push_back(a);}


        vector<Figure> getFiguras()
        {return figuras;}
        void setFiguras(vector<Figure> a)
        {figuras = a;}
        void addFigura(Figure a)
        {figuras.push_back(a);}

        Transformacao getTransform()
        {return transformacoes;}
        void setTransform(Transformacao a)
        {transformacoes = a;}

};