#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
//vision
//glob
int flag = 1;

int file_size(FILE *fp);

void * p_fread(void *a)
{
	FILE *fp  =(FILE *)a;
	int size = 0 ,size_last = 0,ch = 0;
	printf("a:%p fp:%p\r\n",a,fp);
	while(1)
	{

		//size = file_size(fp);
		//if((size - size_last) > 0)
		if(!flag)
		{

			if(  fseek(fp ,-1, SEEK_CUR) )
			{
				printf("file seek failed.\r\n");
				return 0;
			}
			ch  = fgetc(fp);
			printf("a_read:%c\r\n",ch);
			flag =1;
			//write_count = fwrite(&((char)ch),1,1,fp);
			//if(write_count == 0)
			//{
			//	printf("file write failed.\r\n");
			//	return 0;
			//}
		}
		size_last =  size;
	}

	return 0;
}

int file_size(FILE *fp)
{
	int size = 0,ch = 0;

	if(  fseek(fp ,0 , SEEK_END) )
	{
		printf("file seek failed.\r\n");
		return 0;
	}

	size = ftell(fp);
	while(0)
	{
		ch  = fgetc(fp);
		printf("ch:%c\r\n",ch);
		sleep(1);
		if(EOF != ch)
		{
			size++;
		}
		else break;
	}
	return size;
}

int main(int argc,char** argv)
{
	FILE *fp = NULL;
	FILE *fp1 = NULL;
	char write_buf[10] = "hello";
	char read_buf[10] = {0};
	int write_count = 0,read_count = 0;
	pthread_t id_read = 0;
	int pcr = 0,i = 0;

	fp = fopen("./test.txt","w+");
	fp1 = fopen("./test1.txt","w+");
	if(NULL == fp || NULL == fp1)
	{
		return 0;
	}
	pcr = pthread_create(&id_read ,NULL ,p_fread , fp);
	if(-1 == pcr)
	{
		printf("pthread create failed\r\n");
		return 0;
	}
//judge file inner pointer ; judge file size changing
	while(*(write_buf+i))
	{
		if(flag)
		{
			write_count = fwrite(write_buf+i,1,1,fp);
			if(write_count == 0)
			{
				printf("file write failed.\r\n");
				return 0;
			}

			printf("a_write:%c\r\n",*(write_buf+i));
			i++;
			flag = 0;
		}

	}

	//printf("file size :%d\r\n",file_size(fp));
	#if 0
	if(  fseek(fp ,0 , SEEK_SET) )
	{
		printf("file seek failed.\r\n");
		return 0;
	}
	printf("write_count:%d\r\n",write_count);
	read_count = fread(read_buf ,5,1 ,fp);

	if(read_count <= 0)
	{
		printf("file write failed.\r\n");
		return 0;
	}
	printf("read buf:%s\r\n",read_buf);
	write_count = fwrite(read_buf,strlen(read_buf) ,1,fp1);
	if(write_count == 0)
	{
		printf("file write failed.\r\n");
		return 0;
	}
#endif
	if(-1 == pthread_join( id_read,NULL))
	{
		printf("pthread_join failed\r\n");
		return 0;
	}
	fclose(fp);
	fclose(fp1);
	return 0;
}








