NAME		=		fdf
SRC			=		fdf_main.c \
					put_line.c
LIBFT		=		libft/libft.a
OBJ_F		=		$(SRC:%.c=obj/%.o)
FLAGS		=		-Wall -Werror -Wextra
MLX_FLAGS	=		-framework Cocoa -framework OpenGL -framework IOKit -lglfw3
MLX_LIB		=		MLX42/build/libmlx42.a
HEADER		=		-I MLX42/include/MLX42 -I include

all : $(NAME)

mlx :
	cmake -S MLX42 -B MLX42/build
	make -C MLX42/build -j4

$(NAME) : $(OBJ_F)
	make -C libft
	$(CC) $(FLAGS) -o $@ $^ $(MLX_LIB) $(MLX_FLAGS) $(LIBFT)
	echo "executable ready"

obj/%.o : src/%.c
	mkdir -p obj
	$(CC) $(FLAGS) $(HEADER) -o $@ -c $^

clean :
	@make -C libft clean
	@rm -rf obj

fclean : clean
	@make -C libft fclean
	@rm -rf MLX42/build
	@rm -f $(NAME)

re : fclean all