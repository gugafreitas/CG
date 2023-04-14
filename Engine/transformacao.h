#pragma once


class Transformacao{
    float translacaoX;
    float translacaoY;
    float translacaoZ;
    float rotacaoX;
    float rotacaoY;
    float rotacaoZ;
    float rotacaoAngle;
    float escalaX;
    float escalaY;
    float escalaZ;

    public:
        Transformacao();
        Transformacao(float,float,float,float,float,float,float,float,float,float);

        float getTranslacaoX()
        {return translacaoX;}
        void setTranslacaoX(float a)
        {translacaoX=a;}
        void sumTranslacaoX(float a)
        {translacaoX+=a;}

        float getTranslacaoY()
        {return translacaoY;}
        void setTranslacaoY(float a)
        {translacaoY=a;}
        void sumTranslacaoY(float a)
        {translacaoY+=a;}

        float getTranslacaoZ()
        {return translacaoZ;}
        void setTranslacaoZ(float a)
        {translacaoZ=a;}
        void sumTranslacaoZ(float a)
        {translacaoZ+=a;}

        float getRotacaoX()
        {return rotacaoX;}
        void setRotacaoX(float a)
        {rotacaoX=a;}
        void sumRotacaoX(float a)
        {rotacaoX+=a;}
        
        float getRotacaoY()
        {return rotacaoY;}
        void setRotacaoY(float a)
        {rotacaoY=a;}
        void sumRotacaoY(float a)
        {rotacaoY+=a;}

        float getRotacaoZ()
        {return rotacaoZ;}
        void setRotacaoZ(float a)
        {rotacaoZ=a;}
        void sumRotacaoZ(float a)
        {rotacaoZ+=a;}

        float getRotacaoAngle()
        {return rotacaoAngle;}
        void setRotacaoAngle(float a)
        {rotacaoAngle=a;}
        void sumRotacaoAngle(float a)
        {rotacaoAngle+=a;}

        float getEscalaX()
        {return escalaX;}
        void setEscalaX(float a)
        {escalaX=a;}
        void sumEscalaX(float a)
        {escalaX=escalaX*a;}

        float getEscalaY()
        {return escalaY;}
        void setEscalaY(float a)
        {escalaY=a;}
        void sumEscalaY(float a)
        {escalaY=escalaY*a;}

        float getEscalaZ()
        {return escalaZ;}
        void setEscalaZ(float a)
        {escalaZ=a;}
        void sumEscalaZ(float a)
        {escalaZ=escalaZ*a;}
};