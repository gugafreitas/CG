
class Rotacao{
    float ex;
    float ey;
    float ez;
    float angle;

    public:
        Rotacao();
        Rotacao(float,float,float,float);

        float getEx()
        {return ex;}
        void setEx(float a)
        {ex=a;}

        float getEy()
        {return ey;}
        void setEy(float a)
        {ey=a;}

        float getEz()
        {return ez;}
        void setEz(float a)
        {ez=a;}

};