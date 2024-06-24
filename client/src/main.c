#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int		sock = 0;
int		interrupted = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	interrupted = 1;
	if (sock)
		close(sock);
	exit(0);
}

int	main(void)
{
	struct sockaddr_in	serv_addr;
	char				buffer[BUFFER_SIZE] = {0};
	fd_set				readfds;
	int					max_sd;
	int					valread;

	signal(SIGINT, sigint_handler);
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Socket creation error");
		return (-1);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		perror("Invalid address/ Address not supported");
		return (-1);
	}
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("Connection Failed");
		return (-1);
	}
	printf("Connected to server\n");
	while (!interrupted)
	{
		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);
		FD_SET(STDIN_FILENO, &readfds);
		max_sd = sock > STDIN_FILENO ? sock : STDIN_FILENO;
		select(max_sd + 1, &readfds, NULL, NULL, NULL);
		if (FD_ISSET(STDIN_FILENO, &readfds))
		{
			fgets(buffer, BUFFER_SIZE, stdin);
			send(sock, buffer, strlen(buffer), 0);
		}
		if (FD_ISSET(sock, &readfds))
		{
			valread = read(sock, buffer, BUFFER_SIZE);
			if (valread > 0)
			{
				buffer[valread] = '\0';
				if (strcmp(buffer, "exit") == 0)
				{
					interrupted = 1;
					if (sock)
						close(sock);
					exit(0);
				}
				printf("Received: %s", buffer);
			}
		}
	}
	close(sock);
	return (0);
}