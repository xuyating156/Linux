#include <stdio.h>
#include <memory.h>
#include <netinet/in.h>
#include <sys/socket.h>

typedef struct sockaddr_in my_sockaddr_in;
#define FAMILY_IPV4 AF_INET
#define SERVER_PORT 8080//端口号可以指定
#define SERVER_IP "127.0.0.1"//本地回环
//#define INADDR_ANY (in_addr_t)0x00000000

int main(int argc ,char **argv)
{
	int server_fd = 0;//存服务端句柄
	my_sockaddr_in server_socket_info ,client_socket_info ;//存服务端句柄
	int client_sockelen = 0;

	memset(&server_socket_info,0,sizeof(my_sockaddr_in));//对结构体初始化为0
	memset(&client_socket_info,0,sizeof(my_sockaddr_in));

	server_fd = socket( FAMILY_IPV4,SOCK_STREAM ,0 );//得到句柄
	if(-1 == server_fd)
	{
		printf("socket failed \r\n");
		return 0;
	}
	printf("server socket id :%d\r\n",server_fd);

	server_socket_info.sin_family = FAMILY_IPV4;//对结构体存信息
	server_socket_info.sin_port =  htons(SERVER_PORT);//将端口号转换为短整型，主机端口号转为网络的高字节
	//memcpy( &server_socket_info.sin_addr,htonl(SERVER_IP) , sizoef(unsigned long ));
	server_socket_info.sin_addr.s_addr =htonl(INADDR_ANY);//htonl((unsigned long)SERVER_IP);
    //任意的，随着当前网络环境变化、主机IP地址转为网络长整形

	if(-1 == bind(server_fd ,(struct sockaddr*)(&server_socket_info),sizeof(my_sockaddr_in) ))//句柄、结构体变量信息（将sockaddr_in强制转换为sockaddr）--本地地址、地址长度。
	{//绑定本地IP地址
		printf("bind failed \r\n");
		return 0;
	}
	printf("bind sucess\r\n");

	if(-1 == listen(server_fd,20))  //监听
	{
		printf("listen failed \r\n");
		return 0;
	}
	printf("listening...\r\n");
	if(-1 == accept(server_fd ,(struct sockaddr*)(&client_socket_info),&client_sockelen))
	{
		printf("accept failed \r\n");
		return 0;
	}
	printf("accept sucess\r\n");

	return 0;
}