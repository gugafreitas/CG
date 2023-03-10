#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

// //generator plane 1 3 plane.3d
// void plane(int lado, int divs, char* nome){
// 	//FILE *fp = fopen(nome, "w");
//     std::ofstream f(nome);
//     float x,z,x1,z1,x2,z2,x3,z3,x4,z4;
//     float aresta = lado/divs;

//     x= -(lado/2);
//     z= -(lado/2);

//     for(int i=0;i<divs;i++){

//         for(int j=0;j<divs;j++){

//             std::stringstream ss;
                
//             z1 = z + (i*aresta);
//             x1 = x + (j*aresta);

//             z2 = z1;
//             x2 = x1 + aresta;

//             z3 = z1 + aresta;
//             x3 = x1 + aresta;

//             z4 = z1 + aresta;
//             x4 = x1;

//             ss << x1; ss << ","; ss << "0,"; ss << z1; ss << '\n';
//             ss << x2; ss << ","; ss << "0,"; ss << z2; ss << '\n';
//             ss << x3; ss << ","; ss << "0,"; ss << z3; ss << '\n';
//             ss << x1; ss << ","; ss << "0,"; ss << z1; ss << '\n';
//             ss << x3; ss << ","; ss << "0,"; ss << z3; ss << '\n';
//             ss << x4; ss << ","; ss << "0,"; ss << z4; ss << '\n';

//             std::string s = ss.str();
//             ss.clear();
//             f << s;
//         }

//     }

//     f.close();
// }

void plane(int lado, int divs, char* nome){
    FILE *fp = fopen(nome, "w");
    float x,z,x1,z1,x2,z2,x3,z3,x4,z4;
    float aresta = lado/divs;

    x= -(lado/2);
    z= -(lado/2);

    for(int i=0;i<divs;i++){

        for(int j=0;j<divs;j++){

            z1 = z + (aresta);
            x1 = x + (j*aresta);

            z2 = z1;
            x2 = x1 + aresta;

            z3 = z1 + aresta;
            x3 = x1 + aresta;

            z4 = z1 + aresta;
            x4 = x1;

            fprintf(fp,"%f,%d,%f\n",x1,0,z1);
            fprintf(fp,"%f,%d,%f\n",x2,0,z2);
            fprintf(fp,"%f,%d,%f\n",x3,0,z3);
            fprintf(fp,"%f,%d,%f\n",x1,0,z1);
            fprintf(fp,"%f,%d,%f\n",x3,0,z3);
            fprintf(fp,"%f,%d,%f\n",x4,0,z4);
        }

    }
    fclose(fp);
}

