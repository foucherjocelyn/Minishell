CFLAGS	?= -Wall -Werror -Wextra
LDFLAGS	?=
OBJS	= ft_atoi.o ft_bzero.o ft_calloc.o ft_isalnum.o ft_isalpha.o      \
		  ft_isascii.o ft_isdigit.o ft_isprint.o ft_memchr.o ft_memcmp.o  \
		  ft_memcpy.o ft_memmove.o ft_memset.o ft_strchr.o ft_strdup.o    \
		  ft_strlcat.o ft_strlcpy.o ft_strlen.o ft_strncmp.o ft_strnstr.o \
		  ft_strrchr.o ft_tolower.o ft_toupper.o ft_substr.o ft_strjoin.o \
		  ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o \
		  ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o \
		  ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o \
		  ft_lstadd_back.o ft_lstdelone.o ft_lstclear.o ft_lstiter.o \
		  ft_lstmap.o ft_veccreate.o ft_vecdestroy.o ft_vecset.o ft_vecadd.o \
		  ft_vecget.o ft_vecremove.o ft_vecinsert.o ft_strcmp.o \
		  ft_isstrdigit.o

NAME		= libft.a

all:	$(NAME)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME):	$(OBJS)
	ar -rcs $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
