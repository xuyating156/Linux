#include <stdio.h>
#include <memory.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h> 

#include "common.h"
#include "client.h"



void* pthread_recv(void * a)
{
	int recv_value = 0 ;
	CLIENT_T *client = (CLIENT_T *)a;
	while(1)
	{
		memset(client->recv_buf,0,sizeof(client->recv_buf));
		recv_value = recv(client->socket_fd,client->recv_buf,20,0);
		//printf("recv_value:%d \r\n",recv_value);
		if(-1 == recv_value)
		{
			//printf("recv failed \r\n");
			return 0;
		} 
		else
		{
			printf("come from %d:%s\r\n",client->socket_fd,client->recv_buf);
			
		}		
	}
	
	return NULL;
}


int main(int argc ,char **argv)
{
	CLIENT_T client;
	memset(&client,0,sizeof(CLIENT_T));

	common_socket_init(&client.sock_info);
	client.socket_fd = common_socket(client.sock_info);
	if(-1 == client.socket_fd) return 0;
	if(-1 == client_connect(client)) return 0;
	
	if(-1 == pthread_create(&client.recv_id,NULL,pthread_recv,&client))
	{
		printf("recv pthread_create failed.\r\n");
		return 0;
	}
	
	while(1)
	{
		memset(client.send_buf,0,sizeof(client.send_buf));
		scanf("%s",client.send_buf);
		printf("send_buf\r\n:%s",client.send_buf);

		if(-1 == send(client.socket_fd,client.send_buf,strlen(client.send_buf),0))
		{
			printf("send failed \r\n");
			return 0;
		} 
		//else
			printf("send content:%s\r\n",client.send_buf);

	}
}






