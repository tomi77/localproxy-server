#include <cstdlib>      // std::getenv
#include "zmq_proxy.h"

using namespace std;

int main() {
    const char* incoming_uri = getenv("ZMQ_LOCAL_INCOMING_BROADCAST_URI");
    const char* outgoing_uri = getenv("ZMQ_LOCAL_OUTGOING_BROADCAST_URI");

    localproxy::zmq_::proxy(incoming_uri, outgoing_uri);
}
