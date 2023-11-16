FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
NAME = pathfinder

.PHONY: all clean uninstall reinstall

all: $(NAME)

$(NAME):
	make -C libmx
	clang $(FLAGS) src/*.c -c
	mkdir obj
	mv *.o obj
	clang $(FLAGS) obj/*.o libmx/libmx.a -o $(NAME)

clean:
	rm -rf libmx/obj
	rm -rf obj

uninstall: clean
	rm -rf libmx/libmx.a
	rm -rf $(NAME)

reinstall: uninstall all
