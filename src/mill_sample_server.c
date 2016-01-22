/*
    Compile with:
        gcc -o mill_sample_server mill_sample_server.c -lmill
*/
#include <libmill.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int port = 5555;
    if(argc > 1)
        port = atoi(argv[1]);

    ipaddr  addr    = iplocal(NULL, port, 0);
    tcpsock ls      = tcplisten(addr, 10);
    if(!ls) 
    {
        perror("Can't open listening socket");
        return 1;
    } 

    while(1)
    {
        tcpsock as = tcpaccept(ls, -1);
        printf("New connection!\n");

        tcpsend(as, "What's your name?\r\n", 19, -1);
        tcpflush(as, -1);

        tcpclose(as);
    }

    return 0;
}


