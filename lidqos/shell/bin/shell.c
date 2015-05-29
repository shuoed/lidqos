/*
 * shell.c
 *
 *  Created on: Nov 26, 2014
 *      Author: lidq
 */

#include <shell/shell.h>

int main(int argc, char **args)
{
	char *buff = malloc(0x200);
	char ch = 0;

	printf("\nlidq-os login: ");
	scanf("%s", buff);
	printf("Password: ");
	while (ch != '\n')
	{
		ch = getchar();
	}
	printf("\n");
	do
	{
		printf("[lidq-os /]$ ");
		//scanf("%s", buff);
//		execute_cmd(buff);
		execute_cmd("/usr/bin/example_fpu");
	}
	while (1);

	return 0;
}

void execute_cmd(char *cmd)
{
	if (str_len(cmd) > 0)
	{
		install_program(cmd, "");
	}
}

void install_program(char *path, char *args)
{
	u32 sem_addr = 0;
	int params[0x10];
	params[0] = 0;
	params[1] = (int) path;
	params[2] = (int) args;
	params[3] = (int) &sem_addr;
	__asm__ volatile("int $0x80" :: "a"(params));
	if (sem_addr != 0)
	{
		sem_wait_shell(sem_addr);
		sem_post_shell(sem_addr + sizeof(s_sem));
	}
}

