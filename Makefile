NAME    = libasm.a

SRCS    = $(wildcard *.s)
OBJS    = $(SRCS:.s=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.s
	nasm  -f elf64 $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) test

re: fclean all

.PHONY: all clean fclean re test

test: $(NAME)
	cc main.c $(NAME) -o test && ./test



# ar rcs = making .a from .o
# r = insert .o in .a
# c = create archive if doesnt
# s = symbolindex

# ar -f elf64
# -f = format			elf64 = linux ex 64 bits
