#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define COUNT 100
int main(int argc,char** argv)
{
    if(argc!=3)
        exit(-2);

    char * src=argv[1];
    char * dst=argv[2];

    int srcFd=open(src,O_RDONLY);
    if(srcFd<=-1)
        exit(-9);
    int dstFd=open(dst,O_WRONLY|O_CREAT|O_TRUNC,0644);


    if(srcFd<=-1||dstFd<=-1)
        exit(-5);

    char tmp[100];

    int tmpCount=0;
    while((tmpCount=read(srcFd,tmp,COUNT))>0)
    {
        write(dstFd,tmp,tmpCount);
    }
    if(unlink(src)!=0)
        exit(-18);
    
    close(dstFd);
    return 0;
}