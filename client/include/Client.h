#ifndef CLIENT_H_
#define CLIENT_H_


#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <map>
#include <memory>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/data/Container.h"
#include <opendavinci/odcore/base/Thread.h>

namespace automotive {
    namespace miniature {

        using namespace std;



        class Client : public odcore::base::module::TimeTriggeredConferenceClientModule{
            private:

            	Client(const Client &/*obj*/);

            	Client& operator=(const Client &/*obj*/);

            public:

            	Client(const int32_t &argc, char **argv);

                virtual ~Client();


                odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

            private:
                virtual void setUp();

                virtual void tearDown();
            private:
                int m_clientUDP,m_clientTCP;
                struct sockaddr_in m_server_addr;
        };

    }
} // automotive::miniature

#endif /*CLIENT_H_*/