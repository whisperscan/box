/*
 * client.c
 *
 *  Created on: 2014年9月30日
 *      Author: lipengfei
 */
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

extern void pro_fun(FILE* fd,int sockfd);

int main(void)
{
	struct sockaddr_in address;
	int sockfd;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	address.sin_family = AF_INET;
	address.sin_port = htons(50001);
	inet_pton(AF_INET,"localhost",&address.sin_addr);

	connect(sockfd,(struct sockaddr *)&address,sizeof(address));
	printf("input: ");
	fflush(stdout);
	pro_fun(stdin,sockfd);
	close(sockfd);
	exit(0);
}


