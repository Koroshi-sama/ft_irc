/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:31:40 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/23 11:37:53 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include <poll.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <algorithm>
#include <fcntl.h>

#include <ctime>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"


std::vector<std::string> split(const std::string& s, char delimiter);
std::string to_string(int n);
std::string strtrim(std::string& str);
std::string set_color(std::string client);

#endif