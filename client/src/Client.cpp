#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>


#include "automotivedata/GeneratedHeaders_AutomotiveData.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/wrapper/Mutex.h"
#include "opendavinci/odcore/wrapper/MutexFactory.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStatistics.h"

#include "Client.h"
namespace automotive {
    namespace miniature {

		using namespace std;
		using namespace odcore::base;
		using namespace odcore::data;
		using namespace odcore::wrapper;
		using namespace odcore::data::dmcp;
		//int m_clientUDP,m_clientTCP;
		//struct sockaddr_in m_server_addr;
		//struct hostent *server;
		//char const* ip ="127.0.0.1";
		//int portNum = 8872;
			//socklen_t m;
		const char* p;
		int length;
		string cs;
		Client::Client(const int32_t &argc, char **argv) :
		TimeTriggeredConferenceClientModule(argc, argv,"client"),
		m_clientUDP(),
		m_clientTCP(),
		m_server_addr(),
		m_sentMessage(),
		m_containerHandlerMutex()
		{}

		Client::~Client() {
        }
        void Client::nextContainer(Container &c) {
            if (c.getDataType() == odcore::data::dmcp::ModuleStatistics::ID()) {
            	m_containerHandlerMutex -> lock();
                // ModuleStatistics ms = c.getData<ModuleStatistics>();
                stringstream ss;
                ss << c;
                m_sentMessage = ss.str();
                m_containerHandlerMutex ->unlock();
        		
        	}

        }
        void Client::setUp() {
        	m_containerHandlerMutex = unique_ptr<odcore::wrapper::Mutex>(MutexFactory::createMutex());
   //      	if (m_containerHandlerMutex.get() == NULL ){
   //      		cerr << "Couldnt create MUTEX" <<endl;
			// }
			cout << "Setup started" << endl;
			KeyValueConfiguration kv = getKeyValueConfiguration();
        	
        	string theIp = kv.getValue<string>("client.ip");
        	char const* ip = theIp.c_str();
        	const int portNum = kv.getValue<int>("client.port");
			m_server_addr.sin_family = AF_INET;
			
			m_server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
			inet_pton(AF_INET, ip, &m_server_addr.sin_addr);
			
			m_server_addr.sin_port =htons(portNum);

			//CLIENT TCP
			//-----------------------------------------------------//
			m_clientTCP=socket(AF_INET,SOCK_STREAM,0);
			if(m_clientTCP < 0){
				cout << "TCP socket couldnt create..."<< endl;
				exit(1);
			}
			cout <<"TCP socket created!" << endl;
			

			if (connect(m_clientTCP,(struct sockaddr *)&m_server_addr,sizeof(m_server_addr)) ==0){
				cout << "Connecting TCP.." <<endl;
			}
  			
  			

			// CLIENT UDP
        	//--------------------------------------------------------------------//
        	
        	
        	m_clientUDP = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
        	
        	if (m_clientUDP<0){
				cout << "UDP socket coudlnt create..." << endl;
				exit(1);
			}
			cout <<"UDP socket created! " << endl;



			if (connect(m_clientUDP,(struct sockaddr *)&m_server_addr, sizeof(m_server_addr)) == 0)
				cout << "Connecting UDP.. " << endl;
        }
        
        	//m = sizeof(m_server_addr);
        void Client::tearDown() {
        	close(m_clientUDP);
        	close(m_clientTCP);
        }

        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode Client::body() {
        	//char buffers[256];
        	while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
        		Container ms = getKeyValueDataStore().get(ModuleStatistics::ID());
        		nextContainer(ms);
        		
			
        		cout << "Input something to send" << endl;
        		


				//sprintf (buffers, p);
            //send TCP and UDP
            //--------------------------------------------------------------//
            	//cin >> buffers;
	  			sendto(m_clientUDP, m_sentMessage.c_str(), m_sentMessage.length(), 0, (struct sockaddr *)&m_server_addr, sizeof(m_server_addr));
            	cout <<"Sent UDP"<< endl;
            	sendto(m_clientTCP, m_sentMessage.c_str(), m_sentMessage.length(), 0, (struct sockaddr *)&m_server_addr, sizeof(m_server_addr));
	  			//write(m_clientTCP,buffer,bufferLength);
	  			cout <<"Sent TCP"<< endl;

        	}	
        	return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }
    }
} 