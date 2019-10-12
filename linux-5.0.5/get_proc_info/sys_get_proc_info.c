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


SYSCALL_DEFINE2(get_proc_info, pid_t, pid, struct procinfos *, info)
//asmlinkage long sys_get_proc_info(pid_t pid, struct procinfos *info)
{
    struct task_struct *task_list;
    struct list_head *p;
    info->studentID = 1752242;
    for_each_process(task_list) 
    {
        if (task_list->pid == pid)
        {
            p = &task_list->children;
            if (list_empty(p)){
                strcpy(info->oldest_child_proc.name, "NOT");
                info->oldest_child_proc.pid = 0;
            }
            else
            {
                info->oldest_child_proc.pid = list_first_entry(&task_list->children, struct task_struct, sibling)->pid;
                 strcpy(info->oldest_child_proc.name, list_first_entry(&task_list->children, struct task_struct, sibling)->comm);
            }
            
            info->proc.pid = pid;
            strcpy(info->proc.name, task_list->comm);
        
            info->parent_proc.pid = task_list->parent->pid;
            strcpy(info->parent_proc.name, task_list->parent->comm);
            //printk("child: [%d], %s\n", info->oldest_child_proc.pid, info->oldest_child_proc.name);
            //printk("parent: [%d]\n", info->oldest_child_proc.pid);
            
            return 0;
        }
    }

    return -EINVAL;
}
//MODULE_LICENSE("GPL");
