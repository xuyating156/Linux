#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include "common.h"
#include "client.h"

U8_T client_connect(CLIENT_T client)
{
	U8_T connect_return = 0;
	connect_return = connect(client.socket_fd,(struct sockaddr*)(&client.sock_info.my_sockaddr_in),sizeof(struct sockaddr) );
	if(-1 == connect_return)
		printf("connect failed \r\n");
	else
		printf("connect sucess\r\n");
	return connect_return;

}


