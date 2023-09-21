/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:01:05 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/20 19:49:42 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

void Command::join(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Joooooooin" << vc[1] << client_socket << std::endl;
}
