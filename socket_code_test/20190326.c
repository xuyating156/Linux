#include<stdio.h>
#include<sys/socket.h>

int main(int argc , char** argv)
{
  int b=0;//返回的句柄
  b = socket(AF_INET, SOCK_STREAM, 0);
  if(-1==b)
  {
  printf("socket failed\r\n");
  return 0;
  }
  printf("b:%d\r\n",b);
  return 0;
}