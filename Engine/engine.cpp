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

Figure lerficheiro(string fileP, Figure f) {
	string linha, token, delimiter = ",";
	int pos;
	double a,b,c;
	Ponto p;
	Figure res = f;
	
	
	ifstream myFile(fileP);

	if (myFile.is_open()){
		while(getline(myFile,linha)){
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

			res.addPonto(p);
		}
		myFile.close();			
	}
	else {
		cout << "ERRO AO LER O FICHEIRO NA LERFICHEIRO" << endl;
	}
	return res;
}

// void drawPontos(vector<Ponto> p) {
// 	int i = 0;

// 	while(i < p.size()) {
// 		glColor3f(R, G, B);
// 		glBegin(GL_TRIANGLES);
// 		glVertex3f(p[i].getX(), p[i].getY(), p[i].getZ());
// 		i++;
// 		glVertex3f(p[i].getX(), p[i].getY(), p[i].getZ());
// 		i++;
// 		glVertex3f(p[i].getX(), p[i].getY(), p[i].getZ());
// 		i++;
// 		glEnd();
// 	}
// }

// void drawFigure(Figure fig) {
// 	Transformacao trans = fig.getTransform();

// 	vector<Figure> vf = fig.getFiguras();

// 	vector<string> mods = fig.getModelFiles();

// 	vector<Ponto> pon = fig.getPontos();


// 	glPushMatrix();

// 	glTranslatef(trans.getTranslacaoX(), trans.getTranslacaoY(), trans.getTranslacaoZ());
// 	glRotatef(trans.getRotacaoAngle(), trans.getRotacaoX(), trans.getRotacaoY(), trans.getRotacaoZ());
// 	glScalef(trans.getEscalaX(), trans.getEscalaY(), trans.getEscalaZ());
// 	for (int i = 0; i < mods.size(); i++) {
// 		drawPontos(pon);
// 	}

// 	glPopMatrix();
// }

// void drawFigures(vector<Figure> figs) {
// 	for (int i = 0; i < figs.size(); i++) {
// 		for(int j=0;j<figs[i].getModelFiles().size();j++){
// 			figs[i] = lerficheiro(figs[i].getModelFiles()[j],figs[i]);
// 		}
// 		drawFigures(figs[i].getFiguras());
// 		drawFigure(figs[i]);
// 	}

// }

Figure readGrupo(XMLElement* grupoElem){
	Figure res = Figure();

	XMLElement* transformAux = grupoElem->FirstChildElement("transform");
	if(transformAux != nullptr){
		Transformacao tAux = Transformacao();
		XMLElement* translacaoElemento = transformAux->FirstChildElement("translate");

		if (translacaoElemento != nullptr) {
			bool align;
			float time = 0, xt=0, yt=0, zt=0;
			vector<Ponto> catmullPoints;
			if(translacaoElemento->Attribute("x") != nullptr){
				xt = stof(translacaoElemento->Attribute("x"));
			}
			if(translacaoElemento->Attribute("y") != nullptr){
				yt = stof(translacaoElemento->Attribute("y"));
			}
			if(translacaoElemento->Attribute("z") != nullptr){
				zt = stof(translacaoElemento->Attribute("z"));
			}

			if (translacaoElemento->Attribute("align") != nullptr) {
				char *aux;
				aux = strdup(translacaoElemento->Attribute("align"));
				if(!strcmp(aux,"True")){
					align = true;
				}
				else{
					align = false;
				}
			}
			if (translacaoElemento->Attribute("time") != nullptr) {
				time = stof(translacaoElemento->Attribute("time"));
			}
			XMLElement* transPonto = translacaoElemento->FirstChildElement("point");
			while(transPonto != nullptr){
				float x=0, y=0, z=0;
				if(transPonto->Attribute("x") != nullptr){
					x = stof(transPonto->Attribute("x"));
				}
				if(transPonto->Attribute("y") != nullptr){
					y = stof(transPonto->Attribute("y"));
				}
				if(transPonto->Attribute("z") != nullptr){
					z = stof(transPonto->Attribute("z"));
				}
				Ponto pAux;
				pAux.setX(x);
				pAux.setY(y);
				pAux.setZ(z);
				catmullPoints.push_back(pAux);
				transPonto = transPonto->NextSiblingElement();
			}
			tAux.setTransAlign(align);
			tAux.setTransTempo(time);
			tAux.setTransPontosCurva(catmullPoints);
			tAux.sumTrans_X(xt);
			tAux.sumTrans_Y(yt);
			tAux.sumTrans_Z(zt);
		}

		XMLElement* rotacaoElemento = transformAux->FirstChildElement("rotate");
		if (rotacaoElemento != nullptr) {
			float angulo = 0, x = 0, y = 0, z = 0, tempo = 0;
			if(rotacaoElemento->Attribute("time") != nullptr){
				tempo = stof(rotacaoElemento->Attribute("time"));
			}
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
		res.setTransform(tAux);
	}

	XMLElement* modelosXML = grupoElem->FirstChildElement("models");
	if(modelosXML != nullptr){
		XMLElement* modelElem = modelosXML->FirstChildElement("model");
		while(modelElem != nullptr){
			string filePath;
			filePath = modelElem->Attribute("file");
			res.addModelFile(filePath);
			modelElem = modelElem -> NextSiblingElement();
		}
	}

	XMLElement* filhos = grupoElem->FirstChildElement("group");
	while(filhos != nullptr){
		Figure filho = readGrupo(filhos);
		res.addFigura(filho);
		filhos = filhos->NextSiblingElement();
	}

	return res;
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
			Figure res = readGrupo(grupoElem);
			xml.models.push_back(res);
			grupoElem = grupoElem->NextSiblingElement();
		}
	}
	else {
		cout << "Erro ao ler o xml" << endl;
	}
}

