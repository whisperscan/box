/*
 * pro_fun.c
 *
 *  Created on: 2014年9月30日
 *      Author: lipengfei
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

int max(int a,int b)
{
	if(a > b)
		return a;
	else
		return b;
}

void pro_fun(FILE *fd,int sockfd)
{
	int maxFd1,isStdinEOF;
	fd_set rSet;
	char buff[BUFSIZ];
	int n;

	isStdinEOF = 0;
	FD_ZERO(&rSet);
	memset(buff,'\0',sizeof(buff));
	for(;;)
	{
		if(isStdinEOF == 0)
		{
			FD_SET(fileno(fd),&rSet);
		}
		FD_SET(sockfd,&rSet);
		maxFd1 = max(fileno(fd),sockfd) + 1;
		select(maxFd1,&rSet,NULL,NULL,NULL);

		//stdin
		if(FD_ISSET(fileno(fd),&rSet))
		{
			if((n = read(fileno(fd),buff,BUFSIZ)) == 0)
			{
				isStdinEOF = 1;
				shutdown(sockfd,SHUT_WR);
				continue;
			}
			write(sockfd,buff,n);
		}

		//socket
		if(FD_ISSET(sockfd,&rSet))
		{
			if((n = read(sockfd,buff,BUFSIZ)) == 0)
			{
				if(isStdinEOF == 1)
					return;
				else
					printf("\nserver terminated permaturely\n");
					return;
			}
//			write(fileno(stdout),buff,n);
			printf("%s",buff);
		}
	}
}
