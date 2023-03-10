#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glut.h>
#include <stdlib.h>

//generator plane 1 3 plane.3d
void plane(int lado, int divs, char* nome){
	//FILE *fp = fopen(nome, "w");
    std::ofstream f(nome)
    std::stringstream ss;
    float x,z,x1,z1,x2,z2,x3,z3,x4,z4;
    float aresta = lado/divs;

    x= -(lado/2);
    z= -(lado/2);

    for(int i=0;i<divs;i++){

        for(int j=0;j<divs;j++){
                
            z1 = z + (i*aresta);
            x1 = x + (j*aresta);

            z2 = z1;
            x2 = x1 + aresta;

            z3 = z1 + aresta;
            x3 = x1 + aresta;

            z4 = z1 + aresta;
            x4 = x1;

            ss << x1; ss << ","; ss << "0,"; ss << z1; ss << '\n';
            ss << x2; ss << ","; ss << "0,"; ss << z2; ss << '\n';
            ss << x3; ss << ","; ss << "0,"; ss << z3; ss << '\n';
            ss << x1; ss << ","; ss << "0,"; ss << z1; ss << '\n';
            ss << x3; ss << ","; ss << "0,"; ss << z3; ss << '\n';
            ss << x4; ss << ","; ss << "0,"; ss << z4; ss << '\n';

            std::string s = ss.str();
            ss.clear();
            f << s;
        }

    }

    f.close();
}

void sphere(float raio,int slices,int stacks,char *file){

	//FILE *fp = fopen(file, "w");
    std::ofstream f(file)
    std::stringstream ss;
	float angBase = (2 * M_PI)/slices;

	float x1,z1,x2,z2,x3,z3,x4,z4;

	float yBase=0;
	float yAcima=0;
	float yAux=0;
	float angStack = 0;

	for(int j=1;j<=stacks;j++){
		yAux = yAcima;
		angStack = j * (M_PI / stacks);

		for(int i =0;i<slices;i++){
			yBase = yAux;
			yAcima = raio * sin(angStack);
			x1 = raio * sin(i*angBase);
			z1 = raio * cos(i*angBase);
			

			x2 = raio * cos(angStack) * sin(i*angBase);
			z2 = raio * cos(angStack) * cos(i*angBase);

			x3 = raio * sin((i+1)*angBase);
			z3 = raio * cos((i+1)*angBase);

			x4 = raio * cos(angStack) * sin((i+1)*angBase);
			z4 = raio * cos(angStack) * cos((i+1)*angBase);

			ss << x1; ss << ","; ss << yBase; ss << ","; ss << z1; ss << '\n';
			ss << x2; ss << ","; ss << yAcima; ss << ","; ss << z2; ss << '\n';
			ss << x3; ss << ","; ss << yBase; ss << ","; ss << z3; ss << '\n';
			ss << x3; ss << ","; ss << yBase; ss << ","; ss << z3; ss << '\n';
			ss << x2; ss << ","; ss << yAcima; ss << ","; ss << z2; ss << '\n';
			ss << x4; ss << ","; ss << yAcima; ss << ","; ss << z4; ss << '\n';
            //std::string s = ss.str();
            //ss.clear();
            //f << s;
		}
		

	}
	for(int j=1;j<=stacks;j++){
		yAux = yAcima;
		angStack = j * (M_PI / stacks);

		for(int i =0;i<slices;i++){
			yBase = yAux;
			yAcima = -raio * sin(angStack);
			x1 = -raio * sin(i*angBase);
			z1 = -raio * cos(i*angBase);
			

			x2 = -raio * cos(angStack) * sin(i*angBase);
			z2 = -raio * cos(angStack) * cos(i*angBase);

			x3 = -raio * sin((i+1)*angBase);
			z3 = -raio * cos((i+1)*angBase);

			x4 = -raio * cos(angStack) * sin((i+1)*angBase);
			z4 = -raio * cos(angStack) * cos((i+1)*angBase);

            ss << x1; ss << ","; ss << yBase; ss << ","; ss << z1; ss << '\n';
            ss << x3; ss << ","; ss << yBase; ss << ","; ss << z3; ss << '\n';
            ss << x2; ss << ","; ss << yAcima; ss << ","; ss << z2; ss << '\n';
            ss << x3; ss << ","; ss << yBase; ss << ","; ss << z3; ss << '\n';
            ss << x4; ss << ","; ss << yAcima; ss << ","; ss << z4; ss << '\n';
            ss << x2; ss << ","; ss << yAcima; ss << ","; ss << z2; ss << '\n';
            //std::string s = ss.str();
            //ss.clear();
            //f << s;
		}
	}

    std::string s = ss.str();
    ss.clear();
    f << s;
	f.close()
}