void aplicaRotacao(Transformacao rot) {

	float aux, anguloRot;
	int tempoPrograma;

	if (rot.getTempo() != 0) {
		tempoPrograma = glutGet(GLUT_ELAPSED_TIME);
		aux = tempoPrograma % (int)(rot.getTempo() * 1000);
		anguloRot = (aux * 360) / (rot.getTempo() * 1000);
		glRotatef(anguloRot, rot.getX(), rot.getY(), rot.getZ());
	}
}

void drawGrupo(Grupo g) {

	// obtenção da informação do grupo passado como arugmento

	Translacao t = g.getTranslacao();
	Rotacao r = g.getRotacao();
	Escala e = g.getEscala();
	string ordem = g.getOrdem();
	vector<Grupo> filhos = g.getFilhos();
	vector<Modelo> m = g.getModelos();

	glPushMatrix();

	// executar as tranformações pela ordem correta

	for (int i = 0; i < 5; i += 2) {
		switch (ordem[i]) {
		case 'T':
			if (t.getPontos().size() == 0) {
				glTranslatef(t.getX(), t.getY(), t.getZ());
			}
			else {
				glColor3f(1.0f, 1.0f, 1.0f);
				t.draw();
			}
			break;
		case 'R':
			if (r.getAngulo() != 0) {
				glRotatef(r.getAngulo(), r.getX(), r.getY(), r.getZ());
			}
			else {
				aplicaRotacao(r);
			}
			break;
		case 'E':
			glScalef(e.getX(), e.getY(), e.getZ());
			break;
		default:
			break;
		}
	}


	for (int i = 0; i < m.size(); i++) {
		glColor3f(m[i].getR(), m[i].getG(), m[i].getB());
		Modelo aux = m[i];
		aux.draw();
	}

	for (int i = 0; i < filhos.size(); i++) {
		drawGrupo(filhos[i]);
	}

	glPopMatrix();
}

void drawGrupos() {
	for (int i = 0; i < gruposLista.size(); i++) { // vai individualmente a cada grupo principal, que estao alocados globalmente no vetor gruposLista
		drawGrupo(gruposLista[i]);
	}
}

//funcao que processa as teclas do rato e muda as coordenadas, angulos ou raio da camara com base nisso
void processMouseButtons(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		xInicial = x;
		yInicial = y;
		if (button == GLUT_LEFT_BUTTON)		modoRato = 1; //modo rodar camara
		else if (button == GLUT_RIGHT_BUTTON)  modoRato = 2; //modo aproximar ou afastar camara
		else modoRato = 0;
	}
	else if (state == GLUT_UP) {
		if (modoRato == 1) { //muda alpha e beta pois este modo muda a posicao
			alpha += (x - xInicial);
			beta += (y - yInicial);
		}
		else if (modoRato == 2) { //muda raio pois este modo muda o zoom
			r -= y - yInicial;
			if (r < 3) r = 3.0;
		}
		modoRato = 0;
	}
}

//funcao que faz a movimentacao das variaveis da camara
void processMouseMotion(int x, int y)
{
	int xAux, yAux;
	int alphaAux, betaAux;
	int rAux;

	if (!modoRato) return;

	xAux = x - xInicial;
	yAux = y - yInicial;

	if (modoRato == 1) {

		alphaAux = alpha + xAux;
		betaAux = beta + yAux;
		if (betaAux > 85.0) betaAux = 85.0;
		else if (betaAux < -85.0) betaAux = -85.0;
		rAux = r;
	}
	else if (modoRato == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - yAux;
		if (rAux < 3) rAux = 3;
	}
	//nova posicao x,y,z da camara
	camX = rAux * sin(-alphaAux * M_PI / 180.0) * cos(betaAux * M_PI / 180.0);
	camZ = rAux * cos(-alphaAux * M_PI / 180.0) * cos(betaAux * M_PI / 180.0);
	camY = rAux * sin(betaAux * M_PI / 180.0);
}

//funcao que dá função ás teclas premidas
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'e') {
		eixos = !eixos;
	}
	if (key == 'f') {
		tipo = GL_FILL;
	}
	if (key == 'l') {
		tipo = GL_LINE;
	}
	if (key == 'p') {
		tipo = GL_POINT;
	}

	if (key == 'r') {
		v = 1.0f;
		g = 0.0f;
		b = 0.0f;

	}
	if (key == 'g') {
		v = 0.0f;
		g = 1.0f;
		b = 0.0f;
	}
	if (key == 'b') {
		v = 0.0f;
		g = 0.0f;
		b = 1.0f;
	}

	glutPostRedisplay();

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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//modo de desenho, começa com linhas por defeito
	glPolygonMode(GL_FRONT_AND_BACK, tipo);

	// set the camera
	glLoadIdentity();
	gluLookAt(xml.cameraPosX,xml.cameraPosY,xml.cameraPosZ,
            xml.cameraLookAtX,xml.cameraLookAtY,xml.cameraLookAtZ,
			xml.cameraUpX,xml.cameraUpY,xml.cameraUpZ);

    //drawFigures(xml.models);
	drawGrupos();

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
    glutCreateWindow("Phase 3");

    // put callback registration here
    glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	// mouse callbacks
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	glutKeyboardFunc(keyboard);

	glewInit();
  
	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);

	
	// enter GLUT's main loop
	glutMainLoop(); 

	return 1;
}
