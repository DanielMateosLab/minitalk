CC = gcc

NAME = libft.a
BUILD_DIR = build

PRINTF_SRCS = printf/ft_printf.c printf/pf_putchar.c printf/pf_puthex.c \
printf/pf_putnbr.c printf/pf_putptr.c printf/pf_putstr.c printf/pf_putunbr.c \
printf/pf_check_err.c

BONUS_SRCS = src/ft_lstadd_back_bonus.c src/ft_lstadd_front_bonus.c src/ft_lstclear_bonus.c \
src/ft_lstdelone_bonus.c src/ft_lstiter_bonus.c src/ft_lstlast_bonus.c src/ft_lstmap_bonus.c \
src/ft_lstnew_bonus.c src/ft_lstsize_bonus.c

SRCS = $(BONUS_SRCS) $(PRINTF_SRCS) src/ft_atoi.c src/ft_bzero.c src/ft_calloc.c \
src/ft_isalnum.c src/ft_isalpha.c src/ft_isascii.c src/ft_isdigit.c src/ft_isprint.c \
src/ft_itoa.c src/ft_memchr.c src/ft_memcmp.c src/ft_memcpy.c src/ft_memmove.c \
src/ft_memset.c src/ft_putchar_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c src/ft_putstr_fd.c \
src/ft_split.c src/ft_strchr.c src/ft_strdup.c src/ft_striteri.c src/ft_strjoin.c src/ft_strlcat.c \
src/ft_strlcpy.c src/ft_strlen.c src/ft_strmapi.c src/ft_strncmp.c \
src/ft_strnstr.c src/ft_strrchr.c src/ft_strtrim.c src/ft_substr.c src/ft_tolower.c src/ft_toupper.c \
src/ft_hashmap.c src/ft_hm_node.c src/ft_free.c 

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

CFLAGS = -Wall -Wextra -Werror -Iinclude

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS) $(LIBS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

deb: fclean
	$(CC) $(CFLAGS) -g -fsanitize=address main.c $(NAME) -o test

leaks: fclean
	$(CC) $(CFLAGS) -g main.c $(NAME) -o test

.PHONY: all clean fclean re test