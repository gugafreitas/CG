#include "generator.h"

void plane(int lado, int divs, char* nome){
    //FILE *fp = fopen(nome, "w");
    float x,z,x1,z1,x2,z2,x3,z3,x4,z4;
    float aresta = lado/divs;
    std::ofstream f(nome);

    x= -(lado/2);
    z= -(lado/2);

    if((lado%2)!=0){
        x -= 0.5;
        z -= 0.5;
    }

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
            
            std::stringstream ss;
            ss << x1; ss << ",0,"; ss << z1; ss << '\n';
            ss << x3; ss << ",0,"; ss << z3; ss << '\n';
            ss << x2; ss << ",0,"; ss << z2; ss << '\n';
            
            ss << x1; ss << ",0,"; ss << z1; ss << '\n';
            ss << x4; ss << ",0,"; ss << z4; ss << '\n';
            ss << x3; ss << ",0,"; ss << z3; ss << '\n';
            
            std::string s = ss.str();
            ss.clear();
            f << s;
        }

    }

    f.close();
}

void sphere(float raio, int slices, int stacks, char* file) {

    std::ofstream f(file);

    float angBase = (2*M_PI)/slices;
    float angAltura = M_PI/stacks;

    float x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,z3,z4=0;

    for (int i=0;i<stacks;i++) {

        for (int j=0;j<slices;j++){

        x1 = raio * sin(i*angAltura) * sin(j*angBase);
        y1 = raio * cos(i*angAltura);
        z1 = raio * sin(i*angAltura) * cos(j*angBase);

        x2 = raio * sin((i+1)*angAltura) * sin((j+1)*angBase);
        y2 = raio * cos((i+1)*angAltura);
        z2 = raio * sin((i+1)*angAltura) * cos((j+1)*angBase);

        x3 = raio * sin((i+1)*angAltura) * sin(j*angBase);
        y3 = raio * cos((i+1)*angAltura);
        z3 = raio * sin((i+1)*angAltura) * cos(j*angBase);

        x4 = raio * sin(i*angAltura) * sin((j+1)*angBase);
        y4 = raio * cos(i*angAltura);
        z4 = raio * sin(i*angAltura) * cos((j+1)*angBase);

        std::stringstream ss;
        ss << x1; ss << ","; ss << y1; ss << ","; ss << z1; ss << '\n';
        ss << x2; ss << ","; ss << y2; ss << ","; ss << z2; ss << '\n';
        ss << x3; ss << ","; ss << y3; ss << ","; ss << z3; ss << '\n';
        ss << x1; ss << ","; ss << y1; ss << ","; ss << z1; ss << '\n';
        ss << x4; ss << ","; ss << y4; ss << ","; ss << z4; ss << '\n';
        ss << x2; ss << ","; ss << y2; ss << ","; ss << z2; ss << '\n';
        std::string s = ss.str();
        ss.clear();
        f << s;
        }        
    }
    f.close();
}

