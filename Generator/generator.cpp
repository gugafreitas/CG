#include "generator.h"

using namespace std;
string fileName;

string converte(float x, float y, float z){
    return to_string(x) + " " + to_string(y) + " " + to_string(z);
}

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

float* formulaBezier( float tt, float *p1 , float *p2 , float *p3 , float *p4) {

	float ite = 1.0 - tt;
	float* ppt = new float[3];

	float x0 , x1 , x2 , x3;
	x0 = pow(ite,3);
	x1 = 3 * tt*pow(ite,2);
	x2 = 3 * tt * tt * ite;
	x3 = tt * tt * tt;

	ppt[0] = x0*p1[0] + x1*p2[0] + x2*p3[0] + x3*p4[0];
	ppt[1] = x0*p1[1] + x1*p2[1] + x2*p3[1] + x3*p4[1];
	ppt[2] = x0*p1[2] + x1*p2[2] + x2*p3[2] + x3*p4[2];


	return ppt;
}

float* bezier( float a , float b , int* indice , float** pontos , int ni , int np) {

	float* ponto = new float[3];
	float altp[4][3];
	float res[4][3];
	int i , j = 0 , x = 0;
	float *calculo;


	for( i = 0 ; i < 16 ; i++) {
		altp[j][0] = pontos[indice[i]][0];
		altp[j][0] = pontos[indice[i]][1];
		altp[j][0] = pontos[indice[i]][2];

		j++;

		if( j % 4 == 0 ) {
			ponto = formulaBezier(a,altp[0],altp[1],altp[2],altp[3]);
			res[x][0] = ponto[0];
			res[x][1] = ponto[1];
			res[x][2] = ponto[2];

			x++;

			j = 0;
		}

	}
	calculo = formulaBezier(b,res[0],res[1],res[2],res[3]);

	return calculo;
}

void patch( string file , int tess , string name) {

	//abrir ficheiros de input e output

	ofstream fileo(name);
	string line , aux;
	ifstream filei(file);
	int i;

	//get patch
	if(filei.is_open()) {
		getline(filei,line);
		int npatch = atoi(line.c_str());
		int** indices = new int*[npatch];
		cout << npatch << endl;

		for(int r = 0 ; r < npatch ; r++) {
			getline(filei,line);
			indices[r] = new int[16];

			for(int j = 0 ; j < 16 ; j++) {
				i = line.find(",");
				aux = line.substr(0,i);
				indices[r][j] = atoi(aux.c_str());
				line.erase(0, i + 1);
			} 
		}

		getline(filei,line);
		int npontos = atoi(line.c_str());
		cout << npontos << endl;
		float** pontos = new float*[npontos];

        //get pontos
		for( int m = 0 ; m < npontos ; m++){
			getline(filei,line);
			pontos[m] = new float[3];
			for( int l = 0 ; l < 3 ; l++) {
				i = line.find(",");
				aux = line.substr(0,i);
				pontos[m][l] = atof(aux.c_str());
				line.erase(0 , i + 1);
			}
		}

		float incre = 1.0 / tess , u , v , u2 , v2;
		float *** pontoRes = new float**[npatch];

		for(int rr = 0 ; rr < npatch ; rr++) {
			pontoRes[rr] = new float*[4];
		 	//escrever pontos
		 	for( int jj = 0 ; jj < tess ; jj++) {

		 		for( int mn = 0 ; mn < tess ; mn++) {

		 			u = jj*incre;
		 			v = mn*incre;
		 			u2 = (jj + 1)* incre;
		 			v2 = (mn + 1)* incre;

		 			pontoRes[rr][0] = bezier(u, v, indices[rr], pontos, npatch, npontos);
					pontoRes[rr][1] = bezier(u, v2, indices[rr], pontos, npatch, npontos);
					pontoRes[rr][2] = bezier(u2, v, indices[rr], pontos, npatch, npontos);
					pontoRes[rr][3] = bezier(u2, v2, indices[rr], pontos, npatch, npontos);

                    fileo << pontoRes[rr][0][0] << "," << pontoRes[rr][0][1] << "," << pontoRes[rr][0][2] << endl;
					fileo << pontoRes[rr][2][0] << "," << pontoRes[rr][2][1] << "," << pontoRes[rr][2][2] << endl;
					fileo << pontoRes[rr][3][0] << "," << pontoRes[rr][3][1] << "," << pontoRes[rr][3][2] << endl;

					fileo << pontoRes[rr][0][0] << "," << pontoRes[rr][0][1] << "," << pontoRes[rr][0][2] << endl;
					fileo << pontoRes[rr][3][0] << "," << pontoRes[rr][3][1] << "," << pontoRes[rr][3][2] << endl;
					fileo << pontoRes[rr][1][0] << "," << pontoRes[rr][1][1] << "," << pontoRes[rr][1][2] << endl;
		 		}
		 	}

		 }
	}

	filei.close();
	fileo.close();
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
    else if(strcmp(argv[1],"Patch")==0){
        if(argc == 5){
            patch(argv[2], atoi(argv[3]), argv[4]);
        }
        else
            printf("NUMERO DE ARGUMENTOS INCORRETOS!");
    }
    else{
        printf("FIGURA NÃO IMPLEMENTADA");
    }

	return 1;
}
