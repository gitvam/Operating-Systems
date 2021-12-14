#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <asm/uaccess.h>
#include <asm/current.h>

struct task_struct *curr;

int check_list(int pid,struct task_struct *s){

	int found=0;
	int i=0;
	struct list_head *list;
	struct task_struct *task ,*temp;
	task=s;
	printk("Task pid=%d\n",task->pid);
	list_for_each(list,&task->children){

		temp=list_entry(list,struct task_struct,sibling);
		printk("Temp%d=pid=%d\n",i,temp->pid);
		if(temp->pid==pid){
			found=1;
			break;
		}
		i++;

	}
	if(found!=1){
		return 1;
	}

	return 0;
}




asmlinkage long
sys_set_deadlines(int pid , int c_time,int deadline){

	int found=0;
	int i=0;

	printk("Vamvakousis Giorgos 4112 sys_set_deadlines\n");

	if(pid<-1){
		return EINVAL;
	}

	if(pid==-1){
		curr=get_current();
		found=1; /*Found the process */
	}
	else{
		for_each_process(curr){
			printk("FOREACH----Pid%dst=%d\n",i,curr->pid);
			if(curr->pid==pid && check_list(pid,curr->parent)==0){
				found=1;	/*Found the process*/
			}
				i++;
		}
	}
	if(found==1){
		curr->computation_time=c_time;
		curr->deadline=deadline;
	}

	if(curr->deadline <= curr->computation_time){
		return EINVAL;
	}
	printk("Pid: %d \n",curr->pid);
	printk("Computation Time:%d\n",curr->computation_time);
	printk("Deadline:%d\n",curr->deadline);

	return 0;

}
