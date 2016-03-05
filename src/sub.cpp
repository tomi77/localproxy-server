#include <iostream>     // std::cout, std::cerr, std::endl
#include <cstring>      // std::string
#include <cstdlib>      // std::getenv
#include <zmq.hpp>      // zmq::

using namespace std;

void proxy(const char* uri) {
    zmq::context_t ctx(1);

    zmq::socket_t socket(ctx, ZMQ_SUB);

    try {
        socket.connect(uri);
        socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    } catch (zmq::error_t error) {
        cerr << error.num() << endl;
    }

    zmq::pollitem_t poller = { static_cast<void *>(socket), 0, ZMQ_POLLIN, 0 };

    cout << "Start" << endl;
    cout << "In: " << uri << endl;
    unsigned int i = 0;

    while (1) {
        try {
            zmq::poll(&poller, 1, 1000);
        } catch (zmq::error_t error) {
            cerr << error.num();
        }
        if (poller.revents & ZMQ_POLLIN) {
            /* Create an empty ØMQ message */
            zmq::message_t msg;

            /* Create an empty ØMQ message */
            socket.recv(&msg);

            size_t l = msg.size();
            void* tmp = msg.data();
            string s_msg = string((char*)tmp, l);

            cout << "Incomming message: " << s_msg << " id: " << ++i << endl;
        }
    }
}

int main() {
    const char* outgoing_uri = getenv("ZMQ_LOCAL_OUTGOING_BROADCAST_URI");

    proxy(outgoing_uri);
}
