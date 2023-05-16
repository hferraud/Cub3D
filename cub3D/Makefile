UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	FLAGS_MLX	=	-lXext -lX11
	MLX_DIR		=	minilibx/linux/
endif
ifeq ($(UNAME_S), Darwin)
	FLAGS_MLX	=	-framework OpenGL -framework Appkit
	MLX_DIR		=	minilibx/macos/
endif

NAME		=		cub3D

SERVER		=		cub3D_server

CLIENT		=		cub3D_client

#######################
#	DIR
#######################

SRC_DIR		=		src/

INC_DIR		=		include/

BUILD_DIR	=		.build/

LIBFT_DIR	=		../libft/

ifeq ($(UNAME_S), Linux)
	MLX_DIR		=	../minilibx/linux/
endif
ifeq ($(UNAME_S), Darwin)
	MLX_DIR		=	../minilibx/macos/
endif

#######################
#	FILES
#######################

LIBFT		=		$(LIBFT_DIR)libft.a

MLX			=		$(MLX_DIR)libmlx_Linux.a

SRC			=		main.c	\
					error.c	\
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
						mlx_handler/initialization/mlx_data_init.c		\
						mlx_handler/initialization/wall_sprite_init.c	\
						\
						mlx_handler/destroy/mlx_data_destroy.c		\
						mlx_handler/destroy/wall_sprite_destroy.c	\
						\
						mlx_handler/hook/init_hook.c	\
						mlx_handler/hook/key_press.c	\
						mlx_handler/hook/key_release.c	\
						mlx_handler/hook/cub_exit.c		\
						\
					\
						display/render_frame.c	\
						\
						display/vector/vector.c	\
						display/vector/fvector.c	\
						display/vector/matrix.c	\
						\
						display/draw_shape/mlx_put_pixel.c		\
						display/draw_shape/draw_line.c			\
						display/draw_shape/draw_rectangle.c		\
						display/draw_shape/draw_background.c	\
						display/draw_shape/draw_wall.c			\
						display/draw_shape/draw_player_view.c	\
						display/draw_shape/draw_shape_utils.c	\
						\
						display/player/player_pos_init.c	\
						display/player/player_movement.c	\
						\
						display/raycasting/raycasting.c	\
						\
					\

OBJ			=		$(addprefix $(BUILD_DIR), $(SRC:.c=.o))

DEPS		=		$(addprefix $(BUILD_DIR), $(SRC:.c=.d))

#######################
#	FLAGS
#######################

CFLAGS		=		-Wall -Werror -Wextra -g3

IFLAGS		=		-I $(INC_DIR) -I $(LIBFT_DIR)include -I $(MLX_DIR)

LFLAGS		=		-L $(LIBFT_DIR) -lft -L $(MLX_DIR) -lmlx -lm

ifeq ($(UNAME_S), Linux)
	MLX_FLAGS	=	-lXext -lX11
endif
ifeq ($(UNAME_S), Darwin)
	MLX_FLAGS	=	-framework OpenGL -framework Appkit
endif

DFLAGS		=		-MMD -MP

#######################
#	RULES
#######################

############
#	GENERAL
############

.PHONY:				all
all:				$(NAME)

.PHONY:				clean
clean:
					$(MAKE) clean -C $(LIBFT_DIR)
					$(MAKE) clean -C $(MLX_DIR)
					$(RM) $(MLX) $(OBJ) $(OBJ_SERVER) $(OBJ_CLIENT) $(DEPS)

.PHONY:				fclean
fclean:
					$(MAKE) fclean -C $(LIBFT_DIR)
					$(MAKE) clean -C $(MLX_DIR)
					$(RM) $(MLX) $(OBJ) $(OBJ_SERVER) $(OBJ_CLIENT) $(DEPS) $(NAME) $(SERVER) $(CLIENT)

.PHONY:				re
re:					fclean
					$(MAKE)

################
#	EXECUTABLES
################

-include			$(DEPS)

$(NAME):			$(LIBFT) $(MLX) $(OBJ)
					$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) $(MLX_FLAGS) -o $@

##################
#	OBJECTS FILES
##################

$(BUILD_DIR)%.o:	$(SRC_DIR)%.c
					mkdir -p $(shell dirname $@)
					$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

############
#	LIBRARY
############

$(LIBFT):			FORCE
					$(MAKE) -C $(LIBFT_DIR)

$(MLX):				FORCE
					$(MAKE) -C $(MLX_DIR)

.PHONY:				FORCE
FORCE:
