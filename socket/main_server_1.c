#include <stdio.h>
#include <memory.h>
#include <pthread.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <unistd.h> 
#include "common.h"
#include "server.h"



void* pthread_send(void * a)
{
	U8_T *send_buf = (U8_T *)(a);
	U8_T send_obj[2] = {0};
	while(1)
	{
		memset(send_buf,0,strlen(send_buf));
		printf("send?(Y or N)\r\n");
		scanf("%s",send_buf);
		if(0 == strcmp("Y",send_buf))
		{
			printf("who?\r\n");
			scanf("%s",send_obj);
			printf("what?\r\n");
			memset(send_buf,0,sizeof(send_buf));
			scanf("%s",send_buf);
			if(-1 == send(send_obj[0]-'0',send_buf,strlen(send_buf),0))
			{
				printf("send failed \r\n");
				return 0;
			} 
			//else
				printf("send content:%s\r\n",send_buf);
		}	
	}
	return NULL;
}

void* pthread_recv(void * a)
{
	int recv_value = 0;
	CLIENT_CON_T *client = (CLIENT_CON_T*)(a);

	while(1)
	{
		memset(client->recv_buf,0,sizeof(client->recv_buf));
		recv_value = recv(client->client_fd,client->recv_buf,20,0);
		//printf("recv_value:%d \r\n",recv_value);
		if(-1 == recv_value)
		{
			//printf("recv failed \r\n");
			return 0;
		} 
		else
		{
			printf("come from %d:%s\r\n",client->client_fd,client->recv_buf);
			if(0 == strcmp("quit",client->recv_buf))
			{
				close(client->client_fd);
			}
			//sleep(3);
		}	
		
	}
	
	return NULL;
}

int main(int argc ,char **argv)
{
	int i =0;
	SERVER_T server;
	
	memset(&server,0,sizeof(SERVER_T));

	common_socket_init(&server.sock_info);
	server.socket_fd= common_socket(server.sock_info);
	if(-1 == server.socket_fd) return 0;
	if(-1 == server_bind(server)) return 0;
	if(-1 == server_listen(server.socket_fd)) return 0;

	if(-1 == pthread_create(&server.send_id,NULL,pthread_send,server.send_buf))
	{
		printf("send pthread_create failed.\r\n");
		return 0;
	}
	
	while(1)
	{				
		server_accept(&server,i);
		if(-1 == pthread_create(&server.recv_id[i],NULL,pthread_recv,&(server.client[i])))
		{
			printf("recv pthread_create failed.\r\n");
			return 0;
		}
		i++;
	}
}





