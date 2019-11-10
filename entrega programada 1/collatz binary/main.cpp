#include <iostream>
#include <chrono>
#include <bitset>
#include <sstream>

#define BLACK "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"

using namespace std;
using namespace std::chrono;

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> SOURCES\n"
              << "\t-h\t\tShow this help message\n"
              << "\tInteger Number for the collatz to work on \tRemember to use int for it to work"
              << std::endl;
}

int Add(unsigned int x, unsigned int y)
{
    // Iterate till there is no carry
    while (y != 0)
    {
        // carry now contains common
        //set bits of x and y
        int carry = x & y;

        // Sum of bits of x and y where at
        //least one of the bits is not set
        x = x ^ y;

        // Carry is shifted by one so that adding
        // it to x gives the required sum
        y = carry << 1;
    }
    return x;
}


int Collatz(unsigned int numero){
    unsigned int tempnum=numero;
    int veces=0;
    while(tempnum!=1){

        if((tempnum&1)==0){

            tempnum=tempnum>>1;
            veces++;
            cout <<"La operacion es la del par "<<GREEN<< tempnum <<BLACK<< " se ha iterado un total de "<< veces<<" veces!"<<std::endl;
        }else{
            unsigned int multiply=tempnum<<1;
            unsigned int addi=multiply|1;
            unsigned int addoub=Add(addi,tempnum);
            tempnum=addoub;
            veces++;
            cout <<"La operacion es la del impar "<<RED<< tempnum <<BLACK<< " se ha iterado un total de "<< veces<<" veces!"<<std::endl;

        }


    }



return veces;

}


std::string toBinary(int n)
{
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}


int main(int argc, char** argv)
{

    if (argc < 2) { //para poder agregar los argumentos o el mensaje de ayuda
            show_usage(argv[0]);
            return 1;
        }
        string archivo = "";
        int coll=0;
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if ((arg == "-h") || (arg == "--help")) {
                show_usage(argv[0]);
                return 0;
            } else {
                stringstream geek(argv[1]);

                geek >> coll;

            }
        }

    auto start = high_resolution_clock::now();
    unsigned int numero=Collatz(coll);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Se hizo un total de " <<numero <<" iteraciones y se tardo "<< duration.count() <<" microsegundos."<<endl;


    return 0;
}
