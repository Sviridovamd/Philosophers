SRC		= main.c utils.c start_game.c loop_live.c

OBJS	= $(SRC:.c=.o)

OBJSB	= $(SRCB:.c=.o)

NAME	= philo

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -pthread

all:		$(NAME)

$(NAME):    $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS) $(OBJSB)

fclean:		clean
			$(RM) $(NAME)
re:			fclean all