#include <stdio.h>
#include <unistd.h>
int main()
{
    char *output;
    output = get_current_dir_name();
    printf("%s\n", output);
}