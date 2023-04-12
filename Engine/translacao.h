class translacao{
    float xt;
    float yt;
    float zt;

    public:
        Translacao();
        Translacao(float x, float y, float z);

        float getXT(){
            return xt;
        }

        void setXT(float x){
            this->xt = x;
        }

        float getYT(){
            return yt;
        }

        void setYT(float y){
            this->yt = y;
        }

        float getZT(){
            return zt;
        }

        void setZT(float z){
            this->zt = z;
        }
};