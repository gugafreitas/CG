#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>

#include <math.h>
#include "tinyxml2.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <string.h>
#include "figure.h"


using namespace tinyxml2;
using namespace std;


float R = 1, G = 1, B = 1;
float size;
float a = 1, w = 1;
float camX = 0, camY = 0, camZ = 0;
float zx = 6, zy = 6, zz = 6;
int xinicio, yinicio , tracking = 0;
int k = 5 , alpha = 0 , beta = 0;
vector<Ponto> vertices; //vetor com os pontos lidos do ficheiro
int linha = GL_LINE;
int nOfFiles;

struct World {
    int windowWidth;
    int windowHeight;
    float cameraPosX;
    float cameraPosY;
    float cameraPosZ;
    float cameraLookAtX;
    float cameraLookAtY;
    float cameraLookAtZ;
    float cameraUpX;
    float cameraUpY;
    float cameraUpZ;
    float cameraFov;
    float cameraNear;
    float cameraFar;
    vector<Figure> models;
}xml;

// void lerXML(string ficheiro) {
//     XMLDocument doc;
//     if (doc.LoadFile(ficheiro.c_str()) != XML_SUCCESS) {
//         std::cerr << "Error loading XML file: " << doc.GetErrorStr1() << std::endl;
//         return;
//     }

//     XMLElement* root = doc.RootElement();

//     XMLElement* windowElem = root->FirstChildElement("window");
//     if (windowElem) {
//         windowElem->QueryIntAttribute("width", &xml.windowWidth);
//         windowElem->QueryIntAttribute("height", &xml.windowHeight);
//     }

//     XMLElement* cameraElem = root->FirstChildElement("camera");
//     if (cameraElem) {
//         XMLElement* posElem = cameraElem->FirstChildElement("position");
//         if (posElem){
//             posElem->QueryFloatAttribute("x", &xml.cameraPosX);
//             posElem->QueryFloatAttribute("y", &xml.cameraPosY);
//             posElem->QueryFloatAttribute("z", &xml.cameraPosZ);
//         }

//         XMLElement* lookAtElem = cameraElem->FirstChildElement("lookAt");
//         if (lookAtElem) {
//             lookAtElem->QueryFloatAttribute("x", &xml.cameraLookAtX);
//             lookAtElem->QueryFloatAttribute("y", &xml.cameraLookAtY);
//             lookAtElem->QueryFloatAttribute("z", &xml.cameraLookAtZ);
//         }

//         XMLElement* upElem = cameraElem->FirstChildElement("up");
//         if (upElem) {
//             upElem->QueryFloatAttribute("x", &xml.cameraUpX);
//             upElem->QueryFloatAttribute("y", &xml.cameraUpY);
//             upElem->QueryFloatAttribute("z", &xml.cameraUpZ);
//         }

//         XMLElement* projElem = cameraElem->FirstChildElement("projection");
//         if (projElem) {
//             projElem->QueryFloatAttribute("fov", &xml.cameraFov);
//             projElem->QueryFloatAttribute("near", &xml.cameraNear);
//             projElem->QueryFloatAttribute("far", &xml.cameraFar);
//         }
//     }

//     XMLElement* groupElem = root->FirstChildElement("group");
//     while(groupElem){
//         Figure figAux;
//         XMLElement* transformElem = groupElem->FirstChildElement("transform");
//         if(transformElem){
//             XMLElement* scaleElem = transformElem->FirstChildElement("scale");
//             Transformacao auxT;
//             if(scaleElem){
//                 float xe, ye, ze;
//                 scaleElem->QueryFloatAttribute("x", &xe);
//                 scaleElem->QueryFloatAttribute("y", &ye);
//                 scaleElem->QueryFloatAttribute("z", &ze);

//                 auxT.setEscalaX(xe);
//                 auxT.setEscalaY(ye);
//                 auxT.setEscalaZ(ze);
//             }

//             XMLElement* translateElem = transformElem->FirstChildElement("translate");
//             if(translateElem){
//                 float xt, yt, zt;
//                 translateElem->QueryFloatAttribute("x", &xt);
//                 translateElem->QueryFloatAttribute("y", &yt);
//                 translateElem->QueryFloatAttribute("z", &zt);

//                 auxT.setTranslacaoX(xt);
//                 auxT.setTranslacaoY(yt);
//                 auxT.setTranslacaoZ(zt);
//             }

