NAME		=	cub3D
MLXFLAGS	=	-lmlx -Ilmlx -lXext -lX11
SRCS		=	main.c
OBJ_DIR		=	obj
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
ifeq ($(shell uname),Darwin) # MacOS
	MLXFLAGS	+=	-framework OpenGL -framework AppKit
endif

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@ -I ./

$(NAME):  $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) $(MLXFLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p obj

clean:
	@rm -rf obj
	@echo "cleaning .o files"

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean
