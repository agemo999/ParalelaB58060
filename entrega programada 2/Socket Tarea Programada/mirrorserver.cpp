#include <iostream>
#include "Socket.h"
#include <stdio.h>
#include <unistd.h>
#include <cstring>
using namespace std;




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
              s2->enviarmensaje( a2 );	// Write it back to client
              exit( 0 );	// Exit
      }
      s2->Close();		// Close socket in parent
   }


    return 0;
}
