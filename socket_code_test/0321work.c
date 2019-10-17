#include<stdio.h>
#include<string.h>

int main(int argc , char** argv)
{
   FILE *fp=NULL,*fp1=NULL;
   char write_buf[10] = "hello";
   char read_buf[10] = {0};
   char read1_buf[10] = {0};

   int write_count =0,read_count=0;
   int write1_count =0,read1_count=0;

    fp=fopen("./test.txt","w+");
    fp1=fopen("./test1.txt","wt+");
    if(NULL==fp||NULL==fp1)
     {
     return 0;
     }

     write_count = fwrite(write_buf,strlen(write_buf),1,fp);
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

     read_count = fread(read_buf,strlen(write_buf),1,fp);
      if(read_count<=0)
     {
     printf("file read failed.\r\n");
     return 0;
     }
     printf("read buf:%s\r\n",read_buf);

   write_count = fwrite(read_buf,strlen(read_buf),1,fp1);
      if(write_count<=0)
     {
     printf("file write failed.\r\n");
     return 0;
     }

  /*   if(fseek(fp1,0,0))
     {
     printf("file seek1 failed.\r\n");
     return 0;

     }

     read1_count = fread(read1_buf,strlen(write1_buf),1,fp1);
      if(read1_count<=0)
     {
     printf("file read1 failed.\r\n");
     return 0;
     }
     printf("read1 buf:%s\r\n",read1_buf);*/
	fclose(fp);
        fclose(fp1);
	return 0;

}