void cone(int radius, int height, int slices, int stacks, char* filePath){
    float sliceAngle = (float) (2 * M_PI) / slices;
    float stackSize = (float) height / stacks;
    float halfSize = (float) (-height) / 2;
    float radiusAux = (float) radius / stacks;
    std::ofstream f(filePath);
    //base
    for(float a = 0; a < (2 * M_PI); a += sliceAngle){
        float x1 = 0;
        float y1 = 0;
        float z1 = 0;

        float x3 = (float) radius * sin(a);
        float y3 = 0;
        float z3 = (float)radius * cos(a);

        float x2 = (float) radius * sin(a + sliceAngle);
        float y2 = 0;
        float z2 =(float) radius * cos(a + sliceAngle);



        std::stringstream ss;
        ss << x1; ss << ","; ss << y1; ss << ","; ss << z1; ss << '\n';
        ss << x3; ss << ","; ss << y3; ss << ","; ss << z3; ss << '\n';
        ss << x2; ss << ","; ss << y2; ss << ","; ss << z2; ss << '\n';


        std::string s = ss.str();
        ss.clear();
        f << s;

    }

    //altura
    for(int i = 0; i<stacks; i++){
        for(float a = 0; a < (2 * M_PI); a += sliceAngle){
            float yBaixo = i * stackSize;
            float yCima = (i + 1) * stackSize;

            float radiusBaixo = (float) radius - (i * radiusAux);
            float radiusCima = (float) radius - ((i + 1) * radiusAux);

            float x1 = radiusCima * sin(a);
            float y1 = yCima;
            float z1 = radiusCima * cos(a);

            float x2 = radiusBaixo * sin(a);
            float y2 = yBaixo;
            float z2 = radiusBaixo * cos(a);

            float x5 = radiusBaixo * sin(a + sliceAngle);
            float y5 = yBaixo;
            float z5 = radiusBaixo * cos(a + sliceAngle);


            float x3 = radiusCima * sin(a);
            float y3 = yCima;
            float z3 = radiusCima * cos(a);

            float x4 = radiusBaixo * sin(a + sliceAngle);
            float y4 = yBaixo;
            float z4 = radiusBaixo * cos(a + sliceAngle);

            float x6 = radiusCima * sin(a + sliceAngle);
            float y6 = yCima;
            float z6 = radiusCima * cos(a + sliceAngle);

            //float x10 = 0;
            //float y10 = height;
            //float z10 = 0;

            std::stringstream ss;
            ss << x1; ss << ","; ss << y1; ss << ","; ss << z1; ss << '\n';
            ss << x2; ss << ","; ss << y2; ss << ","; ss << z2; ss << '\n';
            ss << x5; ss << ","; ss << y5; ss << ","; ss << z5; ss << '\n';
            ss << x3; ss << ","; ss << y3; ss << ","; ss << z3; ss << '\n';
            ss << x4; ss << ","; ss << y4; ss << ","; ss << z4; ss << '\n';
            ss << x6; ss << ","; ss << y6; ss << ","; ss << z6; ss << '\n';
            //ss << x10; ss << ","; ss << y10; ss << ","; ss << z10; ss << '\n';
            std::string s = ss.str();
            ss.clear();
            f << s;

        }
    }

    f.close();
}

