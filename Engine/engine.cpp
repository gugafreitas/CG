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

//funcao que lê cada ficheiro .3d a partir do seu caminho
//preenchendo a lista de pontos com os pontos lidos do ficheiro

// void readFile(string caminho3d) {
//     string linha;
//     vector<string> coordenadas;
//     list<Ponto> pontosLista;
    
//     //abrir o ficheiro
//     ifstream file(caminho3d);
//     if (file.is_open()) {
        
//         //pega na primeira linha que é o número de vértices ou seja numero de linhas a ler (1 vertice por linha)
//         getline(file, linha);                   
//         int nLinhas = atoi(linha.c_str());        
//         for (int i = 1; i <= nLinhas; i++) {
//             getline(file, linha);     //pegar na linha atual
//             stringstream ss(linha);        
//             vector<string> result{
//                 istream_iterator<string>(ss), {}    //separar a linha nos espaços e guardar como array de strings em result
//             };
//             pontosLista.push_back(Ponto(stof(result[0]), stof(result[1]), stof(result[2]))); //adiciona o Ponto lido à lista de pontos
//         }

//         return pontosLista;
//     }
//     else { cout << "Erro ao ler o ficheiro .3d" << endl; }
// }

void lerficheiro(std::string fileP,Figure f) {
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	printf("String : %s\n",fileP.c_str());
	string linha,token,delimiter = ",";
	int pos;
	double a,b,c;
	Ponto p;

	ifstream file(fileP);
	if (file.is_open()){
		printf("Abri\n");

		while(getline(file,linha)){
			getline(file,linha);

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
			f.addPonto(p);
			printf("N pontos dentro: %d	n",f.getPontos().size());
		}
		file.close();			
	}
	else {
		cout << "ERRO AO LER O FICHEIRO" << endl;
	}
}

void drawPontos(vector<Ponto> p) {
	int i = 0;
	printf("N pontos: %d\n",p.size());

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
	printf("Desenhei\n");
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
		printf("Figura------------------\n");
		drawFigure(vf[i]);
	}

	glPopMatrix();
}

void drawFigures() {
	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx %d\n",xml.models[1].getModelFiles().size());
	printf("++++++++++++++++++++++++++++++%d\n",xml.models.size());
	for (int i = 0; i < xml.models.size(); i++) {
		printf("I: %d\n",i);
		printf("---------------------------%d\n",xml.models[i].getModelFiles().size());
		for(int j=0;j<xml.models[i].getModelFiles().size();j++)
			lerficheiro(xml.models[i].getModelFiles()[j],xml.models[i]);
		drawFigure(xml.models[i]);
	}
}

void readGrupo(XMLElement* grupoXML,Figure res) {

	//Figure resF = Figure();
	XMLElement* grupoAux = grupoXML->FirstChildElement("group");
	while(grupoAux != nullptr){
		Figure resF;
		XMLElement* transformAux = grupoAux->FirstChildElement("transform");

		Transformacao tAux = Transformacao();
		XMLElement* translacaoElemento = transformAux->FirstChildElement("translate");
		if (translacaoElemento != nullptr) {
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
			tAux.sumTranslacaoX(x);
			tAux.sumTranslacaoY(y);
			tAux.sumTranslacaoZ(z);
		}

		XMLElement* rotacaoElemento = transformAux->FirstChildElement("rotate");
		if (rotacaoElemento != nullptr) {
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
			tAux.sumRotacaoAngle(angulo);
			tAux.sumRotacaoX(x);
			tAux.sumRotacaoY(y);
			tAux.sumRotacaoZ(z);
		}


		XMLElement* escalaElemento = transformAux->FirstChildElement("scale");
		if (escalaElemento != nullptr) {
			float x = 0, y = 0, z = 0;
			if (escalaElemento->Attribute("x") != nullptr) {
				x = stof(escalaElemento->Attribute("x"));
			}
			if (escalaElemento->Attribute("y") != nullptr) {
				y = stof(escalaElemento->Attribute("y"));
			}
			if (escalaElemento->Attribute("z") != nullptr) {
				z = stof(escalaElemento->Attribute("z"));
			}
			tAux.sumEscalaX(x);
			tAux.sumEscalaY(y);
			tAux.sumEscalaZ(z);
		}
		resF.setTransform(tAux);

		XMLElement* modelosXML = grupoAux->FirstChildElement("models");

		if (modelosXML != nullptr) {
				printf("LER MODELOS func readGrupo\n");
				XMLElement* modelElem = modelosXML->FirstChildElement("model");
				while(modelElem != nullptr){
					printf("FICHEIRO PARA LER NA FUNCAO readGrupo\n");
					string filePath;
					filePath = modelElem->Attribute("file");
					printf("FilePath: %s\n", filePath.c_str());
					resF.addModelFile(filePath);
					printf("model file********************: %s \n", resF.getModelFiles()[0].c_str());
					for(int o=0; o<resF.getModelFiles().size();o++){
						printf("model file %d: %s ; ", o, resF.getModelFiles()[o].c_str());
					}
					printf("\n");
					modelElem = modelElem->NextSiblingElement();
				}
		}
		
		XMLElement* filhos = grupoAux->FirstChildElement("group");

		printf("FILHOS\n");

		while(filhos != nullptr) {
			printf("HORA DE LER OS FILHOS\n");
			Figure filho;
			readGrupo(grupoAux,filho);
			//printf("Depois\n");
			resF.addFigura(filho);
			filhos = filhos->NextSiblingElement();
		}
		res.addFigura(resF);
		grupoAux = grupoAux->NextSiblingElement();
	}
	xml.models.push_back(res);
	
	//return resF;
}

void lerXML(string ficheiro) {
	XMLDocument doc;
	if (!(doc.LoadFile(ficheiro.c_str()))){  //condicao que carrega o ficheiro e testa se é válido
		cout << "Ficheiro lido com sucesso" << endl;

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

		XMLElement* grupoElem = root->FirstChildElement("group");
		while(grupoElem != nullptr){
			Figure fig;
			readGrupo(grupoElem,fig);
			xml.models.push_back(fig);
			grupoElem = grupoElem->NextSiblingElement();
		}
	}
	else {
		cout << "Erro ao ler o xml" << endl;
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

    drawFigures();

	// End of frame
	glutSwapBuffers();
}

// void lerMultiFicheiros(vector<Figure> figs){
// 	printf("ENTREI NA LERMULTIFICHEIROS\n");
// 	for(int i = 0; i < figs.size(); i++){
// 		printf("%d\n",figs.size());
// 		printf("size modelFiles: %d\n", figs[i].getModelFiles().size());
// 		printf("modelFiles: %s\n", figs[i].getModelFiles()[i].c_str());
// 		for(int j = 0; j < figs[i].getModelFiles().size(); j++){
// 			lerficheiro(figs[i].getModelFiles()[j]);
// 		}
// 		printf("Num de filhos: %d\n", figs[i].getFiguras().size());
// 		for(int o = 0; o < figs[i].getFiguras().size(); o++){
// 			lerMultiFicheiros(figs[i].getFiguras());
// 		}
// 	}
// }

int main(int argc, char **argv) {

    if(argc > 1){
		printf("VOU LER O XML\n");
		lerXML(argv[1]);
	}

    // put GLUT init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(xml.windowWidth,xml.windowHeight);

	// printf("glut done\n");
	
	// lerMultiFicheiros(xml.models);

	// printf("passei na lerMultiFicheiros\n");

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
