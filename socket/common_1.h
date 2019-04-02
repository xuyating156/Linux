#define FAMILY_IPV4 AF_INET
#define SERVER_PORT 8080
#define SERVER_IP "192.168.57.128"

//#define INADDR_ANY (in_addr_t)0x00000000

typedef unsigned char U8_T;
typedef signed char I8_T;
typedef unsigned int U16_T;
typedef signed int I16_T;

typedef struct 
{
	struct sockaddr_in my_sockaddr_in;
	U8_T socket_type;
}SOCKET_INFO_T;


U16_T common_socket(SOCKET_INFO_T sock_info);
void common_socket_init(SOCKET_INFO_T *sock_info);



