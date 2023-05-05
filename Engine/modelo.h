#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <list>
#include <vector>
#include <string>
#include "ponto.h"

using namespace std;

class Modelo {

    vector<float> pontos;
    GLuint vertices;
    float r;
    float g;
    float b;

public:

    Modelo();

    Modelo(vector<float> pontos, float r, float g, float b);

    vector<float> getPontos();

    float getR();

    float getG();

    float getB();

    void setPontos(vector<float> pontos);

    void setR(float r);

    void setG(float g);

    void setB(float b);

    void prepareData();

    void draw();

};