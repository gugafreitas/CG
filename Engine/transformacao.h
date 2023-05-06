#ifndef CLASS2_TRANSFORMACOES_H
#define CLASS2_TRANSFORMACOES_H

#include "ponto.h"
#include <vector>
//#include <GL/glut.h>

using namespace std;

class Transformacao{
    //rotação
    float rot_Tempo;
    float rot_Angulo;
    float rot_X;
    float rot_Y;
    float rot_Z;

    //translação
    float tempo;
    bool align;
    vector <Ponto> pontos;
    vector <Ponto> pontosCurva;
    float trans_X;
    float trans_Y;
    float trans_Z;

    //escala
    float esc_X;
    float esc_Y;
    float esc_Z;

public:

    Transformacao();

    Transformacao(float,float,float,float,float,float,bool,vector<Ponto>,vector<Ponto>,float,float,float,float,float,float);

    Transformacao(float, vector<Ponto>);

    float getRotTempo();
    float getRotAngulo();
    float getRotX();
    float getRotY();
    float getRotZ();

    float getTransTempo();
    bool getTransAlign();
    vector<Ponto> getTransPontos();
    vector<Ponto> getTransPontosCurva();
    float getTrans_X();
    float getTrans_Y();
    float getTrans_Z();

    float getEscalaX();
    float getEscalaY();
    float getEscalaZ();

    void setRotTempo(float);
    void setRotAngulo(float);
    void setRot_X(float);
    void setRot_Y(float);
    void setRot_Z(float);

    void setTransTempo(float);
    void setTransAlign(bool);
    void setTransPontos(vector<Ponto>);
    void setTransPontosCurva(vector<Ponto>);
    void setTrans_X(float);
    void setTrans_Y(float);
    void setTrans_Z(float);
    void sumTrans_X(float);
    void sumTrans_Y(float);
    void sumTrans_Z(float);

    void setEscalaX(float);
    void setEscalaY(float);
    void setEscalaZ(float);
/*
    void buildRotMatrix(float*, float*, float*, float*);

    void cross(float*, float*, float*);

    void normalize(float*);

    void getCatmullRomPoint(float, Ponto, Ponto, Ponto, Ponto, float*, float*);

    void getGlobalCatmullRomPoint(float, float*, float*, vector<Ponto>);

    void buildCurve(float*, float*);

    void alinhamentoCurva(float*);

    void drawCatmullRomCurve();

    void draw();
*/
};

#endif //CLASS2_TRANSFORMACOES_H