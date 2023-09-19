/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:29:37 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/18 16:05:32 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/client.hpp"
#include "includes.hpp"


std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(s);
    std::string token;

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

std::string to_string(int n) {
    std::string str;
    std::stringstream ss;
    ss << n;
    ss >> str;
    return (str);
}

std::string strtrim(std::string& str) {
    std::string trimmed = str;

    size_t start = trimmed.find_first_not_of(" \t\n\r");

    if (start != std::string::npos) {
        size_t end = trimmed.find_last_not_of(" \t\n\r");
        trimmed = trimmed.substr(start, end - start + 1);
    } else {
        trimmed.clear();
    }
    return trimmed;
}

std::string set_color(std::string client) {
    std::string clientt = strtrim(client);
    std::string colored_client;
    srand(time(NULL));
    int color = rand() % 6;

    if (color == 0)
        colored_client = RED + clientt + RESET;
    else if (color == 1)
        colored_client = GREEN + clientt + RESET;
    else if (color == 2)
        colored_client = BLUE + clientt + RESET;
    else if (color == 3)
        colored_client = YELLOW + clientt + RESET;
    else if (color == 4)
        colored_client = CYAN + clientt + RESET;
    else if (color == 5)
        colored_client = MAGENTA + clientt + RESET;
    return (colored_client);
}
