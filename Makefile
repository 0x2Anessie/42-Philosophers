NAME = philo

SRC = main.c \
		parsing.c \
		init.c \
		routine.c \
		utils.c \
		philo_life_utils.c \

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