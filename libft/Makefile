# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 14:38:11 by edelage           #+#    #+#              #
#    Updated: 2022/12/20 17:28:17 by edelage          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ***************************
#  Folders
# ***************************

INC_DIR =			include/

SRC_DIR =			srcs/

BUILD_DIR =			.build/

DIR =				fd \
					char \
					list \
					stdout \
					memory \
					string \
					convert \
					get_next_line \


# ***************************
#  Files
# ***************************

CHAR =				ft_isalpha.c \
					ft_isdigit.c \
					ft_isalnum.c \
					ft_isascii.c \
					ft_isspace.c \
					ft_isprint.c \
					ft_issign.c \
					ft_isspace.c \
					ft_toupper.c \
					ft_tolower.c \

CONVERT =			ft_atoi.c \
					ft_atoll.c \
					ft_itoa.c \

FD =				ft_putchar_fd.c \
					ft_putstr_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \

GNL =				get_next_line.c \
					get_next_line_utils.c \

STDOUT =			ft_putchar.c \
					ft_putstr.c \
					ft_putendl.c \
					ft_putnbr.c \

LST =				ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstadd_back.c \
					ft_lstdelone.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c \

MEMORY =			ft_bzero.c \
					ft_memset.c \
					ft_memchr.c \
					ft_memcpy.c \
					ft_memcmp.c \
					ft_calloc.c \
					ft_memmove.c \
					free_string_array.c \

STRING =			ft_split.c \
					ft_strlen.c \
					ft_strchr.c \
					ft_strcmp.c \
					ft_strdup.c \
					ft_strcpy.c \
					ft_substr.c \
					ft_strlcpy.c \
					ft_strlcat.c \
					ft_strrchr.c \
					ft_strncmp.c \
					ft_strnstr.c \
					ft_strjoin.c \
					ft_strtrim.c \
					ft_strmapi.c \
					ft_strncpy.c \
					ft_striteri.c \

SRCS =				$(addprefix fd/, $(FD)) \
					$(addprefix list/, $(LST)) \
					$(addprefix char/, $(CHAR)) \
					$(addprefix stdout/, $(STDOUT)) \
					$(addprefix string/, $(STRING)) \
					$(addprefix memory/, $(MEMORY)) \
					$(addprefix convert/, $(CONVERT)) \
					$(addprefix get_next_line/, $(GNL)) \

HEADER =			$(INC_DIR)libft.h \
					$(INC_DIR)get_next_line.h \

OBJS =				$(addprefix $(BUILD_DIR), $(SRCS:.c=.o))

DEPS =				$(OBJS:.o=.d)

NAME =				libft.a


# ***************************
# Compilation
# ***************************

FLAGS =				-Wall -Wextra -Werror

DEPS_FLAGS =		-MMD -MP


# ***************************
# Commands
# ***************************

AR_FLAGS =			rcs

MKDIR =				mkdir -p


# ***************************
# Rules
# ***************************

all:				$(NAME)

$(NAME):			$(BUILD_DIR) $(OBJS)
					$(AR) $(AR_FLAGS) $@ $(OBJS)

-include			$(DEPS)

$(BUILD_DIR)%.o:	$(SRC_DIR)%.c $(HEADER) Makefile
					$(CC) $(FLAGS) $(DEPS_FLAGS) -I $(INC_DIR) -c $< -o $@

$(BUILD_DIR):
					$(MKDIR) $(addprefix $(BUILD_DIR), $(DIR))

clean:
					$(RM) $(OBJS)

fclean:				clean
					$(RM) $(NAME)

re:					fclean
					$(MAKE) all

.PHONY:				all clean fclean re
