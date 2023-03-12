#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include "tinyxml2.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

struct Ponto
{
    double x;
    double y;
    double z;
};

struct xml
{
	float window_width;
	float window_height;
	float camera_position_x;
	float camera_position_y;
	float camera_position_z;
	float camera_lookAt_x;
	float camera_lookAt_y;
	float camera_lookAt_z;
	float camera_up_x;
	float camera_up_y;
	float camera_up_z;
} settings;


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
	

	gluLookAt(zx,zy,zz,
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
   

	// put drawing instructions here
    glPolygonMode(GL_FRONT_AND_BACK,linha);
    glTranslatef(camX,camY,camZ);
    glRotatef(a,0,1,0);
    glRotatef(w,1,0,0);



	glBegin(GL_TRIANGLES);
	glColor3f(R,G,B);

	for (int i = 0; i < vertices.size(); i++)
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	glEnd();

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

// Leitura do ficheiro XML
void lerXML(string ficheiro) {
	XMLDocument docxml;

	if (!(docxml.LoadFile(ficheiro.c_str()))) {
		XMLElement* root = docxml.FirstChildElement();
		for(XMLElement *elemento = root -> FirstChildElement();elemento != NULL; elemento = elemento -> NextSiblingElement()){
			string fich = elemento -> Attribute("file");
			cout << "Ficheiro: " << fich << " lido com sucesso " << endl;
			lerficheiro(fich);
		}		
	}
	else {
		cout << "Ficheiro XML não foi encontrado" << endl;
	}
}

// void lerXML(string ficheiro) {
// 	XMLDocument docxml;

// 	if (!(docxml.LoadFile(ficheiro.c_str()))) {
// 		XMLElement* root = docxml.FirstChildElement();
// 		for(XMLElement *elemento = root -> FirstChildElement();elemento != NULL; elemento = elemento -> NextSiblingElement()){
// 			string fich = elemento -> Attribute("file");
// 			settings.window_width = elemento -> Attribute("width");
// 			settings.window_height = elemento -> Attribute("height");
// 			settings.camera_position_x = elemento -> Attribute("x");
// 			settings.camera_position_y = elemento -> Attribute("y");
// 			settings.camera_position_z = elemento -> Attribute("z");
// 			settings.camera_lookAt_x = elemento -> Attribute("x");
// 			settings.camera_lookAt_y = elemento -> Attribute("y");
// 			settings.camera_lookAt_z = elemento -> Attribute("z");
// 			settings.camera_up_x = elemento -> Attribute("x");
// 			settings.camera_up_y = elemento -> Attribute("y");
// 			settings.camera_up_z = elemento -> Attribute("z");
// 			cout << "Ficheiro: " << fich << " lido com sucesso " << endl;
// 			lerficheiro(fich);
// 		}		
// 	}
// 	else {
// 		cout << "Ficheiro XML não foi encontrado" << endl;
// 	}
// }

// void lerXML(string arquivo) {
//     XMLElement doc;
//     if (!doc.LoadFile("arquivo.xml")) {
//         std::cerr << "Erro ao abrir o arquivo XML." << std::endl;
//         return;
//     }

//     XMLElement* world = doc.FirstChildElement("world");
//     if (world) {
//         XMLElement* window = world->FirstChildElement("window");
//         if (window) {
//             window->QueryFloatAttribute("width", &settings.window_width);
// 			float print = settings.window_width;
// 			printf("%f", print);
//             window->QueryFloatAttribute("height", &settings.window_height);
//             std::cout << "Tamanho da janela: " << settings.window_width << " x " << settings.window_height << std::endl;
//         }
//         XMLElement* camera = world->FirstChildElement("camera");
//         if (camera) {
//             XMLElement* position = camera->FirstChildElement("position");
//             if (position) {
//                 position->QueryFloatAttribute("x", &settings.camera_position_x);
//                 position->QueryFloatAttribute("y", &settings.camera_position_y);
//                 position->QueryFloatAttribute("z", &settings.camera_position_z);
//                 std::cout << "Posicao da camera: (" << settings.camera_position_x << ", " << settings.camera_position_y << ", " << settings.camera_position_z << ")" << std::endl;
//             }
//             XMLElement* lookAt = camera->FirstChildElement("lookAt");
//             if (lookAt) {
//                 lookAt->QueryFloatAttribute("x", &settings.camera_lookAt_x);
//                 lookAt->QueryFloatAttribute("y", &settings.camera_lookAt_y);
//                 lookAt->QueryFloatAttribute("z", &settings.camera_lookAt_z);
// 				std::cout << "LookAt da camera: (" << settings.camera_lookAt_x << ", " << settings.camera_lookAt_y << ", " << settings.camera_lookAt_z << ")" << std::endl;
//             }
//             XMLElement* up = camera->FirstChildElement("up");
//             if (up) {
//                 float x, y, z;
//                 up->QueryFloatAttribute("x", &settings.camera_up_x);
//                 up->QueryFloatAttribute("y", &settings.camera_up_y);
//                 up->QueryFloatAttribute("z", &settings.camera_up_z);
//                 std::cout << "Vetor Up da camera: (" << settings.camera_up_x << ", " << settings.camera_up_y << ", " << settings.camera_up_z << ")" << std::endl;
//             }
//         }
//         XMLElement* group = world->FirstChildElement("group");
//         if (group) {
//             XMLElement* scene = group->FirstChildElement("scene");
//             if (scene) {
//                 XMLElement* model = scene->FirstChildElement("model");
//                 while (model) {
//                     const char* filename = model->Attribute("file");
//                     if (filename) {
//                         std::cout << "Modelo: " << filename << std::endl;
//                     }
//                     model = model->NextSiblingElement("model");
//                 }
//             }
//         }
//     }
//     //doc.Clear();
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