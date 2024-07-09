CC = gcc
CFLAGS = -Wall -Wextra -Werror

C_SRCS = client.c client_utils.c
C_OBJS = $(C_SRCS:.c=.o)

S_SRCS = server.c server_utils.c
S_OBJS = $(S_SRCS:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: client server

client: $(C_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(C_OBJS) -L$(LIBFT_DIR) -lft

server: $(S_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(S_OBJS) -L$(LIBFT_DIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f client server
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

deb: CFLAGS += -g3 -fsanitize=address
deb: re

leaks: CFLAGS += -g3
leaks: re
