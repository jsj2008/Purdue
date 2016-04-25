
const char * usage =
"                                                               \n"
"IRCServer:                                                   \n"
"                                                               \n"
"Simple server program used to communicate multiple users       \n"
"                                                               \n"
"To use it in one window type:                                  \n"
"                                                               \n"
"   IRCServer <port>                                          \n"
"                                                               \n"
"Where 1024 < port < 65536.                                     \n"
"                                                               \n"
"In another window type:                                        \n"
"                                                               \n"
"   telnet <host> <port>                                        \n"
"                                                               \n"
"where <host> is the name of the machine where talk-server      \n"
"is running. <port> is the port number you used when you run    \n"
"daytime-server.                                                \n"
"                                                               \n";

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "IRCServer.h"

int QueueLength = 5;

FILE * file;
int nWords = 0;
int maxWords = 100;
int nRooms = 0;
int maxRooms = 100;
char * names[100];
char * rnames[100];

struct message{
	//int num;
	char * from;
	char * msg;
};
	

struct room{
	char * rname;
	char *names[100];
	int nNames;
	int maxNames;
	message * msgs;
	int Nm;
	int Mm;
	//LinkedList positions;
};

room * rooms;

int
IRCServer::open_server_socket(int port) {

	// Set the IP address and port for this server
	struct sockaddr_in serverIPAddress; 
	memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
	serverIPAddress.sin_family = AF_INET;
	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
	serverIPAddress.sin_port = htons((u_short) port);
  
	// Allocate a socket
	int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
	if ( masterSocket < 0) {
		perror("socket");
		exit( -1 );
	}

	// Set socket options to reuse port. Otherwise we will
	// have to wait about 2 minutes before reusing the sae port number
	int optval = 1; 
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, 
			     (char *) &optval, sizeof( int ) );
	
	// Bind the socket to the IP address and port
	int error = bind( masterSocket,
			  (struct sockaddr *)&serverIPAddress,
			  sizeof(serverIPAddress) );
	if ( error ) {
		perror("bind");
		exit( -1 );
	}
	
	// Put socket in listening mode and set the 
	// size of the queue of unprocessed connections
	error = listen( masterSocket, QueueLength);
	if ( error ) {
		perror("listen");
		exit( -1 );
	}

	return masterSocket;
}

void
IRCServer::runServer(int port)
{
	int masterSocket = open_server_socket(port);

	initialize();
	
	while ( 1 ) {
		
		// Accept incoming connections
		struct sockaddr_in clientIPAddress;
		int alen = sizeof( clientIPAddress );
		int slaveSocket = accept( masterSocket,
					  (struct sockaddr *)&clientIPAddress,
					  (socklen_t*)&alen);
		
		if ( slaveSocket < 0 ) {
			perror( "accept" );
			exit( -1 );
		}
		
		// Process request.
		processRequest( slaveSocket );		
	}
}

int
main( int argc, char ** argv )
{
	// Print usage if not enough arguments
	if ( argc < 2 ) {
		fprintf( stderr, "%s", usage );
		exit( -1 );
	}
	
	// Get the port from the arguments
	int port = atoi( argv[1] );

	IRCServer ircServer;

	// It will never return
	ircServer.runServer(port);
	
}

//
// Commands:
//   Commands are started y the client.
//
//   Request: ADD-USER <USER> <PASSWD>\r\n
//   Answer: OK\r\n or DENIED\r\n
//
//   REQUEST: GET-ALL-USERS <USER> <PASSWD>\r\n
//   Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//
//   REQUEST: CREATE-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LIST-ROOMS <USER> <PASSWD>\r\n
//   Answer: room1\r\n
//           room2\r\n
//           ...
//           \r\n
//
//   Request: ENTER-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LEAVE-ROOM <USER> <PASSWD>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: SEND-MESSAGE <USER> <PASSWD> <MESSAGE> <ROOM>\n
//   Answer: OK\n or DENIED\n
//
//   Request: GET-MESSAGES <USER> <PASSWD> <LAST-MESSAGE-NUM> <ROOM>\r\n
//   Answer: MSGNUM1 USER1 MESSAGE1\r\n
//           MSGNUM2 USER2 MESSAGE2\r\n
//           MSGNUM3 USER2 MESSAGE2\r\n
//           ...\r\n
//           \r\n
//
//    REQUEST: GET-USERS-IN-ROOM <USER> <PASSWD> <ROOM>\r\n
//    Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//