//             XMLElement* rotateElem = transformElem->FirstChildElement("rotate");
//             if(rotateElem){
//                 float xr, yr, zr, ar;
//                 rotateElem->QueryFloatAttribute("x", &xr);
//                 rotateElem->QueryFloatAttribute("y", &yr);
//                 rotateElem->QueryFloatAttribute("z", &zr);
//                 rotateElem->QueryFloatAttribute("angle", &ar);

//                 auxT.setRotacaoAngle(ar);
//                 auxT.setRotacaoX(xr);
//                 auxT.setRotacaoY(yr);
//                 auxT.setRotacaoZ(zr);
//             }
//             figAux.setTransform(auxT);
//         }

//         XMLElement* modelsElem = groupElem->FirstChildElement("models");
//         if(modelsElem){
//             XMLElement* modelElem = modelsElem->FirstChildElement("model");
//             while(modelElem){
//                 string filePath = modelElem->Attribute("file");
//                 figAux.addModelFile(filePath);
//				   modelElem = modelElem->NextSiblingElement();
//             }
//         }

//         XMLElement* groupElem1 = groupElem->FirstChildElement("group");
//         while(groupElem1){
//             Figure figAux1;
//             XMLElement* transformElem1 = groupElem1->FirstChildElement("transform");
//             if(transformElem1){
//                 XMLElement* scaleElem1 = transformElem1->FirstChildElement("scale");
//                 Transformacao auxT1;
//                 if(scaleElem1){
//                     float xe, ye, ze;
//                     scaleElem1->QueryFloatAttribute("x", &xe);
//                     scaleElem1->QueryFloatAttribute("y", &ye);
//                     scaleElem1->QueryFloatAttribute("z", &ze);

//                     auxT1.setEscalaX(xe);
//                     auxT1.setEscalaY(ye);
//                     auxT1.setEscalaZ(ze);
//                 }

//                 XMLElement* translateElem1 = transformElem1->FirstChildElement("translate");
//                 if(translateElem1){
//                     float xt, yt, zt;
//                     translateElem1->QueryFloatAttribute("x", &xt);
//                     translateElem1->QueryFloatAttribute("y", &yt);
//                     translateElem1->QueryFloatAttribute("z", &zt);

//                     auxT1.setTranslacaoX(xt);
//                     auxT1.setTranslacaoY(yt);
//                     auxT1.setTranslacaoZ(zt);
//                 }

//                 XMLElement* rotateElem1 = transformElem1->FirstChildElement("rotate");
//                 if(rotateElem1){
//                     float xr, yr, zr, ar;
//                     rotateElem1->QueryFloatAttribute("x", &xr);
//                     rotateElem1->QueryFloatAttribute("y", &yr);
//                     rotateElem1->QueryFloatAttribute("z", &zr);
//                     rotateElem1->QueryFloatAttribute("angle", &ar);

//                     auxT1.setRotacaoAngle(ar);
//                     auxT1.setRotacaoX(xr);
//                     auxT1.setRotacaoY(yr);
//                     auxT1.setRotacaoZ(zr);
//                 }
//                 figAux1.setTransform(auxT1);
//             }

//             XMLElement* modelsElem1 = groupElem1->FirstChildElement("models");
//             if(modelsElem1){
//                 XMLElement* modelElem1 = modelsElem1->FirstChildElement("model");
//                 while(modelElem1){
//                     string filePath = modelElem1->Attribute("file");
//                     figAux1.addModelFile(filePath);
//                 }
//             }
//             figAux.addFigura(figAux1);
//         }
//         xml.models.push_back(figAux);
//     }
// }

void drawPontos(vector<Ponto> p) {
	int i = 0;

	while(i < p.size()) {
		glBegin(GL_TRIANGLES);
		glVertex3f(p[i].getX(), p[i].getY(), p[i].getZ());
		i++;
		glVertex3f(p[i].getX(), p[i].getY(), p[i].getZ());
		i++;
		glVertex3f(p[i].getX(), p[i].getY(), p[i].getZ());
		i++;
		glEnd();
	}

}


