#include "headers/modelo.h"


using namespace std;

Modelo::Modelo() {
    r = 0.0f;
    g = 0.0f;
    b = 1.0f;
}

Modelo::Modelo(vector<float> pontos1, float r1, float g1, float b1) {
    pontos = pontos1;
    r = r1;
    g = g1;
    b = b1;
}

vector<float> Modelo::getPontos() {
    return pontos;
}

float Modelo::getR() {
    return r;
}

float Modelo::getG() {
    return g;
}

float Modelo::getB() {
    return b;
}

void Modelo::setPontos(vector<float> pontos1) {

    pontos = pontos1;
    pontos1.clear();
}

void Modelo::setR(float r1) {
    r = r1;
}

void Modelo::setG(float g1) {
    g = g1;
}

void Modelo::setB(float b1) {
    b = b1;
}


void Modelo::prepareData() {

    glGenBuffers(1, &vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * pontos.size(), pontos.data(), GL_STATIC_DRAW);

}


void Modelo::draw() {

    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, pontos.size() / 3);

}