SRC =		src/parseur/get_ellement_json.c 			\
			src/parseur/string_json.c 					\
			src/parseur/first_fonc.c 					\
			src/parseur/error/my_error.c 				\
			src/parseur/fill_buffer_from_file.c			\
			src/print_struct/print_json.c 				\
			src/get_data/find_data.c 					\
			src/free_struct/free_json.c

OBJ = 		$(SRC:.c=.o)

NAME =		libmy_json.a

CFLAGS = 	-I include/

all:		$(NAME)

$(NAME):	$(OBJ)
	ar rc libmy_json.a $(NAME) $(OBJ)

clean :
	rm -f $(OBJ) *~
	rm -f *.o *.a *~

fclean : clean