void drawFigure(Figure fig) {
	Transformacao trans = fig.getTransform();

	vector<Figure> vf = fig.getFiguras();

	vector<string> mods = fig.getModelFiles();

	vector<Ponto> pon = fig.getPontos();

	glPushMatrix();

	glTranslatef(trans.getTranslacaoX(), trans.getTranslacaoY(), trans.getTranslacaoZ());
	glRotatef(trans.getRotacaoAngle(), trans.getRotacaoX(), trans.getRotacaoY(), trans.getRotacaoZ());
	glScalef(trans.getEscalaX(), trans.getEscalaY(), trans.getEscalaZ());

	for (int i = 0; i < mods.size(); i++) {
		glColor3f(R, G, B);
		drawPontos(pon);
	}

	for (int i = 0; i < vf.size(); i++) {
		drawFigure(vf[i]);
	}

	glPopMatrix();
}

//esta penso que já está, confirmem só
void drawFigures() {
	for (int i = 0; i < xml.models.size(); i++) {
		drawFigure(xml.models[i]);
	}
}

void lerficheiro(std::string fileP) {
	string linha,token,delimiter = ",";
	int pos;
	double a,b,c;
	Ponto p;

	ifstream file(fileP);
	if (file.is_open()){

		while(getline(file,linha)){

			pos = linha.find(delimiter);
			token = linha.substr(0,pos);
			a = atof(token.c_str());
			linha.erase(0,pos + delimiter.length());
			p.setX(a);

			pos = linha.find(delimiter);
			token = linha.substr(0,pos);
			b = atof(token.c_str());
			linha.erase(0,pos + delimiter.length());
			p.setY(b);

			pos = linha.find(delimiter);
			token = linha.substr(0, pos);
			c = atof(token.c_str());
			linha.erase(0, pos + delimiter.length());
			p.setZ(c);

			//cout << p.x << " " << p.y << " " << p.z << endl;
			vertices.push_back(p);
		}
		file.close();			
	}
	else {
		cout << "ERRO AO LER O FICHEIRO" << endl;
	}
}

void readGrupo(Figure* figure, XMLElement* elementoXml) {


	int linhaTrans = -1, linhaRot = -1, linhaScale = -1;
	XMLElement* elementoAux = elementoXml->FirstChildElement("transform");
	Transformacao tAux;
	XMLElement* translacaoElemento = elementoAux->FirstChildElement("translate");
	if (translacaoElemento != nullptr) {

		//cout << "translate" << endl;
		linhaTrans = translacaoElemento->GetLineNum();

		float x = 0, y = 0, z = 0;
		if (translacaoElemento->Attribute("x") != nullptr) {
			x = stof(translacaoElemento->Attribute("x"));
		}
		if (translacaoElemento->Attribute("y") != nullptr) {
			y = stof(translacaoElemento->Attribute("y"));
		}
		if (translacaoElemento->Attribute("z") != nullptr) {
			z = stof(translacaoElemento->Attribute("z"));
		}
		tAux.setTranslacaoX(x);
		tAux.setTranslacaoY(y);
		tAux.setTranslacaoZ(z);
	}


	XMLElement* rotacaoElemento = elementoAux->FirstChildElement("rotate");
	if (rotacaoElemento != nullptr) {

		linhaRot = rotacaoElemento->GetLineNum();

		float angulo = 0, x = 0, y = 0, z = 0;
		if (rotacaoElemento->Attribute("angle") != nullptr) {
			angulo = stof(rotacaoElemento->Attribute("angle"));
		}
		if (rotacaoElemento->Attribute("x") != nullptr) {
			x = stof(rotacaoElemento->Attribute("x"));
		}
		if (rotacaoElemento->Attribute("y") != nullptr) {
			y = stof(rotacaoElemento->Attribute("y"));
		}
		if (rotacaoElemento->Attribute("z") != nullptr) {
			z = stof(rotacaoElemento->Attribute("z"));
		}
		tAux.setRotacaoAngle(angulo);
		tAux.setRotacaoX(x);
		tAux.setRotacaoY(y);
		tAux.setRotacaoZ(z);
	}


	XMLElement* escaloElemento = elementoAux->FirstChildElement("scale");
	if (escaloElemento != nullptr) {

		linhaScale = escaloElemento->GetLineNum();

		float x = 0, y = 0, z = 0;
		if (escaloElemento->Attribute("x") != nullptr) {
			x = stof(escaloElemento->Attribute("x"));
		}
		if (escaloElemento->Attribute("y") != nullptr) {
			y = stof(escaloElemento->Attribute("y"));
		}
		if (escaloElemento->Attribute("z") != nullptr) {
			z = stof(escaloElemento->Attribute("z"));
		}
		
		tAux.setEscalaX(x);
		tAux.setEscalaY(y);
		tAux.setEscalaZ(z);
	}
	(*figure).setTransform(tAux);

	XMLElement* modelosXML = elementoXml->FirstChildElement("models");

	if (modelosXML != nullptr) {
			XMLElement* modelElem = modelosXML->FirstChildElement("model");
            while(modelElem){
				string filePath;
                filePath = modelElem->Attribute("file");
                (*figure).addModelFile(filePath);
				modelElem = modelElem->NextSiblingElement();
            }
	}
	
	XMLElement* filhos = elementoXml->FirstChildElement("group");

	while (filhos != nullptr) {

		Figure filho = *new Figure();
		readGrupo(&filho, filhos);
		(*figure).addFigura(filho);

		filhos = filhos->NextSiblingElement();
	}
}

