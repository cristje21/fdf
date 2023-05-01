NAME		=		fdf
SRC			=		fdf_main.c \
					put_line.c \
					parse_map.c \
					fdf_atoi.c \
					misc_utils.c \
					key_functions.c

LIBFT		=		libft/libft.a
OBJ_F		=		$(SRC:%.c=obj/%.o)
FLAGS		=		-Wall -Werror -Wextra
MLX_FLAGS	=		-framework Cocoa -framework OpenGL -framework IOKit -lglfw3
MLX_LIB		=		MLX42/build/libmlx42.a
HEADER		=		-I MLX42/include/MLX42 -I include
FSAN		=		-g -fsanitize=address

all : $(NAME)

mlx :
	cmake -S MLX42 -B MLX42/build
	make -C MLX42/build -j4

$(NAME) : $(OBJ_F)
	make -C libft
	$(CC) $(FSAN) $(FLAGS) -o $@ $^ $(MLX_LIB) $(MLX_FLAGS) $(LIBFT)
	echo "executable ready"

obj/%.o : src/%.c
	mkdir -p obj
	$(CC) $(FLAGS) $(HEADER) -o $@ -c $^

clean :
	@rm -rf obj

fclean : clean
	@make -C libft fclean
	@rm -rf MLX42/build
	@rm -f $(NAME)

re : fclean all