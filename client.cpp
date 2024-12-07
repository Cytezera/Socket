#include <cstring> 
#include <iostream> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std; 

void runGame(int clientSocket){
	char buffer[1024] = {0};
	memset(buffer,0,sizeof(buffer)); 
	int byte = recv(clientSocket,buffer,sizeof(buffer),0); 		
	if (byte > 0) {
		cout << buffer << endl ;
	}else {
		cerr << "Error bro" << endl ;
	}
}
void connectServer(){
	int clientSocket; 
	struct sockaddr_in serverAddr; 
	socklen_t addr_size; 

	char buffer[1024] = {0}; 

	clientSocket = socket(AF_INET, SOCK_STREAM, 0 ) ; 
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_port = htons(8080); 
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	connect(clientSocket, (struct sockaddr*)&serverAddr , sizeof(serverAddr)); 
	cout << "Connected to server" << endl ; 

	while(true){
		memset(buffer,0,sizeof(buffer));
		int bytes= recv(clientSocket,buffer,sizeof(buffer),0 ) ;
		if (bytes <= 0) 
		{
			cerr << "Error on recieving server connection " << endl;
			break; 
		}
		cout << buffer << endl; 
			
		if((string(buffer) == "Hello Player 1") || (string(buffer) == "Hello Player 2")){
			break; 
		}
	}
	runGame(clientSocket);		
	close(clientSocket);
	cout << "Socket closed" << endl;
}
int main() {
	connectServer();
	return 0; 
}
	
