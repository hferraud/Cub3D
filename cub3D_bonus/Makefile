SERVER		=		cub3D_server

CLIENT		=		cub3D

#######################
#	DIR
#######################

SRC_DIR		=		src/

INC_DIR		=		include/

BUILD_DIR	=		.build/

LIBFT_DIR	=		../libft/

MLX_DIR		=		../minilibx/

#######################
#	FILES
#######################

LIBFT		=		$(LIBFT_DIR)libft.a

MLX			=		$(MLX_DIR)libmlx_Linux.a

SRC_SERVER	=		error.c	\
					\
						server/server.c	\
					\
							server/parser/parser.c			\
							server/parser/parser_utils.c	\
							\
							server/parser/parse_map_data/parse_path.c		\
							server/parser/parse_map_data/parse_map_data.c	\
							\
							server/parser/parse_map/parse_map.c			\
							server/parser/parse_map/parse_map_utils.c	\
							\
							server/parser/map_checker/map_checker.c	\
							server/parser/map_checker/map_error.c	\
							server/parser/map_checker/get_spawn.c	\
							\
					\
							server/socket/socket_init.c		\
							server/socket/client_accept.c	\
					\
							utils/socket/port_get.c	\
					\

SRC_CLIENT	=		error.c	\
					\
						client/client.c	\
					\
						client/socket/socket_init.c	\
					\
						utils/socket/port_get.c	\
					\

OBJ_SERVER	=		$(addprefix $(BUILD_DIR), $(SRC_SERVER:.c=.o))

OBJ_CLIENT	=		$(addprefix $(BUILD_DIR), $(SRC_CLIENT:.c=.o))

DEPS		=		$(addprefix $(BUILD_DIR), $(SRC_SERVER:.c=.d))	\
					$(addprefix $(BUILD_DIR), $(SRC_CLIENT:.c=.d))	\

#######################
#	FLAGS
#######################

CFLAGS		=		-Wall -Werror -Wextra #-fsanitize=address

IFLAGS		=		-I $(INC_DIR) -I $(LIBFT_DIR)include -I $(MLX_DIR)

LFLAGS		=		-L $(LIBFT_DIR) -lft -L $(MLX_DIR) -lmlx -lm

MLX_FLAGS	=		-lXext -lX11

DFLAGS		=		-MMD -MP

#######################
#	RULES
#######################

############
#	GENERAL
############

.PHONY:				all
all:				$(SERVER) $(CLIENT)

.PHONY:				server
server:				$(SERVER)

.PHONY:				client
client:				$(CLIENT)

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

$(SERVER):			$(LIBFT) $(MLX) $(OBJ_SERVER)
					$(CC) $(CFLAGS) $(OBJ_SERVER) $(LFLAGS) $(MLX_FLAGS) -o $@

$(CLIENT):			$(LIBFT) $(MLX) $(OBJ_CLIENT)
					$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LFLAGS) $(MLX_FLAGS) -o $@

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
