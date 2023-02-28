/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <acmaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:42:48 by acmaghou          #+#    #+#             */
/*   Updated: 2023/02/28 17:38:00 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

const int	MAX_CONNECTIONS = 1024;
const int	MAX_MSG_SIZE = 1024;

int	main(int ac, char **av) {
	int			port;
	std::string	password;
	if (ac != 3) {
		std::cerr << "Usage: " << av[0] << " <port> <password>\n";
		return 1;
	}
	port = atoi(av[1]);
	password = av[2];
	
	int	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
		return 2;
	}
	int	optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	struct sockaddr_in	servaddr;
	
	memset(&servaddr, 0 , sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		std::cerr << "Failed to bind socket: " << strerror(errno) << std::endl;
		return 3;
	}
	
	if (listen(sockfd, MAX_CONNECTIONS) < 0) {
		std::cerr << "Cannot listen to socket: " << strerror(errno) << std::endl;
		return 4;
	}
	std::vector<client>	clients;
	char	buf[MAX_MSG_SIZE];
	while (true) {
		struct	sockaddr_in	cliaddr;
		socklen_t	clilen = sizeof(cliaddr);
		int	connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
		if (connfd < 0) {
			std::cerr << "Error accepting connection: " << strerror(errno) << std::endl;
			continue;
		}

		std::string	welcome_msg = "Welcome to the sex dungeon.\r\n";
		send(connfd, welcome_msg.c_str(), welcome_msg.size(), 0);
		
		int	nbytes = recv(connfd, buf, MAX_MSG_SIZE, 0);
		if (nbytes <= 0) {
			close(connfd);
			continue;
		}
		buf[nbytes] = '\0';
		// Parse the incoming message
	}
	close(sockfd);
	return 0;  
}