#include <iostream>
#include <chrono>
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

int Collatz(int numero){
    int tempnum=numero;
    int veces=0;
    while(tempnum!=1){

        if(tempnum%2==0){
            tempnum=tempnum/2;
            veces++;
            cout <<"La operacion es la del par "<<GREEN<< tempnum <<BLACK<< " se ha iterado un total de "<< veces<<" veces!"<<std::endl;
        }else{

            tempnum=3*tempnum+1;
            cout <<"La operacion es la del impar "<<RED<< tempnum <<BLACK<< " se ha iterado un total de "<< veces<<" veces!"<<std::endl;
            veces++;
        }


    }



return veces;

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
    int numero=Collatz(coll);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Se hizo un total de " <<numero <<" iteraciones y se tardo "<< duration.count() <<" microsegundos."<<endl;

    return 0;
}
