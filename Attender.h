//Clase para manejar las personas que atienden a los conciertos, cada equivale a 50 personas, de esa manera se reduce el gasto de memoria

#ifndef __ATTENDER__
#define __ATTENDER__ 1

using namespace std;

class AttenderGroup{

private:
        int groupID;
        int countAt=0;
        int size=50;

    public:
        AttenderGroup(int size)
        {
            groupID = 10+countAt++;
            this->size=size;
        };
        int getId(){
            return groupID;
        }
        int getSize() const {
            return size;
        }


};


#endif