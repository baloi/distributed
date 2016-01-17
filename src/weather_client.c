// Weather update client
// Connects SUB socket to tcp://localhost:5556
// Collects weather updates and finds av temperature in zipcode

#include "zhelpers.h"

int main(int argc, char **argv)
{
    // Socket to talk to server
    printf("Collecting updates from weather server...\n");
    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    int rc = zmq_connect(subscriber, "tcp://localhost:5556");

    assert(rc == 0);

    // Suscribe to zip code, default is 12184
    char *filter = (argc > 1)? argv[1]: "12184 ";
    rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, filter, strlen(filter));
    
    assert(rc == 0);
    
    // process 100 updates
    int update_nbr;
    long total_temp = 0;
    for(update_nbr = 0; update_nbr < 100; update_nbr++)
    {
        char *string = s_recv(subscriber);
        
        int zipcode, temperature, relhumidity;
        sscanf(string, "%d %d %d", &zipcode, &temperature, &relhumidity);
        printf("%d >> temp = %d , relhumbidity= %d\n", update_nbr, temperature,
                    relhumidity);
        total_temp += temperature;
        free(string);
    }
    
    printf("Average temperature for zipcode '%s' was %dF\n", 
        filter, (int) (total_temp / update_nbr));
    zmq_close(subscriber);
    zmq_ctx_destroy(context);

    return 0;
}