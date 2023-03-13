NAME		=		cub3D

#######################
#	DIR
#######################

SRC_DIR		=		src/

INC_DIR		=		include/

BUILD_DIR	=		.build/

LIBFT_DIR	=		libft/

MLX_DIR		=		minilibx/

#######################
#	FILES
#######################

LIBFT		=		$(LIBFT_DIR)libft.a

MLX			=		$(MLX_DIR)libmlx_Linux.a

SRC			=		main.c \
					\
						parser/parser.c			\
						parser/parser_utils.c	\
						\
						parser/parse_map_data/parse_wall.c				\
						parser/parse_map_data/parse_map_data.c			\
						parser/parse_map_data/parse_horizontal_plane.c	\
						\
						parser/parse_map/parse_map.c		\
						parser/parse_map/parse_map_utils.c	\
						\
						parser/map_checker/map_checker.c	\
						parser/map_checker/get_spawn.c		\
						\
					\



OBJ			=		$(addprefix $(BUILD_DIR), $(SRC:.c=.o))

DEPS		=		$(addprefix $(BUILD_DIR), $(SRC:.c=.d))

#######################
#	FLAGS
#######################

CFLAGS		=		-Wall -Werror -Wextra -fsanitize=address

IFLAGS		=		-I $(INC_DIR) -I $(LIBFT_DIR)include -I $(MLX_DIR)

LFLAGS		=		-L $(LIBFT_DIR) -lft -lm

MLX_FLAGS	=		-lXext -lX11

DFLAGS		=		-MMD -MP

#######################
#	RULES
#######################

.PHONY:				all
all:				$(NAME)

-include			$(DEPS)

$(NAME):			$(LIBFT) $(OBJ)
					$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $@

$(LIBFT):			FORCE
					$(MAKE) -C $(LIBFT_DIR)

$(MLX):				FORCE
					$(MAKE) -C $(MLX_DIR)

.PHONY:				FORCE
FORCE:

$(BUILD_DIR)%.o:	$(SRC_DIR)%.c
					mkdir -p $(shell dirname $@)
					$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

.PHONY:				clean
clean:
					$(MAKE) clean -C $(LIBFT_DIR)
					$(MAKE) clean -C $(MLX_DIR)
					$(RM) $(OBJ) $(DEPS)

.PHONY:				fclean
fclean:
					$(MAKE) fclean -C $(LIBFT_DIR)
					$(MAKE) clean -C $(MLX_DIR)
					$(RM) $(MLX) $(OBJ) $(DEPS) $(NAME)

.PHONY:				re
re:					fclean
					$(MAKE)
