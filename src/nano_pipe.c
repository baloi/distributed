#include <assert.h>
//#include <libc.h>  // unistd.h strring.h and pthread.h
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>

#define NODE0 "node0"
#define NODE1 "node1"

int node0(const char *url)
{
    int sock = nn_socket(AF_SP, NN_PULL);
    assert(sock >= 0);
    assert(nn_bind(sock, url) >= 0);
    while(1)
    {
        char *buf = NULL;
        int bytes = nn_recv(sock, &buf, NN_MSG, 0); 
        assert(bytes >= 0);
        printf("NODE0: RECEIVED \"%s\"\n", buf);
        nn_freemsg(buf);
    }
}

int main(const int argc, const char **argv)
{
    

    return 0;
}
