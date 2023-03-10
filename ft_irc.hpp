/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <acmaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:45:16 by acmaghou          #+#    #+#             */
/*   Updated: 2023/02/28 14:56:52 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_IRC_HPP
#define FT_IRC_HPP

#include <iostream>
#include <errno.h>
#include <cstring>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

struct	client {
	int			sockfd;
	std::string	nickname;
	std::string	channel;
};


#endif