#include "transformacao.h"

using namespace std;

Transformacao::Transformacao(){
    rot_Tempo = 0;
    rot_Angulo = 0;
    rot_X = 0;
    rot_Y = 0;
    rot_Z = 0;

    //translação
    trans_tempo = 0;
    trans_Align = true;
    pontos = new vector<Ponto>;
    pontosCurva = new vector<Ponto>;
    trans_X = 0;
    trans_Y = 0;
    trans_Z = 0;

    //escala
    esc_X = 0;
    esc_Y = 0;
    esc_Z = 0;
}

Transformacao::Transformacao(float a,float b,float c,float d,float e,float f,bool al,vector<Ponto> g,vector<Ponto> h,float i,float j,float k,float l,float m,float n){
    rot_Tempo = a;
    rot_Angulo = b;
    rot_X = c;
    rot_Y = d;
    rot_Z = e;

    //translação
    trans_Tempo = f;
    trans_Align = al;
    pontos = g;
    pontosCurva = h;
    trans_X = i;
    trans_Y = j;
    trans_Z = k;

    //escala
    esc_X = l;
    esc_Y = m;
    esc_Z = n;
}

float getRotTempo()
{return rot_Tempo;}
void setRotTempo(float a)
{rot_Tempo=a;}

float getRotAngulo()
{return rot_Angulo;}
void setRotAngulo(float a)
{rot_Angulo=a;}

float getRotX()
{return rot_X;}
void setRotX(float a)
{rot_X=a;}

float getRotY()
{return rot_Y;}
void setRotY(float a)
{rot_Y=a;}

float getRotZ()
{return rot_Z;}
void setRotZ(float a)
{rot_Z=a;}



float getTransTempo()
{return trans_Tempo;}
void setTransTempo(float a)
{trans_Tempo=a;}

bool getTransAlign()
{return trans_Align;}
void setTransAlign(bool a)
{trans_Align=a;}

vector<Ponto> getPontos()
{return pontos;}
void setPontos(vector<Ponto> a)
{pontos = a;}

vector<Ponto> getPontosCurva()
{return pontosCurva;}
void setPontosCurva(vector<Ponto> a)
{pontosCurva = a;}

float getTrans_X()
{return trans_X;}
void setTrans_X(float a)
{trans_X=a;}
void sumTrans_X(float a)
{trans_X=trans_X+a;}

float getTrans_Y()
{return trans_Y;}
void setTrans_Y(float a)
{trans_Y=a;}
void sumTrans_Y(float a)
{trans_Y=trans_Y+a;}

float getTrans_Z()
{return trans_Z;}
void setTrans_Z(float a)
{trans_Z=a;}
void sumTrans_Z(float a)
{trans_Z=trans_Z+a;}



        


float getEscalaX()
{return esc_X;}
void setEscalaX(float a)
{esc_X=a;}
void sumEscalaX(float a)
{esc_X=esc_X*a;}

float getEscalaY()
{return esc_Y;}
void setEscalaY(float a)
{esc_Y=a;}
void sumEscalaY(float a)
{esc_Y=esc_Y*a;}

float getEscalaZ()
{return esc_Z;}
void setEscalaZ(float a)
{esc_Z=a;}
void sumEscalaZ(float a)
{esc_Z=esc_Z*a;}

