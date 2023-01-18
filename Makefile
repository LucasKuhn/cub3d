NAME		=	cub3D
MLXFLAGS	=	-lmlx -Ilmlx -lXext -lX11
# CFLAGS		=	-g -fsanitize=address
SRC_DIR		=	src
SRCS		=	$(addprefix $(SRC_DIR)/, get_map_error.c main.c \
				valid_extension.c draw_minimap.c keycode_helpers.c \
				movement_utils.c find_player.c load_map.c utils.c\
				render_screen.c cast_rays.c draw_utils.c surrounded_by_walls.c)

OBJ_DIR		=	obj
OBJS		=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT		=	libft/libft.a
LIBFT_FLAGS	=	-L./libft -lft

ifeq ($(shell uname),Darwin) # MacOS
	MLXFLAGS	+=	-framework OpenGL -framework AppKit
endif

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) -g $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIBFT_FLAGS) -lm -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -g $(CFLAGS) -c $< -o $@ -I ./

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
