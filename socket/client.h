

//client:fd sock_info send_buf recv_buf
typedef struct
{
	U16_T socket_fd;
	SOCKET_INFO_T sock_info;
	pthread_t recv_id;
	U8_T send_buf[512];
	U8_T recv_buf[512];
}CLIENT_T;


U8_T client_connect(CLIENT_T client);



