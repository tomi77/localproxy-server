#include <iostream>     // std::cout, std::cerr, std::endl
#include <thread>       // std::this_thread::sleep_for
#include <chrono>       // std::chrono::seconds
#include <string>       // std::string, std::to_string
#include <cstring>      // std::strcpy
#include <cstdlib>      // std::realloc, std::getenv
#include <zmq.hpp>      // zmq::

using namespace std;

inline void my_free (void *data, void *hint) {
    free(data);
}

void* stoc(const string s, void* out) {
    out = realloc(out, s.length() + 1);
    strcpy((char*)out, s.c_str());

    return out;
}

int main() {
    const char* incoming_uri = getenv("ZMQ_LOCAL_INCOMING_BROADCAST_URI");

    zmq::context_t context(1);

    zmq::socket_t socket(context, ZMQ_PUB);

    try {
        socket.connect(incoming_uri);
    } catch (zmq::error_t error) {
        cerr << error.num() << endl;
    }

    this_thread::sleep_for(chrono::seconds(1));

    for(unsigned int i = 0; i < 100; ++i) {
        void* data = NULL;
        string str = to_string(i + 1);
        data = stoc(str, data);

        /* Create an empty ØMQ message */
        zmq::message_t msg(data, str.length(), my_free);

        /* Send the message to the socket */
        try {
            socket.send(msg);
        } catch (zmq::error_t error) {
            cerr << "send: " << error.num() << endl;
        }
    }

    socket.disconnect(incoming_uri);
}
