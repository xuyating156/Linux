#define CLIENT_CONNECT_NUM 20



typedef struct
{
	struct sockaddr_in client_socket_info ;
	I16_T client_sockelen;
	I16_T client_fd ;
	U8_T recv_buf[512];
}CLIENT_CON_T;

//server:fd sock_info send_buf recv_buf
typedef struct
{
	U16_T socket_fd;
	SOCKET_INFO_T sock_info;
	pthread_t recv_id[CLIENT_CONNECT_NUM];
	pthread_t send_id;
	U8_T send_buf[512];
	CLIENT_CON_T client[CLIENT_CONNECT_NUM];
}SERVER_T;


U8_T server_bind(SERVER_T server);
U8_T server_listen(U16_T socket_fd);
U8_T server_accept(SERVER_T *server,U16_T i);

