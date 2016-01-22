#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <nanomsg/nn.h>
#include <nanomsg/pair.h>

int main(int argc, char **argv)
{
    int sock = nn_socket(AF_SP, NN_PAIR);
    char *url = "ipc:///tmp/pipeline.ipc";
    nn_bind(sock, url);

    char *buf = NULL;
    int result = nn_recv(sock, &buf, NN_MSG, 0);
    printf("-- sent with result >>%s<<\n", buf);

    nn_freemsg(buf);
    nn_send(sock, "kthxbye", 8, 0);
    nn_shutdown(sock, 0);

    return 0;
}
