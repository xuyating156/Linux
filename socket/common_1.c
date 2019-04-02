#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <unistd.h> 
#include "common.h"


U16_T common_socket(SOCKET_INFO_T sock_info)
{
	U16_T fd = 0,i = 0;

	if(SOCK_RAW == sock_info.socket_type); 
	else i = 0;
	fd = socket(sock_info.my_sockaddr_in.sin_family,sock_info.socket_type,i );// FAMILY_IPV4,SOCK_STREAM
	if(-1 == fd)
		printf("socket failed \r\n");
	else
		printf("socket id :%d\r\n",fd);
	return fd;
}

void common_socket_init(SOCKET_INFO_T *sock_info)
{
	sock_info->socket_type = SOCK_STREAM;
	sock_info->my_sockaddr_in.sin_family = FAMILY_IPV4;
	sock_info->my_sockaddr_in.sin_port =  htons(SERVER_PORT);
	sock_info->my_sockaddr_in.sin_addr.s_addr =htonl(INADDR_ANY);//htonl((unsigned long)SERVER_IP);
}


