#include <iostream>
#include "Socket.h"
#include <stdio.h>
#include <unistd.h>
using namespace std;




int main()
{

   Socket s('s',false);     // Crea un socket de IPv4, tipo "stream", valores predefinido
   string mensaje1;
   string ipcon;
   cout << "Escriba el ip del servidor a conectarse, por defecto esta usando el puerto 9876"  << '\n';
   getline (cin, ipcon);
   cout << "Escriba el mensaje que va a ser devuelto por el servidor, el maximo es 512 caracteres" << '\n';
   getline (cin, mensaje1);
   char buffer[ 512 ];
   s.Conectar( ipcon, 9876 ); // Same port as server
   s.enviarmensaje( mensaje1);		// send message
   s.obtenermensaje( buffer, 512 );	// Read the answer sent back from server
   cout << "He recibido del server el mensaje "  <<buffer<< endl;	// Print the string


    return 0;
}
