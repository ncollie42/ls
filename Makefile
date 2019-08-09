CC = gcc
FILES = main.c
NAME = ls
FLAGS = 
NC_LIB_STANDARD = -L $(LIBRARY_PATH)/standard -I $(LIBRARY_PATH)/standard -lstandard
NC_LIB_BUFFER =  -L $(LIBRARY_PATH)/buffers -I $(LIBRARY_PATH)/buffers -lbuffer 
all: $(NAME)

$(NAME): $(FILES)
	$(CC) $(FLAGS) $(FILES) -o $@ $(NC_LIB_STANDARD) $(NC_LIB_BUFFER)

clean:
	rm $(NAME)

re: clean all

