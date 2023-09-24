/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:28:32 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/24 15:07:26 by atouba           ###   ########.fr       */
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
        // struct pollfd fds[MAX_NUMB_CLIENTS];
        irc.countClients = 0;
        irc.fds[0].fd = irc.get_socket();
        irc.fds[0].events = POLLIN;
        
        // While loop: Listen for incoming connections and handle them. The poll() function do the job of handling multiple clients at the same time.
        // Read about poll() or watch a video to understand how it works. "Events, Revents, POLLIN, ..."

        Command command(&irc);
        
        while (true) {
            int pollCount = poll(irc.fds, irc.countClients + 1, -1);
            if (pollCount == -1) {
                std::cerr << "Error: poll failed" << std::endl;
                break;
            }
            if (irc.fds[0].revents && POLLIN) {
                // Accept new connection. Check client.cpp for accept_client() function.
                int client_socket = irc.accept_client();
                std::cout << "client_socket: " << client_socket << std::endl;
                if (client_socket != -1) {
                    irc.countClients++;
                    irc.fds[irc.countClients].fd = client_socket;
                    irc.fds[irc.countClients].events = POLLIN;

                    // set the socket to non-blocking mode
                    fcntl(client_socket, F_SETFL, O_NONBLOCK);
                }
                
            }
            for (int i = 1; i <= irc.countClients; i++) {
                std::cout << "---------" << irc.countClients << std::endl;
                if (irc.fds[i].revents && POLLIN) {
                    std::cout << "----> Entered if irc.fds <----" << std::endl;
                    // Receive message from client: buffer that will contain the message, bytesReceived: number of bytes received, all this handled by recv() function.
                    char buffer[MAX_BUFFER];
                    memset(buffer, 0, sizeof(buffer));
                    int bytesReceived = recv(irc.fds[i].fd, buffer, sizeof(buffer), 0);
                    if (bytesReceived == -1) {
                        std::cerr << "Error reading from client" << std::endl;
                        irc.countClients = irc.remove_client(i, irc.countClients);
                        break;
                    }
                    else if (bytesReceived == 0) {
                        std::cout << "Client " << irc.fds[i].fd << " disconnectedddddddd" << std::endl;
                        irc._clients[irc.fds[i].fd]->set_status(HAS_QUITED);
                        irc.countClients = irc.remove_client(i, irc.countClients);
                        break;
                    }
                    else {
                        /**DEBUG MSG**/
                        std::cout << "--------------------------------------------------------------" << std::endl;
                        std::cout << "Received from client " << irc.fds[i].fd << ": " << buffer << std::endl;
                        std::cout << "--------------------------------------------------------------" << std::endl;
                        /**DEBUG MSG**/

                        command.handle_commands(buffer, irc.fds[i].fd);
                        irc.countClients = irc.remove_client(i, irc.countClients);
                    }
                }
            }
        }
        // Close the socket, stop the server. Check ircserv.cpp for stop_server() function.
        irc.stop_server();
    }
    return 0;
}
