CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = client.c server.c
OBJS = $(SRCS:.c=.o)

all: client server

client: client.o libft
	$(CC) $(CFLAGS) -o $@ $< -Llibft -lft

server: server.o libft
	$(CC) $(CFLAGS) -o $@ $< -Llibft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	make -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f client server
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft
