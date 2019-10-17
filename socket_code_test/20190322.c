#include<stdio.h>
#include<pthread.h>

void * pthread1(void*a)
{
printf("hello\r\n");
return NULL;
}

int main(int argc,char **argv)
{
   pthread_t id=0;
   if(0!=pthread_create(&id,NULL,pthread1,NULL))
    {
    printf("pthread_create faile.\r\n");
     return 0;
    }

   if(-1== phread_join(id,NULL))
    {
    printf("pthread_join faile.\r\n");
     return 0;
    }
return 0;


}