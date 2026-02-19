#include <unistd.h>
#include<stdio.h>
#define COUNT 1000
int main()
{
    char tmp[COUNT];
    getcwd(tmp, COUNT);
    printf("%s\n",tmp);
    return 0;
}
       //char *getcwd(char buf[.size], size_t size);
       //char *get_current_dir_name(void);

