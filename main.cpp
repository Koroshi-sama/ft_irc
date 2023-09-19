/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:28:32 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/19 10:34:39 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/ircserv.hpp"
#include "command/command.hpp"

int main(int ac, char **av) {
    if (ac != 3) {
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return (1);
    }
    
    ircserv irc(std::atoi(av[1]), av[2]);
    
    // Create socket and bind it to port. Check ircserv.cpp for more info
    
    if (irc.start_server()) {
        struct pollfd fds[MAX_NUMB_CLIENTS];
        int countClients = 0;
        fds[0].fd = irc.get_socket();
        fds[0].events = POLLIN;
        
        // While loop: Listen for incoming connections and handle them. The poll() function do the job of handling multiple clients at the same time.
        // Read about poll() or watch a video to understand how it works. "Events, Revents, POLLIN, ..."

        Command command(&irc);
        
        while (true) {
            int pollCount = poll(fds, countClients + 1, -1);
            if (pollCount == -1) {
                std::cerr << "Error: poll failed" << std::endl;
                break;
            }
            if (fds[0].revents && POLLIN) {
                // Accept new connection. Check client.cpp for accept_client() function.
                int client_socket = irc.accept_client();
                if (client_socket != -1) {
                    countClients++;
                    fds[countClients].fd = client_socket;
                    fds[countClients].events = POLLIN;
                }
                
            }
            for (int i = 1; i <= countClients; i++) {
                std::cout << "---------" << countClients << std::endl;
                if (fds[i].revents && POLLIN) {
                    std::cout << "----> Entered if fds <----" << std::endl;
                    // Receive message from client: buffer that will contain the message, bytesReceived: number of bytes received, all this handled by recv() function.
                    char buffer[MAX_BUFFER];
                    memset(buffer, 0, sizeof(buffer));
                    int bytesReceived = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                    if (bytesReceived == -1) {
                        std::cerr << "Error reading from client" << std::endl;
                        break;
                    }
                    else if (strcmp(buffer, "QUIT\n") == 0 || bytesReceived == 0) {
                        // Remove client from the map and close the socket. Check client.cpp for remove_client() function.

                        /**DEBUG MSG**/
                        std::cout << "Client " << fds[i].fd << " disconnected" << std::endl;
                        /**DEBUG MSG**/

                        irc.remove_client(fds[i].fd);
                        close(fds[i].fd);
                        countClients--;
                        for (int j = i; j <= countClients; j++) {
                            fds[j] = fds[j + 1];
                        }
                    }
                    else {
                        
                        /**DEBUG MSG**/
                        std::cout << "--------------------------------------------------------------" << std::endl;
                        std::cout << "Received from client " << fds[i].fd << ": " << buffer << std::endl;
                        std::cout << "--------------------------------------------------------------" << std::endl;
                        /**DEBUG MSG**/

                        command.handle_commands(buffer, fds[i].fd);
                    }
                }
            }

        }
        // Close the socket, stop the server. Check ircserv.cpp for stop_server() function.
        irc.stop_server();
    }
    return 0;
}
