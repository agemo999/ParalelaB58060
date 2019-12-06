#include <iostream>
#include "Socket.h"
#include <sys/socket.h>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
Socket::Socket( char t='s', bool ipv6 = false )//crea el socketa
{
    sock=socket(PF_INET, SOCK_STREAM, 0);


    if(sock<0){

        perror("error opening socket");
        exit(0);

    }

}

int Socket::Conectar(string Host1, int Port){//conecta al socket usando un ip y puerto
    port=Port;
    char *Host = new char[Host1.length() + 1];
    strcpy(Host, Host1.c_str());
    struct sockaddr_in host_addr;
    host_addr.sin_family = AF_INET;
    inet_aton( Host,  &host_addr.sin_addr );
    host_addr.sin_port = htons( Port );serv_addr.sin_port=htons(port);
    int len = sizeof( host_addr );
    int b=connect( sock, (sockaddr *) & host_addr, len );
    port=Port;

        return b;




}



int Socket::obtenermensaje(char * text, int len){//lee un mensaje del server


    int b=read(sock, text, len);
    return b;

}

int Socket::enviarmensaje(string text){//envia un mensaje al server
    const char * mensaje = text.c_str();
    int len=(int)strlen(mensaje);
    int n=write(sock,mensaje,len);
     if(n<0){

            perror("error in writing msg");
            exit(0);

    }
    return n;

}



int Socket::Shutdown( int ){//apaga el socket
    int n=shutdown(sock, SHUT_WR);
    if(n<0){

            perror("error shutting down socket");
            exit(0);

    }
    return n;

}

int Socket::Close(){//cierra el socket
    int n=close(sock);
    if(n<0){

            perror("error Closing socket");
            exit(0);

    }
    return n;

}


//para server
int Socket::Listen(int Queue){//espera a recibir datos


    int n=listen(sock, Queue);
    if(n<0){

            perror("error on Listen method");
            exit(0);

    }
    return n;


}


int Socket::Bind(int Port){//hace link cliente server

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl( INADDR_ANY );
    server_addr.sin_port = htons( Port );
    int len = sizeof( server_addr );
    int n= bind( sock, (const sockaddr *) & server_addr, len );
    if(n<0){

            perror("error on Bind method");
            exit(0);

    }
    return n;

}
Socket * Socket::Accept(){//acepta lo que se envia y devuelve un socket con la info

    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    addr_size = sizeof their_addr;
    int n = accept(sock, (struct sockaddr *)&their_addr, &addr_size);
    if (n < 0) {
        exit(0);
        perror("error on Accept method");
    }
    Socket *newSocket = new Socket('s', false);
    newSocket->sock=n;
    newSocket->port=port;

    return newSocket;




}
Socket::~Socket()
{
    //close();
}
