#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define set_deadlines(a,b,c)	syscall(342,a,b)


struct d_params {
	unsigned long deadline;
	unsigned long computation_time;
};

int main(){

	srand(time(0));

	struct d_params test;
	pid_t pid;
	int process=0;

	printf("First test:curr->deadline > curr->computation_time\n\n");

	printf("Calling 1st time syscall set_deadlines\n");
	if(set_deadlines(-1,100,120)){
		printf("Error at 1st call of system call set_deadlines\n");
	}


	printf("Test.deadline=%d\n",test.deadline);
	printf("Test.computation_time=%d\n",test.computation_time);

/*----------------------------------------------------------------------------------*/
	printf("\nSecond test: curr->deadline <= curr->computation_time\n\n");
	printf("Calling 2st time syscall set_deadlines\n");
	if(set_deadlines(-1,125,120)){
		printf("Error at 2st call of system call set_deadlines\n");
	}

/*-----------------------------------------------------------------------------------*/
	printf("\nThird test: Random process\n\n");
	process=rand();
	printf("Calling 3st time syscall set_deadlines\n");
	if(set_deadlines(process,120,100)){
		printf("Error at 3st call of system call set_deadlines\n");
	}


/*-----------------------------------------------------------------------------------*/
	printf("\nForth test: Child process\n\n");
	printf("Forking child\n");
	process=getpid();
	if((pid=fork())==0){
		printf("Pid of child=%d\n",process);
		if(set_deadlines(process,205,200)){
		printf("Error at 4st call of system call set_deadlines\n");
		}

		printf("Test.deadline=%d\n",test.deadline);
		printf("Test.computation_time=%d\n",test.computation_time);

	}
	else{
		wait(NULL);
	}

return 0;
}