void box(double sideLength, int divisions, char *nome){
	double x, y, z, xx, yy, zz; //variaveis que variam ao longo dos eixos
	double espc, espl, espal; //espaçamento entre as divisions de sideLengthrimento, sideLengthura e 
	int i, j; //variáveis que serão usadas nos ciclos
	std::ofstream file(nome);

	//Espaçamentos
	espc = sideLength / divisions; 
	espl = sideLength / divisions; 
	espal = sideLength / divisions; 

	/*
	 * FACES DE CIMA E DE BAIXO
	 */
	y = sideLength / 2; yy = -y; //y é usado para indicar a sideLengthura da face de cima e yy é a sideLengthura a que a base de baixo se encontrará
	z = sideLength / 2;		 //a variável z assume metade do valor da sideLengthura, ficando o poligono centrado no eixo do z

	for (i = 0; i < divisions; i++){
		x = -(sideLength / 2);  //a variável x assume metade do valor do sideLengthrimento, ficando o poligono centrado no eixo do x
		xx = x + espc;   //incrementa também o xx, para andar sempre à frente do x, para fazer o triângulo
 		zz = z - espl;  //decrementa o z, pois temos o z com o seu valor maximo positivo e para o plano ficar centrado temos que ir tirando o espaçamento entre as divisions de sideLengthura
		for (j = 0; j < divisions; j++){

			
			file <<  x << "," << y << "," << z << std::endl;
			file << xx << "," << y << "," << z << std::endl;
			file << x << "," << y << "," << zz << std::endl;
			
			file << xx << "," << y << "," << z << std::endl;
			file << xx << "," << y << "," << zz << std::endl;
			file << x << "," << y << "," << zz << std::endl;

			file << x << "," << yy << "," << z << std::endl;
			file << x << "," << yy << "," << zz << std::endl;
			file << xx << "," << yy << "," << z << std::endl;
			
			file << xx << "," << yy << "," << z << std::endl;
			file << x << "," << yy << "," << zz << std::endl;
			file << xx << "," << yy << "," << zz << std::endl;

			x = x + espc;   //incrementa o x, sendo o x assumindo o valor na proxima camada
			xx = xx + espc;//incrementa também o xx, para andar sempre à frente do x, para fazer o triângulo
		}
		z = z - espl;// z vai decrementando sempre o valor do espaçamento lateral, para ficar com as divisions certas na sideLengthura
	}


	
	x = -(sideLength / 2); // face da esqueda
	xx = -x; // face da direita
	y = -(sideLength / 2);//a sideLengthura onde se iniciam as faces laterais

	for (i = 0; i < divisions; i++){
		z = sideLength / 2;    //a variável z assume metade do valor da sideLengthura, ficando o poligono centrado no eixo do z
		zz = z - espl;  //decrementa o z, pois temos o z com o seu valor maximo positivo e para o plano ficar centrado temos que ir tirando o espaçamento entre as divisions de sideLengthura
		yy = y + espal;//para o poligono ficar centrado, começamos com y negativo, sendo o seu valor metade da sideLengthura

		for (j = 0; j < divisions; j++){
			
			file << x << "," << y << "," << z << std::endl;
			file << x << "," << yy << "," << z << std::endl;
			file << x << "," << yy << "," << zz << std::endl;

			file << x << "," << y << "," << zz << std::endl;
			file << x << "," << y << "," << z << std::endl;
			file << x << "," << yy << "," << zz << std::endl;

			
			file << xx << "," << y << "," << z << std::endl;
			file << xx << "," << y << "," << zz << std::endl;
			file << xx << "," << yy << "," << zz << std::endl;

			file << xx << "," << y << "," << z << std::endl;
			file << xx << "," << yy << "," << zz << std::endl;
			file << xx << "," << yy << "," << z << std::endl;

			z = z - espl;   // z vai decrementando sempre o valor do espaçamento lateral, para ficar com as divisions certas na sideLengthura
			zz = zz - espl;//decrementa o z, pois temos o z com o seu valor maximo positivo e para o plano ficar centrado temos que ir tirando o espaçamento entre as divisions de sideLengthura
		}
		y = y + espal;//incrementar na sideLengthura o valor do espaçamento, para obter nessa sideLengthura as divisions indicadas	
	}

	

	z = sideLength / 2; //Face da frente
	zz = -z; // Face trás
	y = -(sideLength / 2); //sideLengthura que se inicia as divisions frente e trás

	for (i = 0; i < divisions; i++){
		x = -(sideLength / 2);  //valor da coordenada x, onde se começam a desenhar os triângulos
		xx = x + espc;   //valor do x na proxima camada de sideLengthrimento
		yy = y + espal; //valor do y na proxima camada de sideLengthura

		for (j = 0; j < divisions; j++){
			
			file << x << "," << y << "," << z << std::endl;
			file << xx << "," << y << "," << z << std::endl;
			file << x << "," << yy << "," << z << std::endl;

			file << xx << "," << y << "," << z << std::endl;
			file << xx << "," << yy << "," << z << std::endl;
			file << x << "," << yy << "," << z << std::endl;

			file << x << "," << y << "," << zz << std::endl;
			file << x << "," << yy << "," << zz << std::endl;
			file << xx << "," << y << "," << zz << std::endl;

			file << xx << "," << y << "," << zz << std::endl;
			file << x << "," << yy << "," << zz << std::endl;
			file << xx << "," << yy << "," << zz << std::endl;

			x = x + espc;    //x vai incrementando o valor do espaçamento do sideLengthrimento, para ficar com as divisions indicadas
			xx = xx + espc; //xx também incrementa o valor do espaçamento do sideLengthrimento, para ficar sempre na proxima camada no eixo do x	
		}
		y = y + espal; //incrementar na sideLengthura o valor do espaçamento, para obter nessa sideLengthura as divisions indicadas	
	}
	file.close();
}

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
    else if(strcmp(argv[1],"box")==0){
        if(argc == 5){
		    box(atoi(argv[2]), atoi(argv[3]), argv[4]);
	    }
	    else
		    printf("NUMERO DE ARGUMENTOS INCORRETOS!");
    }
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
