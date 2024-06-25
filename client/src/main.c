#include "../inc/hck.h"

void	hck_main_socket_loop(t_hck *d)
{
	char	buffer[BUFFER_SIZE] = {0};
	fd_set	readfds;
	int		max_sd;
	int		valread;

	valread = 0;
	while (1)
	{
		FD_ZERO(&readfds);
		FD_SET(d->d_skt.socket, &readfds);
		d->d_skt.readfds = readfds;
		FD_SET(STDIN_FILENO, &readfds);
		max_sd = d->d_skt.socket > STDIN_FILENO ? d->d_skt.socket : STDIN_FILENO;
		select(max_sd + 1, &readfds, NULL, NULL, NULL);
		if (FD_ISSET(STDIN_FILENO, &readfds))
		{
			fgets(buffer, BUFFER_SIZE, stdin);
			send(d->d_skt.socket, buffer, strlen(buffer), 0);
		}
		if (FD_ISSET(d->d_skt.socket, &readfds))
		{
			valread = read(d->d_skt.socket, buffer, BUFFER_SIZE);
			if (valread > 0)
			{
				buffer[valread] = '\0';
				pthread_mutex_lock(&d->mtx);
				hck_perform_act(&d->d_skt, &d->d_mlx, buffer);
				pthread_mutex_unlock(&d->mtx);
			}
		}
	}
}

void	hck_main_socket_create(struct sockaddr_in *serv_addr, t_skt *skt)
{
	if ((skt->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Socket creation error");
		exit(1);
	}
	serv_addr->sin_family = AF_INET;
	serv_addr->sin_port = htons(PORT);
	if (inet_pton(AF_INET, skt->ip, &serv_addr->sin_addr) <= 0)
	{
		perror("Invalid address/ Address not supported");
		exit(1);
	}
	if (connect(skt->socket, (struct sockaddr *)serv_addr,
			sizeof((*serv_addr))) < 0)
	{
		perror("Connection Failed");
		exit(1);
	}
	printf("Connected to server\n");
}

void	*hck_skt_loop(void *ag)
{
	struct sockaddr_in	serv_addr;
	t_hck				*d;

	d = (t_hck *)ag;
	hck_main_socket_create(&serv_addr, &d->d_skt);
	hck_main_socket_loop(d);
	close(d->d_skt.socket);
	return (NULL);
}

void	*hck_mlx_loop(void *ag)
{
	t_hck	*d;

	d = (t_hck *)ag;
	hck_mlx_init(&d->d_mlx);
	pthread_mutex_lock(&d->mtx);
	hck_ctrl(d);
	pthread_mutex_unlock(&d->mtx);
	mlx_loop(d->d_mlx.mlx);
	// mlx_loop_hook(&d->d_mlx.mlx, &hck_ctrl, d);
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	t[2];
	t_hck		d;

	if (ac < 2)
		exit(1);
	d.d_mlx.adr = NULL;
	d.d_mlx.bpp = 0;
	d.d_mlx.end = 0;
	d.d_mlx.len = 0;
	d.d_mlx.map = 0;
	d.d_mlx.map_img = NULL;
	d.d_mlx.player = 0;
	d.d_mlx.win = NULL;
	d.d_skt.ip = av[1];
	d.d_skt.socket = 0;
	XInitThreads();
	pthread_mutex_init(&d.mtx, NULL);
	pthread_create(&t[0], NULL, &hck_mlx_loop, (void *)&d);
	pthread_create(&t[1], NULL, &hck_skt_loop, (void *)&d);
	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);
	pthread_mutex_destroy(&d.mtx);
	return (0);
}
