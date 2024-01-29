# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acatusse <acatusse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 17:06:53 by acatusse          #+#    #+#              #
#    Updated: 2024/01/05 17:06:56 by acatusse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philo.c \
		init.c \
		life.c \
		utils.c \
		check_death.c \

OBJ = $(SRC:.c=.o)
CC = cc
CFLAG = -Wall -Wextra -Werror 

all: 			$(NAME)
				@clear
				@echo "__________ __     __ __                             __                          ";
				@echo "\______   \  |__ |__|  |   ____  __________ ______ |  |__   ___________  ______ ";
				@echo " |     ___/  |  \|  |  |  /    \/  ___/    \\____  \|  |  \ / __ \_  __ \/  ___/ ";
				@echo " |    |   |   Y  \  |  |_|   |  |___  \  |  |   |  |   Y  \  ___/|  | \/\___ \  ";
				@echo " |____|   |___|  /__|____/\____/______/____/|   __/|___|  /\_____\__|  /_____/ ";
				@echo "               \/                           |__|        \/                     ";

%.o: %.c
	$(CC) -c $(CFLAG) $< -o $@ -I.
# -c sert a creer fichier objet
# -o sert a creer le fichier executable
# -I sert a inclure les header (.h)

$(NAME): 		$(OBJ)
				$(CC) -pthread -lpthread $(CFLAG) -o $(NAME) $(OBJ) -I.

clean:
				rm -f $(OBJ)
				@clear
				@echo "        /\                __              __                         ";
				@echo "  ____  )/ ____   _______/  |_      ____ |  |   ____  _____    ____   ";
				@echo "/  ___\  /  __ \ /  ___/\   __\   /  ___\|  | /  __ \ \__  \  /    \  ";
				@echo "\  \___  \  ___/ \___ \  |  |     \  \___|  |_\  ___/ / __  \|   |  \ ";
				@echo " \____ >  \____ >_____ > |__|      \____ >____/\____> ____  / ___|  / ";
				@echo "                                                          \/      \/  ";
# -r sert a effacer recursivement les sous repertoires
# -f sert a ne pas demander de confirmation d'effacement, et ne pas renvoyer de code erreur quand le fichier n'existe pas

fclean: 		clean
				rm -rf $(NAME)
				@clear
				@echo "        /\                __        _____       __                         ";
				@echo "  ____  )/ ____   _______/  |_    _/ ____\____ |  |   ____  _____    ____   ";
				@echo "/  ___\  /  __ \ /  ___/\   __\   \  __\/  ___\|  | /  __ \ \__  \  /    \  ";
				@echo "\  \___  \  ___/ \___ \  |  |      |  | \  \___|  |_\  ___/  / __ \|   |  \ ";
				@echo " \____ >  \____> _____ > |__|      |__|  \____ >____/\____ > ____  /___|  / ";
				@echo "                                                                 \/     \/  ";

re: 			fclean all

.PHONY: 		all clean fclean re
