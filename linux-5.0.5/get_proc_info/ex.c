#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/unistd.h>
#include <linux/sched/signal.h>
#include <linux/module.h>     
#include <linux/syscalls.h>


struct proc_info {
    pid_t pid;
    char name[16];
};
struct procinfos {
    long studentID;
    struct proc_info proc;
    struct proc_info parent_proc;
    struct proc_info oldest_child_proc;
};


//SYSCALL_DEFINE2(sys_get_proc_info, pid_t, pid, struct procinfos *, info)
asmlinkage long sys_get_proc_info(pid_t pid, struct procinfos *info)
{
    struct task_struct *task_list;
    struct list_head *head;
    info->studentID = 1752242;
    for_each_process(task_list) 
    {
        if (task_list->pid == pid)
        {
            head = &task_list->children;
            if (list_empty(head) == 1)
            {
                info->oldest_child_proc.pid = 0;
            }
            else
            {       
                info->oldest_child_proc.pid = list_first_entry(&task_list->children, struct task_struct, sibling)->pid;
            }


            info->proc.pid = pid;
            //info->parent_proc.pid = list_first_entry(&task_list->children, struct task_struct, sibling)->pid;
            info->parent_proc.pid = task_list->parent->pid;
            printk("parent: [%d]\n", info->parent_proc.pid);
            printk("child: [%d]\n", info->oldest_child_proc.pid);
            return 0;
        }
    }
    return -EINVAL;
}

int init_module(void)
{
    pid_t pid = 5424;
    struct procinfos temp;
    sys_get_proc_info(pid, &temp);
    return 0;
}
void cleanup_module(void)
{
    printk(KERN_INFO "CLEAN\n");
}
