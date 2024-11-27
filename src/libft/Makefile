NAME = libft.a

CFLAGS = -c -Wall -Werror -Wextra -g3

LIB = ar rcs

RM = rm -f

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c\
ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c\
ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c\
ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c\
ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c\
ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
ft_putnbr_fd.c ft_strcmp.c ft_strncpy.c

FT_PRINTF_SRC = ft_printf.c ft_print_char.c ft_print_hex.c ft_print_int.c \
ft_print_ptr.c ft_print_str.c ft_print_uint.c

BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
ft_lstmap.c

OBJ = $(SRC:.c=.o)

FT_PRINTF_OBJ = $(FT_PRINTF_SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME) bonus

%.o:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ) $(FT_PRINTF_OBJ)
	@$(LIB) $(NAME) $(OBJ) $(FT_PRINTF_OBJ)

bonus:	$(BONUS_OBJ)
	@$(LIB) $(NAME) $(BONUS_OBJ)

clean:
	@$(RM) $(OBJ) $(BONUS_OBJ) $(FT_PRINTF_OBJ)

fclean:	clean
	@$(RM) $(NAME) $(OBJ) $(BONUS_OBJ) $(FT_PRINTF_OBJ)

re: fclean all

.PHONY:	all bonus clean fclean re