#include<stdio.h>
#include<string.h>

int main(int argc , char** argv)
{
   FILE *fp=NULL;
   char write_buf[10] = "hello";
   char read_buf[10] = {0};
   int write_count =0,read_count=0;


    fp=fopen("./test.txt","w+");
    if(NULL==fp)
     {
     return 0;
     }

     write_count =          fwrite(write_buf,strlen(write_buf),1,fp);
      if(write_count<=0)
     {
     printf("file write failed.\r\n");
     return 0;
     }

     if(fseek(fp,0,0))
     {
     printf("file seek failed.\r\n");
     return 0;

     }

     read_count =          fread(read_buf,strlen(write_buf),1,fp);
      if(write_count<=0)
     {
     printf("file write failed.\r\n");
     return 0;
     }
     printf("read buf:%s\r\n",read_buf);

	fclose(fp);
	return 0;

}

