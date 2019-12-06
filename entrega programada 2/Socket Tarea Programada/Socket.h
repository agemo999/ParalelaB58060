#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>
using namespace std;

class Socket
{
    public:
        Socket( char t, bool ipv6);
        int Conectar(string Host1, int Port);
        int obtenermensaje(char * text, int len);
        int enviarmensaje(string text);
        int Shutdown( int );
        int Close();
        int readLine(int fd, char *buf, size_t n);
        //para server
        int Bind(int Port);
        int Listen(int Queue);
        Socket * Accept();
        virtual ~Socket();

    protected:

    private:
        int sock;
        struct sockaddr_in serv_addr;
        struct hostent *server;
        int port;


/* Internet address. */


};

#endif // SOCKET_H
