/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:28:32 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/08 18:41:46 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

int main(int ac, char **av) {
    if (ac != 3) {
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return (1);
    }
    
    ircserv irc(std::atoi(av[1]), av[2]);

    if (irc.start_server()) {
        // std::cout << "Server started on port " << av[1] << std::endl;
        struct pollfd fds[MAX_NUMB_CLIENTS];
        int countClients = 0;
        fds[0].fd = irc.get_socket();
        fds[0].events = POLLIN;
        while (true) {
            int pollCount = poll(fds, countClients + 1, -1);
            if (pollCount == -1) {
                std::cerr << "Error: poll failed" << std::endl;
                break;
            }
            if (fds[0].revents && POLLIN) {
                int client_socket = irc.accept_client();
                if (client_socket != -1) {
                    countClients++;
                    fds[countClients].fd = client_socket;
                    fds[countClients].events = POLLIN;
                }
                
            }
            for (int i = 1; i <= countClients; i++) {
                if (fds[i].revents && POLLIN) {
                    char buffer[MAX_BUFFER];
                    memset(buffer, 0, sizeof(buffer));
                    int bytesReceived = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                    if (bytesReceived == -1) {
                        std::cerr << "Error reading from client" << std::endl;
                        break;
                    }
                    else if (strcmp(buffer, "QUIT\n") == 0 || bytesReceived == 0) {
                        std::cout << "Client " << fds[i].fd << " disconnected" << std::endl;
                        irc.remove_client(fds[i].fd);
                        close(fds[i].fd);
                        countClients--;
                        for (int j = i; j <= countClients; j++) {
                            fds[j] = fds[j + 1];
                        }
                    }
                    else {
                        std::cout << "Received from client " << fds[i].fd << ": " << buffer << std::endl;
                        irc.broadcast_message(fds[i].fd, buffer);
                    }
                }
            }

        }
        irc.stop_server();
    }
    return 0;
}
