#include <cstring> 
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std; 
void playGame(int client1, int client2){
	bool continues = false ;
	string rematch = "Rematch mou? " ; 
	send(client1,rematch.c_str(),rematch.size(), 0) ; 
	send(client2,rematch.c_str(),rematch.size(),0); 	
	cout << rematch << endl;
}
void connectClient(){
	int serverSocket, client1, client2; 
	struct sockaddr_in serverAddr, clientAddr ;
	socklen_t addr_size;

	serverSocket = socket(AF_INET, SOCK_STREAM, 0 ) ; 
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080); 
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)  ) ; 
	listen(serverSocket, 2);
	cout <<  "Waiting for players to join ... " << endl; 
	addr_size = sizeof(clientAddr); 
	client1 = accept(serverSocket , (struct sockaddr*)&clientAddr, &addr_size) ;
	if (client1 < 0) {
		cerr << "Error accepting player 1 " << endl ;
		close(serverSocket);
		return; 
	}
	cout << "Player 1 has joined" << endl; 
	string waitingMsg = "Waiting for player 2 to join\n" ; 
	send(client1,waitingMsg.c_str(),waitingMsg.size(),0); 
	client2 = accept(serverSocket ,(struct sockaddr*)&clientAddr,&addr_size); 
	if (client2 < 0 ) {
		cerr << "Error accepting player 2" << endl; 
		close(serverSocket);
		return ;
	}
	cout << "Player 2 has joined" << endl; 
	string one = "Hello Player 1"; 
	string two = "Hello Player 2"; 
	send(client1,one.c_str()  ,one.size(),0); 
	send(client2, two.c_str()   ,two.size(),0);
	playGame(client1,client2); 
	close(serverSocket);
	close(client1);
	close(client2);
}
int main () {
	connectClient();
}