/*
void Translacao::buildRotMatrix(float* x, float* y, float* z, float* m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void Translacao::cross(float* a, float* b, float* res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}


void Translacao::normalize(float* a) {

    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}

void Translacao::getCatmullRomPoint(float t, Ponto p0, Ponto p1, Ponto p2, Ponto p3, float* pos, float* deriv) {

    float M[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
                    { 1.0f, -2.5f,  2.0f, -0.5f},
                    {-0.5f,  0.0f,  0.5f,  0.0f},
                    { 0.0f,  1.0f,  0.0f,  0.0f} };

    float P[4][3] = { {p0.getX(),p0.getY(), p0.getZ()},
                    {p1.getX(), p1.getY(), p1.getZ()},
                    {p2.getX(), p2.getY(), p2.getZ()},
                    {p3.getX(), p3.getY(), p3.getZ()} };

    // A = M * P

    float A[4][3] = { 0 };

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 4; k++) A[i][j] += M[i][k] * P[k][j];

    float T[4] = { t * t * t, t * t, t, 1 };

    // pos = T * A

    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 0;

    for (int j = 0; j < 3; j++)
        for (int k = 0; k < 4; k++) pos[j] += T[k] * A[k][j];

    deriv[0] = 0;
    deriv[1] = 0;
    deriv[2] = 0;

    float Tderiv[4] = { 3 * t * t, 2 * t, 1, 0 };

    for (int j = 0; j < 3; j++)
        for (int k = 0; k < 4; k++) deriv[j] += Tderiv[k] * A[k][j];

}


void Translacao::getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, vector<Ponto> pontos) {

    int tamLoop = pontos.size(); // Points that make up the loop for catmull-rom interpolation
    float t = gt * tamLoop; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + tamLoop - 1) % tamLoop;
    indices[1] = (indices[0] + 1) % tamLoop;
    indices[2] = (indices[1] + 1) % tamLoop;
    indices[3] = (indices[2] + 1) % tamLoop;

    getCatmullRomPoint(t, pontos[indices[0]], pontos[indices[1]], pontos[indices[2]], pontos[indices[3]], pos, deriv);
}

void Translacao::buildCurve(float* pos, float* deriv) {

    for (float t = 0; t < 1; t += 0.001) {

        getGlobalCatmullRomPoint(t, pos, deriv, pontos);
        pontosCurva.push_back(*new Ponto(pos[0], pos[1], pos[2]));
    }

}

void Translacao::drawCatmullRomCurve() {

    int tam = pontosCurva.size();

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < tam; i++) {
        Ponto p = pontosCurva[i];
        glVertex3f(p.getX(), p.getY(), p.getZ());
    }

    glEnd();
}

void Translacao::alinhamentoCurva(float* deriv) {

    float Z[3];
    float Y[3] = { 0,1,0 };
    float X[3] = { deriv[0],deriv[1],deriv[2] };
    float m[16];

    cross(X, Y, Z);
    cross(Z, X, Y);

    normalize(X);
    normalize(Y);
    normalize(Z);

    buildRotMatrix(X, Y, Z, m);

    glMultMatrixf((float*)m);
}

void Translacao::draw() {
    float pos[3];
    float deriv[3];
    float te, gt;
    if (tempo != 0 && pontos.size() > 3) {
        te = glutGet(GLUT_ELAPSED_TIME) % (int)(tempo * 1000);
        gt = te / (tempo * 1000);
        buildCurve(pos, deriv);
        drawCatmullRomCurve();
        getGlobalCatmullRomPoint(gt, pos, deriv, pontos);
        pontosCurva.clear();
        glTranslatef(pos[0], pos[1], pos[2]);
        alinhamentoCurva(deriv);
    }
}

//ESCALA

Escala::Escala() {
    x = 1;
    y = 1;
    z = 1;
}

Escala::Escala(float x1, float y1, float z1) {
    x = x1;
    y = y1;
    z = z1;
}

float Escala::getX() {
    return x;
}

float Escala::getY() {
    return y;
}

float Escala::getZ() {
    return z;
}

void Escala::setX(float a) {
    x = a;
}

void Escala::setY(float b) {
    y = b;
}

void Escala::setZ(float c) {
    z = c;
}
*/


    // Transformacao::Transformacao(){
    //     translacaoX = 0;
    //     translacaoY = 0;
    //     translacaoZ = 0;
    //     rotacaoX = 0;
    //     rotacaoY = 0;
    //     rotacaoZ = 0;
    //     rotacaoAngle = 0;
    //     escalaX = 1;
    //     escalaY = 1;
    //     escalaZ = 1;
    // }

    // Transformacao::Transformacao(float a,float b,float c,float d,float e,float f,float g,float h,float i,float j){
    //     translacaoX = a;
    //     translacaoY = b;
    //     translacaoZ = c;
    //     rotacaoX = d;
    //     rotacaoX = e;
    //     rotacaoX = f;
    //     rotacaoAngle = g;
    //     escalaX = h;
    //     escalaY = i;
    //     escalaZ = j;
    // }