int wordLength;
int wordCount;
int charCount=0;
int wordPos;

#define isaletter(c) ((c>='A'&&c<='Z')||(c>='a'&&c<='z'))

char * nextword(FILE * fd) {
	int c,i=0;
	char word[200]="";
	while((c=fgetc(fd))!=EOF) {
	  charCount++;
	  if (!isaletter(c)) {
	   //printf("Entered while loop %s\n",word);
	    if(i>0) return strdup(word);
	  }
	  else if (c==EOF) return NULL;
	  else word[i++]=c;
	}
	if(i>0)return strdup(word);
	return NULL;
}




void
IRCServer::processRequest( int fd )
{
	// Buffer used to store the comand received from the client
	const int MaxCommandLine = 1024;
	char commandLine[ MaxCommandLine + 1 ];
	int commandLineLength = 0;
	int n;
	
	// Currently character read
	unsigned char prevChar = 0;
	unsigned char newChar = 0;
	
	//
	// The client should send COMMAND-LINE\n
	// Read the name of the client character by character until a
	// \n is found.
	//

	// Read character by character until a \n is found or the command string is full.
	while ( commandLineLength < MaxCommandLine &&
		read( fd, &newChar, 1) > 0 ) {

		if (newChar == '\n' && prevChar == '\r') {
			break;
		}
		
		commandLine[ commandLineLength ] = newChar;
		commandLineLength++;

		prevChar = newChar;
	}
	
	// Add null character at the end of the string
	// Eliminate last \r
	commandLineLength--;
        commandLine[ commandLineLength ] = 0;

	printf("RECEIVED: %s\n", commandLine);

	printf("The commandLine has the following format:\n");
	printf("COMMAND <user> <password> <arguments>. See below.\n");
	printf("You need to separate the commandLine into those components\n");
	printf("For now, command, user, and password are hardwired.\n");

	const char * command = "ADD-USER";
	const char * user = "peter";
	const char * password = "spider";
	const char * args = "";
//	char * args2 = (char*)malloc(100);

	char * token = strtok(commandLine," ");
	int i = 0;
	while(token != NULL ) 
	{
	  //printf("Yolooooooo \n");
	  if(i==0) command = token;
	  if(i==1) user = token;
	  if(i==2) {
		password = token;
		break;
	  }
		
	 // if(i==3) args = token;
		
	 // if(i==4) args2 = token;
	  i++; 
	  token = strtok(NULL, " ");
	}
	args = strtok(NULL, "");
	//const char * args = "";
	//if(args2!=NULL)args = strdup(strcat(args,args2));

	printf("command=%s\n", command);
	printf("user=%s\n", user);
	printf( "password=%s\n", password );
	printf("args=%s\n", args);

	if (!strcmp(command, "ADD-USER")) {
		addUser(fd, user, password, args);
	}
	else if (!strcmp(command, "CREATE-ROOM")) {
		createRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "LIST-ROOMS")) {
		listRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "ENTER-ROOM")) {
		enterRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "LEAVE-ROOM")) {
		leaveRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "SEND-MESSAGE")) {
		sendMessage(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-MESSAGES")) {
		getMessages(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-USERS-IN-ROOM")) {
		getUsersInRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-ALL-USERS")) {
		getAllUsers(fd, user, password, args);
	}
	else {
		const char * msg =  "UNKNOWN COMMAND\r\n";
		write(fd, msg, strlen(msg));
	}

	// Send OK answer
	//const char * msg =  "OK\n";
	//write(fd, msg, strlen(msg));

	close(fd);	
}

void
IRCServer::initialize()
{
	// Open password file
	//file = fopen("password.txt","a+");                           
	// Initialize users in room
	for (int i = 0; i < maxWords; i++) 
		names[i] = (char *)malloc(100);
	//while(i < nWords) {
	//	p = c		
	//	p++;	
	//}
	rooms = (room *) malloc(maxWords * sizeof(room));
	for (int i = 0; i < maxRooms; i++) {
		rooms[i].names[i] = (char *)malloc(100);
		rooms[i].rname = (char *)malloc(100);
		rooms[i].nNames = 0;
		rooms[i].maxNames = 100;
		rooms[i].Nm = 0;
		rooms[i].Mm = 100;
		rooms[i].msgs = (message *)malloc(rooms->Mm * sizeof(message));
		for (int j = 0; j < rooms->Mm; j++) {
			rooms[i].msgs[j].from = (char *)malloc(100);
			rooms[i].msgs[j].msg = (char *)malloc(100);
			//rooms->msgs->num = (int)malloc(4);
		}
	}
	// Initalize message list

}

bool
IRCServer::checkPassword(int fd, const char * user, const char * password) {
	// Here check the password
	file = fopen("password.txt","a+");
	char *w = (char *)malloc(100);
	
	while((w=nextword(file))!=NULL) {
		if(!(strcmp(w,user))) {
			if ( ( (w = nextword(file))!=NULL) && !(strcmp(w,password))) return true;
			else {
				const char * msg = "ERROR (Wrong password)\r\n";
				write(fd, msg, strlen(msg));
				fclose(file);	
				return false;
			}
		}
		else {
			if((w=nextword(file))==NULL)break;
		}
	}
	fclose(file);
	const char * msg = "ERROR (Wrong password)\r\n";
	write(fd, msg, strlen(msg));
	//fclose(file);	
	//return false;
	return false;
}

void
IRCServer::addUser(int fd, const char * user, const char * password, const char * args)
{
	// Here add a new user. For now always return OK.
	file = fopen("password.txt","a+");
	args = NULL;
	int flag = 0;
	char *w;
	while((w=nextword(file))!=NULL) {
	  if(!(strcmp(w,user))) flag = 1;
	  if((w=nextword(file))==NULL)break;
	}
	const char * msg;
	if (flag == 0) { msg =  "OK\r\n"; fprintf(file,"%s\n%s\n\n",user,password); }
	else  msg = "ERROR (Username already exists)\r\n"; 
	//const char * msg =  "OK\r\n";
	//fprintf(file,"%s\n%s\n\n",user,password); 
	write(fd, msg, strlen(msg));
	fclose(file);
	return;		
}

void
IRCServer::createRoom(int fd, const char * user, const char * password, const char * args)
{
	if(checkPassword(fd,user,password) == false) { 
		//const char * msg = "ERROR (Username and Password don't match)\r\n"; 
		//write(fd, msg, strlen(msg));
		return;
	}

	for (int i = 0; i < nRooms; i++) {
		if ( strcmp(rooms[i].rname, strdup(args))== 0 ) {
			const char * msg = "ERROR (Room already exists)\r\n"; 
			write(fd, msg, strlen(msg));
			return;
		}
	}

	if (nRooms == maxRooms) {
        maxRooms = (maxRooms)*2;
        rooms = (room *)realloc(rooms,maxRooms * sizeof(room));
    }
	// Expand the wordArray here.

	// Add new word and position
	rooms[nRooms].rname = strdup(args);
	nRooms++;
	
	const char * msg = "OK\r\n";
	write(fd, msg, strlen(msg));
	//fclose(file);
	return;	
}

void
IRCServer::listRoom(int fd, const char * user, const char * password, const char * args)
{
	if(checkPassword(fd,user,password) == false) { 
		//const char * msg = "ERROR (Username and Password don't match)\r\n"; 
		//write(fd, msg, strlen(msg));
		return;
	}
	if (nRooms == 0){
		const char * msg = "No rooms.\r\n"; 
		write(fd, msg, strlen(msg));
		return;
	}
	int nr = 0;
	int i;
	int j;
	char * tmp = (char *)malloc(100);
	for(i=0; i< nRooms; i++) {
		rnames[nr] = strdup(rooms[i].rname);
		nr ++;
	}
	for(i=0; i< nRooms; i++) {
        for(j=0; j< nRooms-1; j++)
        {
            if(strcmp(rnames[j],rnames[j+1])>0)
            {
                tmp = rnames[j+1];
				rnames[j+1]=rnames[j];
				rnames[j] = tmp;
            }   
        }
	}
	
	for (i = 0;i <nRooms; i++) {
		//printf("%s\r\n",names[i]);
		const char * msg = rnames[i];
		//printf("msg = %s\n",msg);
		write(fd, msg, strlen(msg));
		write(fd, "\r\n", 2);
	}
	//const char * msg = "OK\r\n";
	//write(fd, "\r\n", 2);
	return;
}

void
IRCServer::enterRoom(int fd, const char * user, const char * password, const char * args)
{
	if(checkPassword(fd,user,password) == false) { 
		//const char * msg = "ERROR (Username and Password don't match)\r\n"; 
		//write(fd, msg, strlen(msg));
		return;
	}
	int flag = 1;
	int i;
	for (i = 0; i < nRooms; i++) {
		if (strcmp(rooms[i].rname, strdup(args))== 0) { flag = 0; break; }
	}
	if(flag == 1) {
		const char * msg = "ERROR (No room)\r\n"; 
		write(fd, msg, strlen(msg));
		return;
	}
	
	for (int j = 0; j < rooms[i].nNames; j++) {
		if(!(strcmp(rooms[i].names[j],user))) {
			const char * msg = "OK\r\n";
			write(fd, msg, strlen(msg));
			return;
		}
	}
	rooms[i].names[rooms[i].nNames] = strdup(user);
	rooms[i].nNames++;
	//printf("rooms[i].nNames %d \n",rooms[i].nNames);
	const char * msg = "OK\r\n";
	write(fd, msg, strlen(msg));
	return;
}

void
IRCServer::leaveRoom(int fd, const char * user, const char * password, const char * args)
{
	if(checkPassword(fd,user,password) == false) { 
		//const char * msg = "DENIED\r\n"; 
		//write(fd, msg, strlen(msg));
		return;
	}
	int flag = 1;
	int i;
	for (i = 0; i < nRooms; i++) {
		if (strcmp(rooms[i].rname, strdup(args))== 0) { flag = 0; break; }
	}
	if(flag == 1) {
		const char * msg = "ERROR (No room)\r\n"; 
		write(fd, msg, strlen(msg));
		return;
	}
	
	for (int j = 0; j < rooms[i].nNames; j++) {
		if(!(strcmp(rooms[i].names[j],user))) {
			for (int k = j;k < (rooms[i].nNames) -1;k++) rooms[i].names[k] = rooms[i].names[k+1];
			rooms[i].nNames--;
			const char * msg = "OK\r\n";
			write(fd, msg, strlen(msg));
			return;
		}
	}
	//rooms[i].names[rooms[i].nNames] = strdup(user);
	//rooms[i].nNames++;
	const char * msg = "ERROR (No user in room)\r\n";
	write(fd, msg, strlen(msg));
	return;
}

void
IRCServer::sendMessage(int fd, const char * user, const char * password, const char * args)
{
	if(checkPassword(fd,user,password) == false) { 
		//const char * msg = "DENIED\r\n"; 
		//write(fd, msg, strlen(msg));
		return;
	}
	//printf("Args: %s \n",args);
	int flag = 1;
	int i;
	char * room = strtok(strdup(args)," ");
	char * mess;
	if((mess = strtok(NULL,""))==NULL) {
		const char * msg = "ERROR (user not in room)\r\n"; 
		write(fd, msg, strlen(msg));
		return;
	}
	for (i = 0; i < nRooms; i++) {
		if (strcmp(rooms[i].rname, strdup(room))== 0) { flag = 0; break; }
	}
	printf("nRooms: %d\n",nRooms);
	if(flag == 1) {
		const char * msg = "ERROR (No room)\r\n"; 
		write(fd, msg, strlen(msg));
		return;
	}
	printf("i = %d\n",i);
	printf("rooms[i].Nm= %d\n",rooms[i].Nm);
	printf("rooms[i].nNames: %d\n",rooms[i].nNames);
	printf("rooms[i].Nm= %d\n",rooms[i].Nm);
	printf("Mess: %s\n",mess);
	printf("User: %s\n",user);
	for (int j = 0; j < rooms[i].nNames; j++) {
		if(!(strcmp(rooms[i].names[j],user))) {
			//for (int k = j;k < (rooms[i].nNames) -1;k++) rooms[i].names[k] = rooms[i].names[k+1];
			//rooms[i].nNames--;
			printf("rooms[i].Nm= %d\n",rooms[i].Nm);
			//rooms[i].msgs[rooms[i].Nm] = (message)malloc(100 * sizeof(message));
			rooms[i].msgs[rooms[i].Nm].msg = (char *)malloc(100);
			rooms[i].msgs[rooms[i].Nm].msg = strdup(mess);
			rooms[i].msgs[rooms[i].Nm].from = (char *)malloc(100);
			rooms[i].msgs[rooms[i].Nm].from = strdup(user);
			rooms[i].Nm++;
			printf("Room name: %s\n",room);
			printf("Room number: %d\n",i);
			const char * msg = "OK\r\n";
			write(fd, msg, strlen(msg));
			return;
		}
	}
	//rooms[i].names[rooms[i].nNames] = strdup(user);
	//rooms[i].nNames++;
	const char * msg = "ERROR (user not in room)\r\n";
	write(fd, msg, strlen(msg));
	return;
	
}

void
IRCServer::getMessages(int fd, const char * user, const char * password, const char * args)
{
	if(checkPassword(fd,user,password) == false) { 
		//const char * msg = "DENIED\r\n"; 
		//write(fd, msg, strlen(msg));
		return;
	}
	int flag = 1;
	int i = 0;
	int result = 0;
	char * hi = strtok(strdup(args)," ");
	for(int l=0; l< strlen(hi); l++) result = result * 10 + ( (int)hi[l] - '0' );
	char * mess;
	if((mess = strtok(NULL," "))==NULL) {
		const char * msg = "ERROR (User not in room)\r\n"; 
		write(fd, msg, strlen(msg));
		return;
	}
	for (i = 0; i < nRooms; i++) {
		if (strcmp(rooms[i].rname, strdup(mess))== 0) { flag = 0; break; }
	}
	if(flag == 1) {
		const char * msg = "ERROR (No room)\r\n"; 
		write(fd, msg, strlen(msg));
		return;
	}
	printf("Room name: %s\n",mess);
	printf("Room number: %d\n",i);
	//for (i = 0; i < nRooms; i++) {
	//	if (strcmp(rooms[i].rname, strdup(lm))== 0) { flag = 0; break; }
	//}
	//if(flag == 1) {
	//	const char * msg = "ERROR (No such room)\r\n"; 
	//	write(fd, msg, strlen(msg));
	//	return;
	//}
	//write(fd, "Eehita rox 3\r\n", 16);
	for (int j = 0; j < rooms[i].nNames; j++) {
		if(!(strcmp(rooms[i].names[j],user))) {
			//for (int k = j;k < (rooms[i].nNames) -1;k++) rooms[i].names[k] = rooms[i].names[k+1];
			//rooms[i].nNames--;
			if(result >= rooms[i].Nm) {
				const char * msg = "NO-NEW-MESSAGES\r\n"; 
				write(fd, msg, strlen(msg));
				return;
			}
			//write(fd, "Eehita rox 3\r\n", 14);
			//printf("Eehita rox 3\n");
			//printf("Result: %d\n",result);
			//printf("rooms[i].Nm = %d\n",rooms[i].Nm);
			for (int k = result; k < rooms[i].Nm; k++ ) {
				//printf("k: %d\n",k);
				//printf("Eehita rox 4\n");
				char * msg1 = (char *)malloc(100);
				sprintf(msg1,"%d",k);
				//printf("Eehita rox 5\n");
				msg1 = strcat(msg1," ");
				//printf("Eehita rox 6\n");
				//printf("HI: %s\n",rooms[i].msgs[0].from);
				//printf("Eehita rox 7\n");
				//printf("HI: %s\n",rooms[i].msgs[k].msg);
				//printf("HI: %s\n",rooms[i].msgs[0].msg);
				char * msg2 = strdup(rooms[i].msgs[k].from);
				msg2 = strcat(msg2," ");
				//printf("Eehita rox 8\n");
				//printf("%s\n",msg2);
				char * msg3 = strdup(rooms[i].msgs[k].msg);
				//printf("Eehita rox 9\n");
				//msg3 = strcat(msg1,space);
				char * msg12 = strcat(msg1,msg2);
				//printf("Eehita rox 10\n");
				const char * msg = strcat(msg12,msg3);
				//printf("Eehita rox 11\n");
				write(fd, msg, strlen(msg));
				write(fd, "\r\n", 2);
			}
			write(fd, "\r\n", 2);
			return;
			//rooms[i].msgs[rooms[i].Nm].msg = strdup(mess);
			//rooms[i].msgs[rooms[i].Nm].from = strdup(user);
			//rooms[i].Nm++;
			//const char * msg = "OK\r\n";
			//write(fd, msg, strlen(msg));
		}
	}
	//rooms[i].names[rooms[i].nNames] = strdup(user);
	//rooms[i].nNames++;
	const char * msg = "ERROR (User not in room)\r\n";
	write(fd, msg, strlen(msg));
	return;
	
}

void
IRCServer::getUsersInRoom(int fd, const char * user, const char * password, const char * args)
{
	if(checkPassword(fd,user,password) == false) { 
		//const char * msg = "DENIED\r\n"; 
		//write(fd, msg, strlen(msg));
		return;
	}
	int flag = 1;
	int i;
	int j;
	int k;
	for (i = 0; i < nRooms; i++) {
		if (strcmp(rooms[i].rname, strdup(args))== 0) { flag = 0; break; }
	}
	if(flag == 1) {
		const char * msg = "ERROR (No room)\r\n"; 
		write(fd, msg, strlen(msg));
		return;
	}
	char * tmp = (char *)malloc(100);
	//printf("rooms[i].nNames %d\n",rooms[i].nNames);
	for(k=0; k< rooms[i].nNames; k++) {
        for(j=0; j< rooms[i].nNames-1; j++)
        {
            if(strcmp(rooms[i].names[j],rooms[i].names[j+1])>0)
            {
                tmp = rooms[i].names[j+1];
				rooms[i].names[j+1]=rooms[i].names[j];
				rooms[i].names[j] = tmp;
            }   
        }
	}	
	
	for (j = 0; j < rooms[i].nNames; j++) {
			const char * msg = rooms[i].names[j];
			write(fd, msg, strlen(msg));
			write(fd, "\r\n", 2);
			//return;
	}
	//rooms[i].names[rooms[i].nNames] = strdup(user);
	//rooms[i].nNames++;	
	write(fd, "\r\n", 2);
	return;	
}

void
IRCServer::getAllUsers(int fd, const char * user, const char * password,const  char * args)
{
	if(checkPassword(fd,user,password) == false) { 
		//const char * msg = "DENIED\r\n"; 
		//write(fd, msg, strlen(msg));
		return;
	}
	file = fopen("password.txt","a+");
	//printf("Welcome to get all users \n");
	char *w = (char *)malloc(100);
	nWords = 0;
	//printf("Welcome to get all users \n");
	//for (int i = 0; i <= maxWords; i++) {
	 //names[i] = (char *)malloc(100);
	//}

	//printf("Welcome to get all users \n");

	while((w=nextword(file))!=NULL) {
	  //names[nWords] = (char *)malloc(100);
	//printf("Welcome to get all users %s\n",w);
	  names[nWords] = strdup(w);
	  //printf("%s\n",w);
	  nWords++;
	//printf("Welcome to get all users \n");
	  // Make sure that the array has space.
      if (nWords == maxWords) {
        maxWords = (maxWords)*2;
        //names = (char *)realloc(names,maxWords * sizeof(names[nWords -1]));
		for (int i = 0; i < maxWords; i++) 
			names[i] = (char *)realloc(names,100);
      }
	  if((w=nextword(file))==NULL)break;
	}
	int i;
	int j;
	char * tmp = (char *)malloc(100);
	for(i=0; i< nWords; i++) {
        for(j=0; j< nWords-1; j++)
        {
            if(strcmp(names[j],names[j+1])>0)
            {
                tmp = names[j+1];
				names[j+1]=names[j];
				names[j] = tmp;
            }   
        }
	}
	
	for (i = 0;i <nWords; i++) {
		//printf("%s\r\n",names[i]);
		const char * msg = names[i];
		//printf("msg = %s\n",msg);
		write(fd, msg, strlen(msg));
		write(fd, "\r\n", 2);
	}
	//const char * msg = "OK\r\n";
	write(fd, "\r\n", 2);
	fclose(file);
	return;	
}

