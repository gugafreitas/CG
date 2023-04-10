#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include "tinyxml2.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <string.h>

using namespace tinyxml2;
using namespace std;

struct Ponto
{
    double x;
    double y;
    double z;
};

float R = 1, G = 1, B = 1;
float size;
float a = 1, w = 1;
float camX = 0, camY = 0, camZ = 0;
float zx = 6, zy = 6, zz = 6;
int xinicio, yinicio , tracking = 0;
int k = 5 , alpha = 0 , beta = 0;
vector<Ponto> vertices; //vetor com os pontos lidos do ficheiro
int linha = GL_LINE;

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
    std::vector<std::string> modelFiles;
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
        if (posElem) {
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

    XMLElement* sceneElem = root->FirstChildElement("group")->FirstChildElement("scene");
    if (sceneElem) {
        for (XMLElement* modelElem = sceneElem->FirstChildElement("model"); modelElem != NULL; modelElem = modelElem->NextSiblingElement("model")) {
            const char* file = modelElem->Attribute("file");
            if (file) {
                xml.modelFiles.push_back(file);
            }
        }
    }
}



// int leitura3D(string ficheiro){

//     FILE * fp;
//     char * line = NULL;
//     size_t len = 0;
//     ssize_t read;

//     double list[3];

//     fp = fopen(xml.modelFiles, "r");
//     if (fp == NULL)
//         exit(EXIT_FAILURE);

//     while ((read = getline(&line, &len, fp)) != -1) {
//         char * token = strtok(line, ",");
//         int i = 0;

//         while( token != NULL ) {
//               float x = atof(token);
//             list[i] = x;
//             i++;
//               token = strtok(NULL, ",");
//            }

//         //dar list à função que desenha triangulos
        
//         /*
//         for(int i=0;i<3;i++){
//             printf("%f,",list[i]);
//         }
//         printf("\n");
//         */
        
//     }

//     fclose(fp);
//     if (line)
//         free(line);
//     exit(EXIT_SUCCESS);

// }

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

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    double list[3];
    printf("OLA\n");
    fp = fopen("cone.3d", "r");
    printf("OLAAAA234\n");
    if (fp == NULL){
        printf("OLAAAA234\n");
        exit(EXIT_FAILURE);
    }

    printf("OLAAAA234\n");

    while ((read = getline(&line, &len, fp)) != -1) {
        char * token = strtok(line, ",");
        int i = 0;
        printf("OLAAAAAA\n");

        while( token != NULL ) {
              float x = atof(token);
            list[i] = x;
            i++;
              token = strtok(NULL, ",");
        }
        glBegin(GL_TRIANGLES);
        glColor3f(R,G,B);
        glVertex3f(list[0],list[1],list[2]);
        glEnd();
        printf("OLAAAAAA\n");
    }

    fclose(fp);

    printf("OLAAAAAA\n");

	// glBegin(GL_TRIANGLES);
	// glColor3f(R,G,B);

    // leitura3D(xml.modelFiles)



	// for (int i = 0; i < vertices.size(); i++)
	// 	glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	// glEnd();

	// End of frame
	glutSwapBuffers();
}

void lerficheiro(string ficheiro) {

	string linha,token,delimiter = ",";
	int pos;
	double a,b,c;
	Ponto p;

	ifstream file(ficheiro);
	if (file.is_open()){

		while(getline(file,linha)){

			pos = linha.find(delimiter);
			token = linha.substr(0,pos);
			a = atof(token.c_str());
			linha.erase(0,pos + delimiter.length());
			p.x = a;

			pos = linha.find(delimiter);
			token = linha.substr(0,pos);
			b = atof(token.c_str());
			linha.erase(0,pos + delimiter.length());
			p.y = b;

			pos = linha.find(delimiter);
			token = linha.substr(0, pos);
			c = atof(token.c_str());
			linha.erase(0, pos + delimiter.length());
			p.z = c;

			//cout << p.x << " " << p.y << " " << p.z << endl;
			vertices.push_back(p);
		}
		file.close();			
	}
	else {
		cout << "ERRO AO LER O FICHEIRO" << endl;
	}
}

// // Leitura do ficheiro XML
// void lerXML(string ficheiro) {
// 	XMLDocument docxml;

// 	if (!(docxml.LoadFile(ficheiro.c_str()))) {
// 		XMLElement* root = docxml.FirstChildElement();
// 		for(XMLElement *elemento = root -> FirstChildElement();elemento != NULL; elemento = elemento -> NextSiblingElement()){
// 			string fich = elemento -> Attribute("file");
// 			cout << "Ficheiro: " << fich << " lido com sucesso " << endl;
// 			lerficheiro(fich);
// 		}		
// 	}
// 	else {
// 		cout << "Ficheiro XML não foi encontrado" << endl;
// 	}
// }




int main(int argc, char **argv) {

    if(argc > 1){
		lerXML(argv[1]);
	}

	// put GLUT init here

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Projeto_de_CG"); 


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