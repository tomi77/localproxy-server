#include <iostream>     // std::cout, std::cerr, std::endl
#include <cstring>      // std::string
#include <zmq.hpp>      // zmq::
#include "proxy.h"

using namespace std;

namespace localproxy {
    namespace zmq_ {
	void proxy(const char* in, const char* out) {
	    zmq::context_t ctx(1);

	    zmq::socket_t sock_incoming(ctx, ZMQ_SUB);
	    zmq::socket_t sock_outgoing(ctx, ZMQ_PUB);

	    try {
		sock_incoming.bind(in);
		sock_incoming.setsockopt(ZMQ_SUBSCRIBE, "", 0);

		sock_outgoing.bind(out);
	    } catch (zmq::error_t error) {
		assert(error.num() != 0);
	    }

	    zmq::pollitem_t poller = { static_cast<void *>(sock_incoming), 0, ZMQ_POLLIN, 0 };

	    cout << "In: " << in << endl;
	    cout << "Out: " << out << endl;
	    cout << "Start" << endl;

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
		    sock_incoming.recv(&msg);

		    size_t l = msg.size();
		    void* tmp = msg.data();
		    string s_msg = string((char*)tmp, l);

		    cout << "Incomming message: " << s_msg << endl;

		    /* Send the message to the socket */
		    sock_outgoing.send(msg);
		}
	    }
	}
    }
}