void cone(int radius, int height, int slices, int stacks, char* filePath){
    float sliceAngle = (float) (2 * M_PI) / slices;
    float stackSize = (float) height / stacks;
    float halfSize = (float) (-height) / 2;
    std::ofstream f(filePath);
    //base
    for(float a = 0; a < (2 * M_PI); a += sliceAngle){
        float x1 = 0;
        float y1 = halfSize;
        float z1 = 0;

        float x2 = (float) radius * sin(a + sliceAngle);
        float y2 = halfSize;
        float z2 =(float) radius * cos(a + sliceAngle);

        float x3 = (float) radius * sin(a);
        float y3 = halfSize;
        float z3 = (float)radius * cos(a);

        std::stringstream ss;
        ss << x1; ss << ","; ss << y1; ss << ","; ss << z1; ss << '\n';
        ss << x2; ss << ","; ss << y2; ss << ","; ss << z2; ss << '\n';
        ss << x3; ss << ","; ss << y3; ss << ","; ss << z3; ss << '\n';

        std::string s = ss.str();
        ss.clear();
        f << s;

    }
    //altura
    for(int i = 0; i<stacks; i++){
        for(float a = 0; a < (2 * M_PI); a += sliceAngle){
            float layer = halfSize + i * stackSize;
            float layerAux = halfSize + (i + 1) * stackSize;

            float radius1 = (float) radius - (radius * i) / stacks;
            float radius2 = (float) radius - (radius * (i + 1)) / stacks;

            float x4 = radius2 * sin(a);
            float y4 = layerAux;
            float z4 = radius2 * cos(a);

            float x5 = radius1 * sin(a);
            float y5 = layer;
            float z5 = radius1 * cos(a);

            float x6 = radius2 * sin(a + sliceAngle);
            float y6 = layerAux;
            float z6 = radius2 * cos(a + sliceAngle);

            float x7 = radius1 * sin(a);
            float y7 = layer;
            float z7 = radius1 * cos(a);

            float x8 = radius1 * sin(a + sliceAngle);
            float y8 = layer;
            float z8 = radius1 * cos(a + sliceAngle);

            float x9 = radius2 * sin(a + sliceAngle);
            float y9 = layerAux;
            float z9 = radius2 * cos(a + sliceAngle);

            std::stringstream ss;
            ss << x4; ss << ","; ss << y4; ss << ","; ss << z4; ss << '\n';
            ss << x5; ss << ","; ss << y5; ss << ","; ss << z5; ss << '\n';
            ss << x6; ss << ","; ss << y6; ss << ","; ss << z6; ss << '\n';
            ss << x7; ss << ","; ss << y7; ss << ","; ss << z7; ss << '\n';
            ss << x8; ss << ","; ss << y8; ss << ","; ss << z8; ss << '\n';
            ss << x9; ss << ","; ss << y9; ss << ","; ss << z9; ss << '\n';

            std::string s = ss.str();
            ss.clear();
            f << s;

        }
    }

    f.close();
}


int main(int argc, char *argv[]) {

    if(argv[1] == "sphere"){
        if(argc == 6){
		    sphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]),argv[5]);
	    }
	    else
		    printf("NUMERO DE ARGUMENTOS INCORRETOS!");
    }
    else if(argv[1]=="plane"){
        if(argc == 5){
		    plane(atoi(argv[2]), atoi(argv[3]), argv[4]);
	    }
	    else
		    printf("NUMERO DE ARGUMENTOS INCORRETOS!");
    }
    else if(argv[1]=="box"){
        if(argc == 5){
		    box(atoi(argv[2]), atoi(argv[3]), argv[4]);
	    }
	    else
		    printf("NUMERO DE ARGUMENTOS INCORRETOS!");
    }
    else if(argv[1]=="cone"){
        if(argc == 7){
		    cone(atof(argv[2]),atof(argv[3]), atoi(argv[4]), atoi(argv[5]),argv[6]);
	    }
	    else
		    printf("NUMERO DE ARGUMENTOS INCORRETOS!");
    }
    else{
        printf("FIGURA NÃO IMPLEMENTADA");
    }

	return 1;
}
