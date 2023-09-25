/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:29:37 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/25 08:34:19 by aerrazik         ###   ########.fr       */
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

bool valid_password(std::string nickname) {
    std::string::iterator it = nickname.begin();
    for (; it != nickname.end(); it++) {
        if (!((*it >= '0' && *it <= '9') || (*it >= 'A' && *it <= 'Z') || (*it >= 'a' && *it <= 'z'))) {
            return (false);
        }
    }
    return (true);
}
