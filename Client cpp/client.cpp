#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
using namespace std;
int main() {
	int client, server;
	int portNum = 8879;
	bool isExit = false;
	int buffSize = 512;
	char buffer[buffSize];
	char* ip = "127.0.0.1";
	struct sockaddr_in server_addr;

	client = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

	if (client<0){
		cout << "socket coudlnt create..." << endl;
		exit(1);
	}
	cout <<" Socket created! " << endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port =htons(portNum);


	if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
		cout << "Connecting... " << endl;

	//recv(client, buffer, buffSize, 0);
	//cout << "=> Connection confirmed, you are good to go...";
	socklen_t m = sizeof(server_addr);
	do {
        cout << "Client: ";
        do {
            cin >> buffer;
            sendto(client, buffer, buffSize, 0, (struct sockaddr *)&server_addr, m);
            cout <<"Sent"<< endl;
        }while (*buffer != 42);
    }while (!isExit);

}