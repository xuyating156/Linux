#include <stdio.h>
#define FILE_PATH "./file.c"
#define FILE_WAY_OW  "a+"
#define MIN_ARG_AMOUT 2

int main(int argc , char** argv)
{

    FILE* fp=NULL;//定义文件流为空
    size_t w_count = 0 ,r_count=0;
    int a=97,b=0,c=0;
    if(MIN_ARG_AMOUT!=argc)//判断输入是否为两个
        {
           printf("Usage:%s{FILE_PATH}\r\n",argv[0]);
            return 0;
        }

       fp=fopen(argv[1],FILE_WAY_OW);//打开文件流
       if(NULL == fp)
       {
          printf("open failed. \r\n");
          return 0;
        }

         w_count=fwrite(&a,1,sizeof(1),fp);//在文件中输入整形
         printf("w_count:%ld\r\n",w_count);
         if(w_count<=0)
         {
           printf("fwrite failed. \r\n");
            return 0;
          }

          c=fseek(fp,-sizeof(a),SEEK_CUR);//文件字符从当前位置开始向左移动四个
          if(c)
          {
           printf("fseek failed. \r\n");
           return 0;
           }


           r_count=fread(&b,sizeof(int),sizeof(a)/sizeof(int),fp);//读出文件内容
           printf("r_count %ld\r\n",r_count);
           if(r_count<=0)
           {
                         printf("fread failed. \r\n");
                         return 0;
            }
            else
            {
             printf("b:%d\r\n",b);
            }


          else
          {
           printf("c: %d\r\n",c);
           }
          fcolse(fp);//关闭文件
}