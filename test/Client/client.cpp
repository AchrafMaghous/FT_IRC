/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <acmaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:50:18 by acmaghou          #+#    #+#             */
/*   Updated: 2023/02/27 18:12:58 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

static void usage()
{
	std::cout << "A simple Internet client application.\n"
			  << "Usage:\n"
			  << "         client [IP_address_of_server [port_of_server]]\n"
			  << "     where IP_address_of_server is either IP number of server\n"
			  << "     or a symbolic Internet name, default is \"localhost\";\n"
			  << "     port_of_server is a port number, default is 1234.\n"
			  << "The client connects to a server which address is given in a\n"
			  << "command line, receives a message from a server, sends the message\n"
			  << "\"Thanks! Bye-bye...\", and terminates.\n";
}

int	main(int ac, char **av) {
	if (ac > 1 && *av[1] == '-') {
		usage();
		return 1;
	}

	int	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return 2;
	}

	struct	sockaddr_in	server;
	int	serverAddrLen;
	bzero(&server, sizeof(server));

	std::string	peerHost = "localhost";
	if (ac > 1)
		peerHost.assign(av[1]);
	
	struct	hostent	*host = gethostbyname(peerHost.c_str());
	if (host == NULL) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return 3;
	}

	server.sin_family = AF_INET;
	short	peerPort = 6969;
	if (ac >= 3)
		peerPort = (short) atoi(av[2]);
	server.sin_port = htons(peerPort);

	std::cout << "server address = " << (host->h_addr_list[0][0] & 0xff) << "." <<
										(host->h_addr_list[0][1] & 0xff) << "." <<
										(host->h_addr_list[0][2] & 0xff) << "." <<
										(host->h_addr_list[0][3] & 0xff) << ", port " <<
										static_cast<int>(peerPort) << std::endl;
	
	memmove(&(server.sin_addr.s_addr), host->h_addr_list[0], 4);
	
	int	res = connect(sock, (struct sockaddr*)&server, sizeof(server));
	if (res < 0) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return 4;
	}

	std::cout << "Connected. Reading a server message" << std::endl;
	
	char	buffer[1024];
	res = read(sock, buffer, 1024);
	if (res < 0) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return 5;
	}

	std::cout << "Received: " << "\n" << buffer;
	write(sock, "Bye-Bye...\r\n", 20);
	close(sock);
	return 0;
}