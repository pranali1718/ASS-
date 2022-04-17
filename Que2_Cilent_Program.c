#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>

int main()
{
	char *serv_ip = "127.0.0.1";
	int sock_fd, return_val;

	struct sockaddr_in serveradd;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd < 0)
	{
		perror("sock: ");
		exit(1);
	}

	bzero(&serveradd, sizeof(serveradd));
	serveradd.sin_family = AF_INET;
	serveradd.sin_port = htons(8000);
	inet_pton(AF_INET, serv_ip, &serveradd.sin_addr);

	return_val = connect(sock_fd, (struct sockaddr *) &serveradd, sizeof(serveradd));
	if(return_val < 0)
	{
		perror("connect: ");
		exit(2);
	}

	printf("client established connection with server\n");

	while(1)
	{
		int n;

		char s_buffer[200];
		char r_buffer[200];

		printf("\nEnter The Data Send To The Server: \n");
		gets(s_buffer);
	
		write(sock_fd , s_buffer, strlen(s_buffer));

		n = read(sock_fd, r_buffer, sizeof(r_buffer));
		r_buffer[n] = '\0';
		printf("\nData Received From The Server:\n %s\n", r_buffer);

	}

	close(sock_fd);
    return 0;
}