CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = Mandatory_part/main.c Mandatory_part/ft_split.c Mandatory_part/ft_freesplit.c \
		Mandatory_part/ft_get_path.c Mandatory_part/utils_func.c \
		Mandatory_part/ft_close.c

OBJS = $(SRCS:.c=.o)

HEADER = Mandatory_part/ft_pipex.h

NAME = pipex

all: $(NAME)

$(OBJS): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
