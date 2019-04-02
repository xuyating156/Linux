#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <unistd.h> 
#include "common.h"
#include "server.h"


U8_T server_bind(SERVER_T server)
{
	U8_T bind_return = 0;

	bind_return = bind(server.socket_fd,(struct sockaddr*)(&server.sock_info),sizeof(struct sockaddr_in) );
	if(-1 == bind_return) printf("bind failed \r\n");
	else printf("bind sucess\r\n");	
	return bind_return;
}

U8_T server_listen(U16_T socket_fd)
{
	U8_T listen_return = 0;

	listen_return = listen(socket_fd,20);
	if(-1 == listen_return) printf("listen failed \r\n");
	else printf("listening...\r\n");
	return listen_return;
}

U8_T server_accept(SERVER_T *server,U16_T i)
{
	 server->client[i].client_fd = accept(server->socket_fd,(struct sockaddr*)(&server->client[i].client_socket_info),
		&server->client[i].client_sockelen);
	
	if(-1 == server->client[i].client_fd) printf("accept failed \r\n");
	else printf("client %d: fd[%d] connect sucess \r\n",i,server->client[i].client_fd);
	
	return server->client[i].client_fd;
}

