CC = gcc
FILES = main.c \
sorting.c \
delete.c \
flags.c \
file_make_print.c \
path.c \
test_file2.c
NAME = ls
FLAGS = -g -fsanitize=address -Wall -Wextra
NC_LIB_STANDARD = -L $(LIBRARY_PATH)/standard -I $(LIBRARY_PATH)/standard -lstandard
NC_LIB_BUFFER =  -L $(LIBRARY_PATH)/buffers -I $(LIBRARY_PATH)/buffers -lbuffer 
all: $(NAME)

$(NAME): $(FILES)
	$(CC) -g $(FILES) -o $@ $(NC_LIB_STANDARD) $(NC_LIB_BUFFER)

clean:
	rm $(NAME)

re: clean all

