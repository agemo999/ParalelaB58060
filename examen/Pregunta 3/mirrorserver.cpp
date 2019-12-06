#include <iostream>
#include "Socket.h"
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sstream> 
using namespace std;


int Collatz(int numero){
    int tempnum=numero;
    int veces=0;
    while(tempnum!=1){

        if(tempnum%2==0){
            tempnum=tempnum/2;
            veces++;
            
        }else{

            tempnum=3*tempnum+1;
            veces++;
        }


    }



return veces;

}


int main()
{

    // Este servidor refleja la informacion que le llega (mirror)
   int childpid;
   char a2[512];
   Socket s1('s',false), *s2;

   s1.Bind( 9876 );		// Port to access this mirror server
   s1.Listen( 5 );		// Set backlog queue to 5 conections

   for( ; ; ) {
      s2 = s1.Accept();
      // Wait for a conection
      childpid = fork();	// Create a child to serve the request
      if ( childpid < 0 )
         perror("server: fork error");
      else if (0 == childpid) {  // child code
              s1.Close();	// Close original socket in child
              memset(a2, 0, 512);
              s2->obtenermensaje( a2, 512 ); // Read a string from client
	      string s = a2; 
       	      stringstream geek(s); 
	      int x = 0; 
	      geek >> x;
	      int finx=Collatz(x);
	      stringstream ss;
	      ss << finx;
	      string a2 = ss.str();	
              s2->enviarmensaje( a2 );	// Write it back to client
              exit( 0 );	// Exit
      }
      s2->Close();		// Close socket in parent
   }


    return 0;
}
