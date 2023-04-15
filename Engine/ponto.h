

class Ponto{
    float x;
    float y;
    float z;

    public:
        Ponto();
        Ponto(float,float,float);

        float getX()
        {return x;}
        void setX(float a)
        {x=a;}

        float getY()
        {return y;}
        void setY(float a)
        {y=a;}

        float getZ()
        {return z;}
        void setZ(float a)
        {z=a;}

};