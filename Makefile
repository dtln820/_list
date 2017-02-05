CC = gcc
CFLAGS =
NAME = ft_ls

$(NAME): ft_ls.o ft_string.o ft_print.o info.o sort.o
	$(CC) $(CFLAGS) ft_ls.o ft_string.o ft_print.o info.o sort.o -o ft_ls

all: $(NAME)

ft_ls.o: ft_ls.c list.h
	$(CC) $(CFLAGS) -c ft_ls.c -o ft_ls.o

ft_string.o: ft_string.c list.h
	$(CC) $(CFLAGS) -c ft_string.c -o ft_string.o

ft_print.o: ft_print.c list.h
	$(CC) $(CFLAGS) -c ft_print.c -o ft_print.o

info.o: info.c list.h
	$(CC) $(CFLAGS) -c info.c -o info.o

sort.o: sort.c list.h
	$(CC) $(CFLAGS) -c sort.c -o sort.o

clean:
	rm -f ft_ls.o ft_string.o ft_print.o info.o sort.o

fclean: clean
	rm -f $(NAME)

re: fclean all
