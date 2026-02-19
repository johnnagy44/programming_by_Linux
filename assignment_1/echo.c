#include<stdio.h>
int main(int argc,char ** argv)
{
    if(argc==1)
    {
        printf("\n");
        return 0;
    }
    for(int i=1;i<argc;i++)
    {
        if(i+1==argc)
            printf("%s",argv[i]);
        else
            printf("%s ",argv[i]);
    }
    printf("\n");
    return 0;

}