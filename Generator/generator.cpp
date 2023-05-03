#include "generator.h"
#include "../Engine/ponto.h"

using namespace std;

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
	double x, y, z, xx, yy, zz;
	double espc, espl, espal; 
	int i, j; 
	std::ofstream file(nome);

	//Espaçamentos
	espc = sideLength / divisions; 
	espl = sideLength / divisions; 
	espal = sideLength / divisions; 

	/*
	 * FACES DE CIMA E DE BAIXO
	 */
	y = sideLength / 2; yy = -y;
	z = sideLength / 2;

	for (i = 0; i < divisions; i++){
		x = -(sideLength / 2);
		xx = x + espc;
 		zz = z - espl;
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

			x = x + espc;
			xx = xx + espc;
		}
		z = z - espl;
	}


	
	x = -(sideLength / 2);
	xx = -x;
	y = -(sideLength / 2);

	for (i = 0; i < divisions; i++){
		z = sideLength / 2;   
		zz = z - espl;  
		yy = y + espal;

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

			z = z - espl;
			zz = zz - espl;
		}
		y = y + espal;	
	}

	

	z = sideLength / 2;
	zz = -z;
	y = -(sideLength / 2);

	for (i = 0; i < divisions; i++){
		x = -(sideLength / 2);
		xx = x + espc;
		yy = y + espal;

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

			x = x + espc;
			xx = xx + espc;
		}
		y = y + espal;
	}
	file.close();
}

Ponto calcula(vector<int> patch, vector<Ponto*> pontos, float u, float v) {



    float coef1 = (1 - u) * (1 - u) * (1 - u);
    float coef2 = 3 * (1 - u) * (1 - u) * u;
    float coef3 = 3 * (1 - u) * u * u;
    float coef4 = u * u * u;

    float x1 = coef1 * pontos[patch[0]]->getX() + coef2 * pontos[patch[1]]->getX() + coef3 * pontos[patch[2]]->getX() + coef4 * pontos[patch[3]]->getX();
    float x2 = coef1 * pontos[patch[4]]->getX() + coef2 * pontos[patch[5]]->getX() + coef3 * pontos[patch[6]]->getX() + coef4 * pontos[patch[7]]->getX();
    float x3 = coef1 * pontos[patch[8]]->getX() + coef2 * pontos[patch[9]]->getX() + coef3 * pontos[patch[10]]->getX() + coef4 * pontos[patch[11]]->getX();
    float x4 = coef1 * pontos[patch[12]]->getX() + coef2 * pontos[patch[13]]->getX() + coef3 * pontos[patch[14]]->getX() + coef4 * pontos[patch[15]]->getX();

    float y1 = coef1 * pontos[patch[0]]->getY() + coef2 * pontos[patch[1]]->getY() + coef3 * pontos[patch[2]]->getY() + coef4 * pontos[patch[3]]->getY();
    float y2 = coef1 * pontos[patch[4]]->getY() + coef2 * pontos[patch[5]]->getY() + coef3 * pontos[patch[6]]->getY() + coef4 * pontos[patch[7]]->getY();
    float y3 = coef1 * pontos[patch[8]]->getY() + coef2 * pontos[patch[9]]->getY() + coef3 * pontos[patch[10]]->getY() + coef4 * pontos[patch[11]]->getY();
    float y4 = coef1 * pontos[patch[12]]->getY() + coef2 * pontos[patch[13]]->getY() + coef3 * pontos[patch[14]]->getY() + coef4 * pontos[patch[15]]->getY();

    float z1 = coef1 * pontos[patch[0]]->getZ() + coef2 * pontos[patch[1]]->getZ() + coef3 * pontos[patch[2]]->getZ() + coef4 * pontos[patch[3]]->getZ();
    float z2 = coef1 * pontos[patch[4]]->getZ() + coef2 * pontos[patch[5]]->getZ() + coef3 * pontos[patch[6]]->getZ() + coef4 * pontos[patch[7]]->getZ();
    float z3 = coef1 * pontos[patch[8]]->getZ() + coef2 * pontos[patch[9]]->getZ() + coef3 * pontos[patch[10]]->getZ() + coef4 * pontos[patch[11]]->getZ();
    float z4 = coef1 * pontos[patch[12]]->getZ() + coef2 * pontos[patch[13]]->getZ() + coef3 * pontos[patch[14]]->getZ() + coef4 * pontos[patch[15]]->getZ();

    float Coef1 = (1 - v) * (1 - v) * (1 - v);
    float Coef2 = 3 * (1 - v) * (1 - v) * v;
    float Coef3 = 3 * (1 - v) * v * v;
    float Coef4 = v * v * v;

    float x = Coef1 * x1 + Coef2 * x2 + Coef3 * x3 + Coef4 * x4;
    float y = Coef1 * y1 + Coef2 * y2 + Coef3 * y3 + Coef4 * y4;
    float z = Coef1 * z1 + Coef2 * z2 + Coef3 * z3 + Coef4 * z4;

    return Ponto(x, y, z);

}

void curvaBezier(vector<Ponto>* vertices, std::vector<int> patch, std::vector<Ponto*> pontosControlo, float u, float v, float intervalo) {

    Ponto p1 = calcula(patch, pontosControlo, u, v);
    Ponto p2 = calcula(patch, pontosControlo, u, v + intervalo);
    Ponto p3 = calcula(patch, pontosControlo, u + intervalo, v);
    Ponto p4 = calcula(patch, pontosControlo, u + intervalo, v + intervalo);

    vertices->push_back(p1);
    vertices->push_back(p4);
    vertices->push_back(p2);

    vertices->push_back(p4);
    vertices->push_back(p1);
    vertices->push_back(p3);
}

//faz a leitura do ficheiro .patch
void drawBezierPatches(string ficheiro, int nivel, string origem) {
    float intervalo = (float)1.0 / nivel;
    string linha;
    std::vector<std::vector<int>> patches;
    std::vector<Ponto*> pontosControlo;
    std::vector<Ponto> resultado;

    //abrir o ficheiro
    ifstream file1(ficheiro);
    if (!file1.is_open()) { cout << "Erro ao ler o ficheiro paches" << endl; return; }
    //pega na primeira linha que é o número de patches ou seja numero de linhas a ler 
    getline(file1, linha);
    int nPatches = atoi(linha.c_str());

    int t;
    for (int i = 0; i < nPatches; i++) {
        getline(file1, linha);     //pegar na linha atual
        stringstream strstream(linha);
        patches.push_back(std::vector<int>());
        while (strstream >> t) {	// retirar as ,
            patches[i].push_back(t);
            if (strstream.peek() == ',') {
                strstream.ignore();
            }
        }
    }
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
