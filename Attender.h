//Clase para manejar las personas que atienden a los conciertos, se le agrega un id unico a cada uno

#ifndef _STORE_
#define _STORE_ 1

using namespace std;

class Attender{

private:
    int attID;
    int countAtt=0;
public:
    Attender(){
        attID = 0+countAtt;
        countAtt++;
    };
    int getId(){
        return attID;
    }

};


#endif