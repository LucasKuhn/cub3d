NAME		=	cub3D
MLXFLAGS	=	-lmlx -Ilmlx -lXext -lX11
SRCS		=	main.c
OBJ_DIR		=	obj
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
LIBFT		=	libft/libft.a
LIBFT_FLAGS	=	-L./libft -lft
ifeq ($(shell uname),Darwin) # MacOS
	MLXFLAGS	+=	-framework OpenGL -framework AppKit
endif

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(MLXFLAGS) $(LIBFT_FLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p obj

$(LIBFT):
	make --directory=libft

clean:
	@rm -rf obj
	@echo "cleaning .o files"

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean
