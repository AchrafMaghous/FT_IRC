/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <acmaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:47:43 by acmaghou          #+#    #+#             */
/*   Updated: 2023/02/27 18:12:04 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

static void usage() {
	std::cout << "A simple Internet server application.\n"
			  << "It listens to the port written in command line (default 1234),\n"
			  << "accepts a connection, and sends the \"Hello!\" message to a client.\n"
			  << "Then it receives the answer from a client and terminates.\n\n"
			  << "Usage:\n"
			  << "     server [port_to_listen]\n"
			  << "Default is the port 1234.\n";
}

int	main(int ac, char **av) {
	if (ac > 1 && *(av[1]) == '-') {
		usage();
		return	1;
	}
	int	port = 6969;
	if (ac > 1)
		port = atoi(av[1]);
	int	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return 2;
	}
	
	struct sockaddr_in	addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int	res = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
	if (res < 0) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return 3;
	}

	struct linger	linger_opt = {1, 0};
	setsockopt(sock, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

	res = listen(sock , 1);
	if (res < 0) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return 4;
	}

	struct	sockaddr_in	peeraddr;
	socklen_t	peeraddr_len;
	int	sock2 = accept(sock, (struct sockaddr*)&peeraddr, &peeraddr_len);
	if (sock2 < 0) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return 5;
	}

	std::cout << "Connection from IP "
			<< ( ( ntohl(peeraddr.sin_addr.s_addr) >> 24) & 0xff ) << "."  // High byte of address
			<< ( ( ntohl(peeraddr.sin_addr.s_addr) >> 16) & 0xff ) << "."
			<< ( ( ntohl(peeraddr.sin_addr.s_addr) >> 8) & 0xff )  << "."
			<< ( ntohl(peeraddr.sin_addr.s_addr) & 0xff ) << ", port "   // Low byte of addr
			<< ntohs(peeraddr.sin_port);
	res = close(sock);
	write(sock2, "Hello!\r\n", 8);
	char	buffer[1024];
	res = read(sock2, buffer, 1023);
	if (res < 0) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return 6;
	}

	buffer[res] = 0;
	std::cout << "Received " << res << " bytes:\n" << buffer;

	close(sock2);
	return 0;
}