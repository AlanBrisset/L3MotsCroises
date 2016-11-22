

/*  Hello World server */

#include <zmq.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main (void)
{
    /*  Socket to talk to clients */
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);

    while (1) {
        char buffer [100];
        zmq_recv (responder, buffer, 100, 0);
        printf (buffer);
        sleep (1);      
        zmq_send (responder, "Nom correct, Bienvenue !", 20, 0);
    }
    return 0;
}
