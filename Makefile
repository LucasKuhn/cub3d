NAME		=	cub3D
MLXFLAGS	=	-lmlx -Ilmlx -lXext -lX11
# CFLAGS		=	-fsanitize=address 
SRCS		=	get_map_error.c   main.c            valid_extension.c \
draw_minimap.c    keycode_helpers.c movement_utils.c \
find_player.c     load_map.c        utils.c render_screen.c cast_rays.c draw_utils.c
OBJ_DIR		=	obj
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
LIBFT		=	libft/libft.a
LIBFT_FLAGS	=	-L./libft -lft
ifeq ($(shell uname),Darwin) # MacOS
	MLXFLAGS	+=	-framework OpenGL -framework AppKit
endif

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) -g $(CFLAGS) -c $< -o $@ -I ./

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) -g $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIBFT_FLAGS) -lm -o $(NAME)

$(OBJ_DIR):
	mkdir -p obj

$(LIBFT):
	make --directory=libft

clean:
	@rm -rf obj
	@echo "cleaning .o files"
	make fclean -C libft

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean
