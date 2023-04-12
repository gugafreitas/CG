class Color{
    float c1;
    float c2;
    float c3;

    public:
        Color();
        Color(float,float,float);

        float getC1()
        {return c1;}
        void setC1(float a)
        {c1=a;}

        float getC2()
        {return c2;}
        void setC2(float a)
        {c2=a;}

        float getC3()
        {return c3;}
        void setC3(float a)
        {c3=a;}
};