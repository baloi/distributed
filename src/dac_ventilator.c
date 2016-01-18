// Task ventilator
// Binds PUSH socket to tcp://localhost:5557
// Sends batch of tasks to workers via that socket
#include "zhelpers.h"

int main(void)
{
    void *context = zmq_ctx_new();
    
    // Socket to send messages on 
    void *sender = zmq_socket(context, ZMQ_PUSH);
    zmq_bind(sender, "tcp://*:5557");
    
    // Socket to send start of batch message on
    void *sink = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sink, "tcp://localhost:5558");
    
    printf("Press enter when the workers are ready: ");
    getchar();
    printf("Sending tasks to workers...\n");

    // The first message is "0" and signals start of batch
    s_send(sink, "0");

    // Initialize random number generator
    srandom((unsigned) time(NULL));

    int task_nbr;
    int total_msec = 0; // Total expected cost in msecs

    zmq_close(sink);
    zmq_close(sender);
    zmq_ctx_destroy(context);
    return 0;
}