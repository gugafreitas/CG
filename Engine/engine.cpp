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

void lerXML(string ficheiro) {
    XMLDocument doc;
    if (doc.LoadFile(ficheiro.c_str()) != XML_SUCCESS) {
        std::cerr << "Error loading XML file: " << doc.GetErrorStr1() << std::endl;
        return;
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

    XMLElement* groupElem = root->FirstChildElement("group");
    while(groupElem){
        Figure figAux;
        XMLElement* transformElem = root->FirstChildElement("transform");
        if(transformElem){
            XMLElement* scaleElem = transformElem->FirstChildElement("scale");
            Transformacao auxT;
            if(scaleElem){
                float xe, ye, ze;
                scaleElem->QueryFloatAttribute("x", &xe);
                scaleElem->QueryFloatAttribute("y", &ye);
                scaleElem->QueryFloatAttribute("z", &ze);

                auxT.setEscalaX(xe);
                auxT.setEscalaY(ye);
                auxT.setEscalaZ(ze);
            }

            XMLElement* translateElem = transformElem->FirstChildElement("translate");
            if(translateElem){
                float xt, yt, zt;
                translateElem->QueryFloatAttribute("x", &xt);
                translateElem->QueryFloatAttribute("y", &yt);
                translateElem->QueryFloatAttribute("z", &zt);

                auxT.setTranslacaoX(xt);
                auxT.setTranslacaoY(yt);
                auxT.setTranslacaoZ(zt);
            }

            XMLElement* rotateElem = transformElem->FirstChildElement("rotate");
            if(rotateElem){
                float xr, yr, zr, ar;
                rotateElem->QueryFloatAttribute("x", &xr);
                rotateElem->QueryFloatAttribute("y", &yr);
                rotateElem->QueryFloatAttribute("z", &zr);
                rotateElem->QueryFloatAttribute("angle", &ar);

                auxT.setRotacaoAngle(ar);
                auxT.setRotacaoX(xr);
                auxT.setRotacaoY(yr);
                auxT.setRotacaoZ(zr);
            }
            figAux.setTransform(auxT);
        }

        XMLElement* modelsElem = root->FirstChildElement("models");
        if(modelsElem){
            XMLElement* modelElem = modelsElem->FirstChildElement("model");
            while(modelElem){
                string filePath = modelElem->Attribute("file");
                figAux.addModelFile(filePath);
            }
        }

        XMLElement* groupElem1 = root->FirstChildElement("group");
        while(groupElem1){
            Figure figAux1;
            XMLElement* transformElem1 = root->FirstChildElement("transform");
            if(transformElem1){
                XMLElement* scaleElem1 = transformElem1->FirstChildElement("scale");
                Transformacao auxT1;
                if(scaleElem1){
                    float xe, ye, ze;
                    scaleElem1->QueryFloatAttribute("x", &xe);
                    scaleElem1->QueryFloatAttribute("y", &ye);
                    scaleElem1->QueryFloatAttribute("z", &ze);

                    auxT1.setEscalaX(xe);
                    auxT1.setEscalaY(ye);
                    auxT1.setEscalaZ(ze);
                }

                XMLElement* translateElem1 = transformElem1->FirstChildElement("translate");
                if(translateElem1){
                    float xt, yt, zt;
                    translateElem1->QueryFloatAttribute("x", &xt);
                    translateElem1->QueryFloatAttribute("y", &yt);
                    translateElem1->QueryFloatAttribute("z", &zt);

                    auxT1.setTranslacaoX(xt);
                    auxT1.setTranslacaoY(yt);
                    auxT1.setTranslacaoZ(zt);
                }

                XMLElement* rotateElem1 = transformElem1->FirstChildElement("rotate");
                if(rotateElem1){
                    float xr, yr, zr, ar;
                    rotateElem1->QueryFloatAttribute("x", &xr);
                    rotateElem1->QueryFloatAttribute("y", &yr);
                    rotateElem1->QueryFloatAttribute("z", &zr);
                    rotateElem1->QueryFloatAttribute("angle", &ar);

                    auxT1.setRotacaoAngle(ar);
                    auxT1.setRotacaoX(xr);
                    auxT1.setRotacaoY(yr);
                    auxT1.setRotacaoZ(zr);
                }
                figAux1.setTransform(auxT1);
            }

            XMLElement* modelsElem1 = root->FirstChildElement("models");
            if(modelsElem1){
                XMLElement* modelElem1 = modelsElem1->FirstChildElement("model");
                while(modelElem1){
                    string filePath = modelElem1->Attribute("file");
                    figAux1.addModelFile(filePath);
                }
            }
            figAux.addFigura(figAux1);
        }
        xml.models.push_back(figAux);
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
    glPolygonMode(GL_FRONT_AND_BACK,linha);
    glTranslatef(camX,camY,camZ);
    glRotatef(a,0,1,0);
    glRotatef(w,1,0,0);
	
    glBegin(GL_TRIANGLES);
    glColor3f(R,G,B);
    for (int i = 0; i < vertices.size(); i++){
        glVertex3f(vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
    }
	glEnd();

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

    for(int i = 0; i < nOfFiles; i++){
        lerficheiro(xml.models[xml.models.size() - 1].getModelFiles()[0]);
        glutCreateWindow(xml.models[xml.models.size() - 1].getModelFiles()[0].c_str());
        // put callback registration here
        glutDisplayFunc(renderScene);
        glutReshapeFunc(changeSize);
    }
    
    // put callback registration here
    // glutDisplayFunc(renderScene);
    // glutReshapeFunc(changeSize);    
	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	// enter GLUT's main loop
	glutMainLoop(); 

	return 1;
}