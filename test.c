#include <libc.h>

int main()
{
    char *line = "sgfsqwghdfqwydfqwd\n";
    write(1, line, strlen(line));
    write(1, line, strlen(line));
}