#include <stdio.h>
#include <memory.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct sockaddr_in my_sockaddr_in;
#define FAMILY_IPV4 AF_INET
#define SERVER_PORT 8080
#define SERVER_IP "192.168.91.136"
//#define INADDR_ANY (in_addr_t)0x00000000

int main(int argc ,char **argv)
{
	int client_fd = 0;
      char send_buf[255]={"hello"};
     char recv_buf[255]={0};
	my_sockaddr_in server_socket_info ;
	//int client_sockelen = 0;

	memset(&server_socket_info,0,sizeof(my_sockaddr_in));

	client_fd = socket( FAMILY_IPV4,SOCK_STREAM ,0 );
	if(-1 == client_fd)
	{
		printf("socket failed \r\n");
		return 0;
	}
	printf("cilent socket id :%d\r\n",client_fd);

	server_socket_info.sin_family = FAMILY_IPV4;
	server_socket_info.sin_port =  htons(SERVER_PORT);
	//client_socket_info.sin_addr.s_addr =htonl(INADDR_ANY);//htonl((unsigned long)SERVER_IP);  127.0.0.1
	inet_pton(FAMILY_IPV4,SERVER_IP,&(server_socket_info.sin_addr));
/*

	if(-1 == bind(client_fd ,(struct sockaddr*)(&server_socket_info),sizeof(my_sockaddr_in) ))
	{
		printf("bind failed \r\n");
		return 0;
	}
	printf("bind sucess\r\n");
*/
	if(-1 == connect(client_fd ,(struct sockaddr*)(&server_socket_info),sizeof(my_sockaddr_in) ))
	{
		printf("connect failed \r\n");
		return 0;
	}
	printf("connect sucess\r\n");

        if(-1== send(client_fd,send_buf,10,0) )
         {
                printf("send failed \r\n");
		return 0;

         }
        printf("send conyent:%s \r\n",send_buf);

         while(1)
       {

        if(-1== recv(client_fd,recv_buf,10,0) )
         {
                printf("recv failed \r\n");
		return 0;

         }
        else{
            printf("recv_buf:%s\r\n",recv_buf);
           break;
         }


}
	return 0;
}