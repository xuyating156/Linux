#include <stdio.h>
#include <memory.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>


typedef struct sockaddr_in my_sockaddr_in;
#define FAMILY_IPV4 AF_INET
#define SERVER_PORT 8080//端口号可以指定
#define SERVER_IP "127.0.0.1"//本地回环
//#define INADDR_ANY (in_addr_t)0x00000000

int main(int argc ,char **argv)
{
	int client_fd = 0;//客户端
	my_sockaddr_in server_socket_info  ;//存客户端句柄

	memset(&server_socket_info,0,sizeof(my_sockaddr_in));

	client_fd = socket( FAMILY_IPV4,SOCK_STREAM ,0 );//得到句柄
	if(-1 == server_fd)
	{
		printf("socket failed \r\n");
		return 0;
	}
	printf("client socket id :%d\r\n",client_fd);

	server_socket_info.sin_family = FAMILY_IPV4;
    //对结构体存信息
	server_socket_info.sin_port =  htons(SERVER_PORT);
    //将端口号转换为短整型，主机端口号转为网络的高字节
	//ient_socket_info.sin_addr.s_addr =htonl(INADDR_ANY);
     inet_pton(FAMILY_IPV4,SERVER_IP,&(server_socket_info.sin_addr)) ;
     //要连接服务器的地址,第二个值：要转化的值。、第三个值：//十进制转为二进制，并且调整字节序（htonl）

         /*
	if(-1 == bind(server_fd ,(struct sockaddr*)(&server_socket_info),sizeof(my_sockaddr_in) ))
      //句柄、结构体变量信息（将sockaddr_in强制转换为sockaddr）--本地地址、地址长度。
	{//绑定本地IP地址
		printf("bind failed \r\n");
		return 0;
	}
	printf("bind sucess\r\n");
  */

	if(-1 == connect(client_fd ,(struct sockaddr*)(&server_socket_info),sizeof(my_sockaddr_in))
	{
		printf("connect failed \r\n");
		return 0;
	}
	printf("connect sucess\r\n");

	return 0;
}