void lerXML(string ficheiro) {
	XMLDocument doc;
	if (!(doc.LoadFile(ficheiro.c_str()))){  //condicao que carrega o ficheiro e testa se é válido
		cout << "Ficheiro lido com sucesso" << endl;

		XMLElement* elemento = doc.FirstChildElement("world")->FirstChildElement("group");    //pega no elemento world do xml
		while (elemento != nullptr) {                  //avança até ser null
			Figure f;
			readGrupo(&f, elemento);
			xml.models.push_back(f);
			elemento = elemento->NextSiblingElement();     //avança para o proximo
		}

		XMLElement* root = doc.RootElement();

        XMLElement* windowElem = root->FirstChildElement("window");
        if (windowElem) {
            windowElem->QueryIntAttribute("width", &xml.windowWidth);
            windowElem->QueryIntAttribute("height", &xml.windowHeight);
        }

        XMLElement* cameraElem = root->FirstChildElement("camera");
        if (cameraElem) {
            XMLElement* posElem = cameraElem->FirstChildElement("position");
            if (posElem){
                posElem->QueryFloatAttribute("x", &xml.cameraPosX);
                posElem->QueryFloatAttribute("y", &xml.cameraPosY);
                posElem->QueryFloatAttribute("z", &xml.cameraPosZ);
            }

            XMLElement* lookAtElem = cameraElem->FirstChildElement("lookAt");
            if (lookAtElem) {
                lookAtElem->QueryFloatAttribute("x", &xml.cameraLookAtX);
                lookAtElem->QueryFloatAttribute("y", &xml.cameraLookAtY);
                lookAtElem->QueryFloatAttribute("z", &xml.cameraLookAtZ);
            }

            XMLElement* upElem = cameraElem->FirstChildElement("up");
            if (upElem) {
                upElem->QueryFloatAttribute("x", &xml.cameraUpX);
                upElem->QueryFloatAttribute("y", &xml.cameraUpY);
                upElem->QueryFloatAttribute("z", &xml.cameraUpZ);
            }

            XMLElement* projElem = cameraElem->FirstChildElement("projection");
            if (projElem) {
                projElem->QueryFloatAttribute("fov", &xml.cameraFov);
                projElem->QueryFloatAttribute("near", &xml.cameraNear);
                projElem->QueryFloatAttribute("far", &xml.cameraFar);
            }
        }
	}

	else {
		cout << "Erro ao ler o xml" << endl;
	}
	return;
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	

	gluLookAt(xml.cameraPosX,xml.cameraPosY,xml.cameraPosZ,
            xml.cameraLookAtX,xml.cameraLookAtY,xml.cameraLookAtZ,
			xml.cameraUpX,xml.cameraUpY,xml.cameraUpZ);

	// put drawing instructions here
    // glPolygonMode(GL_FRONT_AND_BACK,linha);
    // glTranslatef(camX,camY,camZ);
    // glRotatef(a,0,1,0);
    // glRotatef(w,1,0,0);
	
    // glBegin(GL_TRIANGLES);
    // glColor3f(R,G,B);
    // for (int i = 0; i < vertices.size(); i++){
    //     glVertex3f(vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
    // }
	// glEnd();

    drawFigures();

	// End of frame
	glutSwapBuffers();
}



int main(int argc, char **argv) {

    if(argc > 1){
		lerXML(argv[1]);
	}

    // put GLUT init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(xml.windowWidth,xml.windowHeight);
    glutCreateWindow("Phase 2");

    // put callback registration here
    glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
  
	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	// enter GLUT's main loop
	glutMainLoop(); 

	return 1;
}