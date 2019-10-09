#include <get_proc_info.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    int pid;
    long sys_return_value;
    struct procinfos info;
    pid = atoi(argv[1]);

    sys_return_value = get_proc_info(pid, &info);
    printf("Student ID: %ld\n", info.studentID);
    if (sys_return_value == 0)
    {
        printf("Current pid: %d [%s]\n", info.proc.pid, info.proc.name);
        printf("Parent pid: %d [%s]\n", info.parent_proc.pid, info.parent_proc.name);
        if (info.oldest_child_proc.pid == 0)
            printf("Dont have a child\n");
        else
            printf("Child pid: %d [%s]\n", info.oldest_child_proc.pid, info.oldest_child_proc.name);
    }
    else
        printf("Not found\n");
    return 0;
}
