CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
ft_hashmap.c ft_hm_node.c ft_free.c

OBJS = $(SRCS:.c=.o)

BONUS_SRCS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBS = printf/libftprintf.a

all: printf $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS) $(LIBS)

bonus: $(NAME) $(BONUS_OBJS)
	ar -rcs $(NAME) $(BONUS_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

printf:
	make -C printf

clean:
	make -C printf clean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(LIBS)

re: fclean all

deb: fclean
	$(CC) $(CFLAGS) -g -fsanitize=address main.c $(NAME) -o test

leaks: fclean
	$(CC) $(CFLAGS) -g main.c $(NAME) -o test

.PHONY: all bonus printf clean fclean re test