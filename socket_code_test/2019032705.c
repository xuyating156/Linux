#include <stdio.h>
#include <memory.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct sockaddr_in my_sockaddr_in;
#define FAMILY_IPV4 AF_INET
#define SERVER_PORT 8080
#define SERVER_IP "192.168.57.128"
//#define INADDR_ANY (in_addr_t)0x00000000

char recv_buf[255] = {0};//接收字符

void* pthread1(void * a)//线程
{
	int recv_value = 0 ,client_fd = 0;
	client_fd = *((int*)(a));//
	while(1)
	{

	memset(recv_buf,0,sizeof(recv_buf));//初始化
	recv_value = recv(client_fd,recv_buf,20,0);//接收20个字符
	//printf("recv_value:%d \r\n",recv_value);
	if(-1 == recv_value)
	{
		//printf("recv failed \r\n");
		return 0;
	}
	else
	{
		printf("come from %d:%s\r\n",client_fd,recv_buf);
		if(0 == strcmp("quit",recv_buf))//比较接收的字符是否为quit
		{
			close(client_fd);//关闭该客户端
		}
		//sleep(3);
	}

}

return NULL;

}

int main(int argc ,char **argv)
{
	int server_fd = 0, i =0;
	my_sockaddr_in server_socket_info ,client_socket_info ;
    //一个结构体，存储客户端和服务端的句柄
	int client_sockelen = 0;
	int client_fd[10] = {0} ;//可同时连接十个客户端


char send_buf[255] = "hello,too";//发送的字符
pthread_t id = 0;

memset(&server_socket_info,0,sizeof(my_sockaddr_in));//初始化为0
memset(&client_socket_info,0,sizeof(my_sockaddr_in));

server_fd = socket( FAMILY_IPV4,SOCK_STREAM ,0 );//得到句柄
if(-1 == server_fd)
{
	printf("socket failed \r\n");
	return 0;
}
printf("server socket id :%d\r\n",server_fd);//输出服务端id

server_socket_info.sin_family = FAMILY_IPV4;
server_socket_info.sin_port =  htons(SERVER_PORT);
//memcpy( &server_socket_info.sin_addr,htonl(SERVER_IP) , sizoef(unsigned long ));
server_socket_info.sin_addr.s_addr =htonl(INADDR_ANY);//htonl((unsigned long)SERVER_IP);

if(-1 == bind(server_fd ,(struct sockaddr*)(&server_socket_info),sizeof(my_sockaddr_in) ))
{
	printf("bind failed \r\n");
	return 0;
}
printf("bind sucess\r\n");

if(-1 == listen(server_fd,20))
{
	printf("listen failed \r\n");
	return 0;
}
printf("listening...\r\n");

while(1)
{
	client_fd[i] = accept(server_fd ,(struct sockaddr*)(&client_socket_info),&client_sockelen);//连接客户端、地址、地址长度

	if(-1 == client_fd[i])
	{
		printf("accept failed \r\n");
		return 0;
	}

	printf("accept sucess \r\n");
	printf("client %d: fd[%d] connect sucess \r\n",i,client_fd[i]);
	if(-1 == pthread_create(&id,NULL,pthread1,client_fd+i))
	{
		printf("pthread_creat failed.\r\n");
		return 0;
	}
	i++;
}
if(-1 == pthread_join(id,NULL))
{
	printf("pthread_join failed.\r\n");
	return 0;
}

#if 0
	while(0)
	{
		sleep(1);
		if(-1 == recv(client_fd,recv_buf,20,0))
		{
			printf("recv failed \r\n");
			return 0;
		}
		else
		{
			printf("recv content:%s\r\n",recv_buf);
			//if(-1 == send(client_fd,send_buf,20,0))
			{
			//	printf("send failed \r\n");
			//	return 0;
			}
			//else
			//	printf("send content:%s\r\n",send_buf);
		}



}


#endif
	return 0;
}