void sphere(float raio,int slices,int stacks,char *file){

	//FILE *fp = fopen(file, "w");
    std::ofstream f(file);
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
	f.close();
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

// void generateBox(double comp, double larg, double alt, int camadas, char *nome){
// 	double x, y, z, xx, yy, zz; //variaveis que variam ao longo dos eixos
// 	double espc, espl, espal; //espaçamento entre as camadas de comprimento, largura e 
// 	int i, j; //variáveis que serão usadas nos ciclos
// 	std::ofstream file(nome);

// 	//Espaçamentos
// 	espc = comp / camadas; 
// 	espl = larg / camadas; 
// 	espal = alt / camadas; 

// 	/*
// 	 * FACES DE CIMA E DE BAIXO
// 	 */
// 	y = alt / 2; yy = -y; //y é usado para indicar a altura da face de cima e yy é a altura a que a base de baixo se encontrará
// 	z = larg / 2;		 //a variável z assume metade do valor da largura, ficando o poligono centrado no eixo do z

// 	for (i = 0; i < camadas; i++){
// 		x = -(comp / 2);  //a variável x assume metade do valor do comprimento, ficando o poligono centrado no eixo do x
// 		xx = x + espc;   //incrementa também o xx, para andar sempre à frente do x, para fazer o triângulo
//  		zz = z - espl;  //decrementa o z, pois temos o z com o seu valor maximo positivo e para o plano ficar centrado temos que ir tirando o espaçamento entre as camadas de largura
// 		for (j = 0; j < camadas; j++){

			
// 			printf("%f %f %f\n", x, y, z); file <<  x << "," << y << "," << z << std::endl;
// 			printf("%f %f %f\n", xx, y, z); file << xx << "," << y << "," << z << std::endl;
// 			printf("%f %f %f\n", x, y, zz); file << x << "," << y << "," << zz << std::endl;
			
// 			printf("%f %f %f\n", xx, y, z); file << xx << "," << y << "," << z << std::endl;
// 			printf("%f %f %f\n", xx, y, zz); file << xx << "," << y << "," << zz << std::endl;
// 			printf("%f %f %f\n", x, y, zz); file << x << "," << y << "," << zz << std::endl;

// 			printf("%f %f %f\n", x, yy, z); file << x << "," << yy << "," << z << std::endl;
// 			printf("%f %f %f\n", x, yy, zz); file << x << "," << yy << "," << zz << std::endl;
// 			printf("%f %f %f\n", xx, yy, z); file << xx << "," << yy << "," << z << std::endl;
			
// 			printf("%f %f %f\n", xx, yy, z); file << xx << "," << yy << "," << z << std::endl;
// 			printf("%f %f %f\n", x, yy, zz); file << x << "," << yy << "," << zz << std::endl;
// 			printf("%f %f %f\n", xx, yy, zz); file << xx << "," << yy << "," << zz << std::endl;

// 			x = x + espc;   //incrementa o x, sendo o x assumindo o valor na proxima camada
// 			xx = xx + espc;//incrementa também o xx, para andar sempre à frente do x, para fazer o triângulo
// 		}
// 		z = z - espl;// z vai decrementando sempre o valor do espaçamento lateral, para ficar com as camadas certas na largura
// 	}


	
// 	x = -(comp / 2); // face da esqueda
// 	xx = -x; // face da direita
// 	y = -(alt / 2);//a altura onde se iniciam as faces laterais

// 	for (i = 0; i < camadas; i++){
// 		z = larg / 2;    //a variável z assume metade do valor da largura, ficando o poligono centrado no eixo do z
// 		zz = z - espl;  //decrementa o z, pois temos o z com o seu valor maximo positivo e para o plano ficar centrado temos que ir tirando o espaçamento entre as camadas de largura
// 		yy = y + espal;//para o poligono ficar centrado, começamos com y negativo, sendo o seu valor metade da altura

// 		for (j = 0; j < camadas; j++){
			
// 			printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z << std::endl;
// 			printf("%f %f %f\n", x, yy, z); file << x << "," << yy << "," << z << std::endl;
// 			printf("%f %f %f\n", x, yy, zz); file << x << "," << yy << "," << zz << std::endl;

// 			printf("%f %f %f\n", x, y, zz); file << x << "," << y << "," << zz << std::endl;
// 			printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z << std::endl;
// 			printf("%f %f %f\n", x, yy, zz); file << x << "," << yy << "," << zz << std::endl;

			
// 			printf("%f %f %f\n", xx, y, z); file << xx << "," << y << "," << z << std::endl;
// 			printf("%f %f %f\n", xx, y, zz); file << xx << "," << y << "," << zz << std::endl;
// 			printf("%f %f %f\n", xx, yy, zz); file << xx << "," << yy << "," << zz << std::endl;

// 			printf("%f %f %f\n", xx, y, z); file << xx << "," << y << "," << z << std::endl;
// 			printf("%f %f %f\n", xx, yy, zz); file << xx << "," << yy << "," << zz << std::endl;
// 			printf("%f %f %f\n", xx, yy, z); file << xx << "," << yy << "," << z << std::endl;

// 			z = z - espl;   // z vai decrementando sempre o valor do espaçamento lateral, para ficar com as camadas certas na largura
// 			zz = zz - espl;//decrementa o z, pois temos o z com o seu valor maximo positivo e para o plano ficar centrado temos que ir tirando o espaçamento entre as camadas de largura
// 		}
// 		y = y + espal;//incrementar na altura o valor do espaçamento, para obter nessa altura as camadas indicadas	
// 	}

	

// 	z = larg / 2; //Face da frente
// 	zz = -z; // Face trás
// 	y = -(alt / 2); //altura que se inicia as camadas frente e trás

// 	for (i = 0; i < camadas; i++){
// 		x = -(comp / 2);  //valor da coordenada x, onde se começam a desenhar os triângulos
// 		xx = x + espc;   //valor do x na proxima camada de comprimento
// 		yy = y + espal; //valor do y na proxima camada de altura

// 		for (j = 0; j < camadas; j++){
			
// 			printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z << std::endl;
// 			printf("%f %f %f\n", xx, y, z); file << xx << "," << y << "," << z << std::endl;
// 			printf("%f %f %f\n", x, yy, z); file << x << "," << yy << "," << z << std::endl;

// 			printf("%f %f %f\n", xx, y, z); file << xx << "," << y << "," << z << std::endl;
// 			printf("%f %f %f\n", xx, yy, z); file << xx << "," << yy << "," << z << std::endl;
// 			printf("%f %f %f\n", x, yy, z); file << x << "," << yy << "," << z << std::endl;

// 			printf("%f %f %f\n", x, y, zz); file << x << "," << y << "," << zz << std::endl;
// 			printf("%f %f %f\n", x, yy, zz); file << x << "," << yy << "," << zz << std::endl;
// 			printf("%f %f %f\n", xx, y, zz); file << xx << "," << y << "," << zz << std::endl;

// 			printf("%f %f %f\n", xx, y, zz); file << xx << "," << y << "," << zz << std::endl;
// 			printf("%f %f %f\n", x, yy, zz); file << x << "," << yy << "," << zz << std::endl;
// 			printf("%f %f %f\n", xx, yy, zz); file << xx << "," << yy << "," << zz << std::endl;

// 			x = x + espc;    //x vai incrementando o valor do espaçamento do comprimento, para ficar com as camadas indicadas
// 			xx = xx + espc; //xx também incrementa o valor do espaçamento do comprimento, para ficar sempre na proxima camada no eixo do x	
// 		}
// 		y = y + espal; //incrementar na altura o valor do espaçamento, para obter nessa altura as camadas indicadas	
// 	}
// 	file.close();
// }

// void box(float sideLength, int divisions) {
//     generateBox(sideLength, sideLength, sideLength, divisions);
// }

int main(int argc, char *argv[]) {

    if(strcmp(argv[1],"sphere")==0){
        if(argc == 6){
		    sphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]),argv[5]);
	    }
	    else
		    printf("NUMERO DE ARGUMENTOS INCORRETOS!");
    }
    else if(strcmp(argv[1],"plane")==0){
        if(argc == 5){
		    plane(atoi(argv[2]), atoi(argv[3]), argv[4]);
	    }
	    else
		    printf("NUMERO DE ARGUMENTOS INCORRETOS!");
    }
    // else if(strcmp(argv[1],"box")==0){
    //     if(argc == 5){
	// 	    box(atoi(argv[2]), atoi(argv[3]), argv[4]);
	//     }
	//     else
	// 	    printf("NUMERO DE ARGUMENTOS INCORRETOS!");
    // }
    else if(strcmp(argv[1],"cone")==0){
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