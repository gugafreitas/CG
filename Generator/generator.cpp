#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <stdlib.h>

//generator plane 1 3 plane.3d
void plane(int lado, int divs, string nome){
    ofstream file(nome); //cria um ficheiro, caso não exista, com o nome do parâmetro nome
    float x,y,z;
    y=0;

    //posicionamento do plano centrado com o eixo
    if ((lado % 2) == 0){
        x = (float)lado / 2;
        z = (float)lado / 2;
    }
    else{
        x = (float)lado / 2 + 0.5;
        z = (float)lado / 2 + 0.5;
    }

    //Triangulo 1
    printf("%f %f %f\n", x,y,z);
        file << x << "," << y << "," << z << endl;
    printf("%f %f %f\n", x,y,z);
        file << x << "," << y << "," << -z << endl;
    printf("%f %f %f\n", x,y,z);
        file << -x << "," << y << "," << -z << endl;

    
    // Triangulo 2
	printf("%f %f %f\n",-x,y,z);
		file << -x << "," << y << "," << z << endl;
	printf("%f %f %f\n",x,y,z);
		file << x << "," << y << "," << z << endl;
	printf("%f %f %f\n",-x,y,-z);
		file << -x << "," << y << "," << -z << endl;


	file.close();
}

void fazEsfera(float raio,int slices,int stacks,char *file){

	FILE *fp = fopen(file, "w");

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

			fprintf(fp,"%f,%f,%f\n",x1,yBase,z1);
			fprintf(fp,"%f,%f,%f\n",x2,yAcima,z2);
			fprintf(fp,"%f,%f,%f\n",x3,yBase,z3);
			fprintf(fp,"%f,%f,%f\n",x3,yBase,z3);
			fprintf(fp,"%f,%f,%f\n",x2,yAcima,z2);
			fprintf(fp,"%f,%f,%f\n",x4,yAcima,z4);

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

			fprintf(fp,"%f,%f,%f\n",x1,yBase,z1);
			fprintf(fp,"%f,%f,%f\n",x3,yBase,z3);
			fprintf(fp,"%f,%f,%f\n",x2,yAcima,z2);			
			fprintf(fp,"%f,%f,%f\n",x3,yBase,z3);
			fprintf(fp,"%f,%f,%f\n",x4,yAcima,z4);
			fprintf(fp,"%f,%f,%f\n",x2,yAcima,z2);
		}
	}
	fclose(fp);
}



int main(int argc, char *argv[]) {//1-Raio_2-Slices_3-Stacks_4-File

	if(argc == 5){
		fazEsfera(atof(argv[1]), atoi(argv[2]), atoi(argv[3]),argv[4]);
	}
	else
		printf("NUMERO DE ARGUMENTOS INCORRETOS!");


	return 1;
}
sphere.cpp
3 KB