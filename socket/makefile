EXEC_SERVER=server
EXEC_CLIENT=client

socket:	
	gcc -o ./$(EXEC_SERVER) ./main_server.c ./server.c ./common.c -lpthread
	gcc -o ./$(EXEC_CLIENT) ./main_client.c ./client.c ./common.c -lpthread
