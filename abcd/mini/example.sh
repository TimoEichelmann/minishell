# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    example.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 12:42:11 by snegi             #+#    #+#              #
#    Updated: 2024/03/27 12:43:58 by snegi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash


ls non_existent_file
echo "Exit status of ls command: $?"


ls /tmp
echo "Exit status of ls command: $?"
