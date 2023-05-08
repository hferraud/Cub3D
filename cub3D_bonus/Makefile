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
							server/thread/initialization/thread_init.c		\
							server/thread/initialization/server_data_init.c	\
							server/thread/initialization/enemies_init.c		\
							server/thread/initialization/mutexes_init.c		\
							\
							server/thread/destroy/server_data_destroy.c	\
							\
								server/thread/routines/connection_routine/connection_routine.c	\
								server/thread/routines/connection_routine/map_send.c			\
								server/thread/routines/connection_routine/asset_send.c			\
								server/thread/routines/connection_routine/file_send.c			\
								server/thread/routines/connection_routine/connection_error.c	\
								server/thread/routines/connection_routine/client_delete.c		\
								\
								server/thread/routines/in_game_routine/in_game_routine.c	\
								server/thread/routines/in_game_routine/listening_request.c	\
								server/thread/routines/in_game_routine/event_router.c		\
								server/thread/routines/in_game_routine/send_request.c		\
								server/thread/routines/in_game_routine/event_request.c		\
								server/thread/routines/in_game_routine/disconnect_client.c	\
							\
					\
							server/socket/socket_init.c		\
							server/socket/client_accept.c	\
					\
							utils/collectible.c			\
							utils/socket/port_get.c		\
					\

SRC_CLIENT	=		error.c	\
					\
						client/client.c	\
					\
						client/socket/socket_init.c	\
					\
						client/parser/parser.c		\
						client/parser/map_parse.c	\
						client/parser/file_parse.c	\
						client/parser/map_clear.c	\
						\
						client/parser/collectible/collectible.c			\
						client/parser/collectible/collectible_list.c	\
						client/parser/collectible/collectible_parse.c	\
					\
						utils/socket/port_get.c	\
					\
						client/player/player_pos_init.c			\
						client/player/player_movement.c			\
						client/player/player_door_interact.c	\
						client/player/position_utils.c			\
						client/player/collectible_dist.c		\
						client/player/player_hit_collectible.c	\
					\
						client/mlx_handler/initialization/mlx_data_init.c	\
						client/mlx_handler/initialization/mlx_sprite_init.c	\
						\
						client/mlx_handler/destroy/mlx_data_destroy.c		\
						client/mlx_handler/destroy/mlx_sprite_destroy.c	\
						\
						client/mlx_handler/hook/init_hook.c		\
						client/mlx_handler/hook/key_press.c		\
						client/mlx_handler/hook/key_release.c	\
						client/mlx_handler/hook/cub_exit.c		\
						\
					\
						client/event/add_event.c	\
						client/event/event_new.c	\
					\
						client/display/render_frame.c	\
						\
						client/display/vector/vector.c	\
						client/display/vector/fvector.c	\
						client/display/vector/matrix.c	\
						\
						client/display/draw/mlx_put_pixel.c		\
						client/display/draw/draw_line.c			\
						client/display/draw/draw_rectangle.c	\
						client/display/draw/draw_background.c	\
						client/display/draw/draw_wall.c			\
						client/display/draw/draw_player_view.c	\
						client/display/draw/draw_collectible.c	\
						client/display/draw/draw_enemy.c		\
						client/display/draw/draw_sprite.c		\
						client/display/draw/draw_shape_utils.c	\
						\
						client/display/draw/hud/draw_minimap.c	\
						client/display/draw/hud/draw_minimap_pixel.c	\
						client/display/draw/hud/draw_health_bar.c	\
						\
						client/display/raycasting/raycasting.c	\
						\
						client/thread/initialization/player_data_init.c	\
						client/thread/initialization/thread_init.c		\
						\
						client/thread/destroy/player_data_destroy.c	\
						\
						client/thread/routine/routine.c						\
						client/thread/routine/listening_response.c			\
						client/thread/routine/send_event.c					\
						client/thread/routine/take_collectible.c			\
						client/thread/routine/send_response.c				\
						client/thread/routine/event_response.c				\
						\
					\
					utils/collectible.c	\
					\

OBJ_SERVER	=		$(addprefix $(BUILD_DIR), $(SRC_SERVER:.c=.o))

OBJ_CLIENT	=		$(addprefix $(BUILD_DIR), $(SRC_CLIENT:.c=.o))

DEPS		=		$(addprefix $(BUILD_DIR), $(SRC_SERVER:.c=.d))	\
					$(addprefix $(BUILD_DIR), $(SRC_CLIENT:.c=.d))	\

#######################
#	FLAGS
#######################

CFLAGS		=		-Wall -Werror -Wextra -g3

IFLAGS		=		-I $(INC_DIR) -I $(LIBFT_DIR)include -I $(MLX_DIR)

LFLAGS		=		-L $(LIBFT_DIR) -lft -lm -lpthread

MLX_FLAGS	=		-L $(MLX_DIR) -lmlx -lXext -lX11

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

$(SERVER):			$(LIBFT) $(OBJ_SERVER)
					$(CC) $(CFLAGS) $(OBJ_SERVER) $(LFLAGS) -o $@

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
