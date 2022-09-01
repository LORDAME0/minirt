# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 17:52:43 by orahmoun          #+#    #+#              #
#    Updated: 2022/08/22 21:56:40 by orahmoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- VARIABLE DECLARATION --- #

NAME				=	minirt

CC					=	cc

FLAGS				=	-Wall -Wextra -I libft -I includes

MLX_FLAGS		=	-lmlx -framework OpenGL -framework AppKit

HEADER			=	includes/main.h includes/parsing.h includes/linear_algebra.h libft/libft.h

LIBFT 			=	libft/libft.a

MAKE_LIBFT 	=	libft/

SRC 				=	srcs/rt/camera.c \
						srcs/rt/cone.c \
						srcs/rt/plane.c \
						srcs/rt/prof.c \
						srcs/rt/ray.c \
						srcs/rt/ray2.c \
						srcs/rt/render.c \
						srcs/rt/rgb.c \
						srcs/rt/rgb2.c \
						srcs/rt/shading.c \
						srcs/rt/sphere.c \
						srcs/rt/world.c \
    					srcs/rt/bm_utils.c \
    					srcs/rt/bm_sphere.c \
    					srcs/rt/uv.c \
    					srcs/rt/checkerboard.c \
						srcs/rt/cylinder.c \
						srcs/rt/discriminant.c \
						srcs/rt/intersection.c \
						srcs/rt/light.c \
						srcs/rt/utils.c \
						srcs/rt/event.c \
						srcs/parsing/parsing.c \
						srcs/parsing/parsing2.c \
						srcs/parsing/parsing3.c \
						srcs/parsing/parsing4.c \
						srcs/parsing/parsing5.c \
						srcs/parsing/parsing6.c \
						srcs/parsing/parsing7.c \
						srcs/parsing/parsing8.c \
						srcs/parsing/parsing9.c \
						srcs/parsing/parsing10.c \
						srcs/parsing/parsing11.c \
						srcs/linear_algebra/transform.c \
						srcs/linear_algebra/transform2.c \
						srcs/linear_algebra/vector.c \
						srcs/linear_algebra/vector2.c \
						srcs/linear_algebra/vector3.c \
						srcs/linear_algebra/vector4.c \
						srcs/linear_algebra/matrix.c \
						srcs/linear_algebra/matrix2.c \
						srcs/linear_algebra/matrix3.c \
						srcs/linear_algebra/matrix4.c \
						srcs/mlx/mlx.c \
						srcs/mlx/mlx2.c \
						srcs/mlx/mlx3.c \
						srcs/mlx/mlx4.c \
						main.c

OBJDIR 			=	obj

OBJ 				=	$(addprefix ${OBJDIR}/, ${SRC:%.c=%.o})

# ---------------------------- #
	
# RULES

all	: ${NAME} 

${LIBFT} :
	@echo "${YEL}MAKING LIBFT ...${NC}"
	@make -C ${MAKE_LIBFT}

${NAME} : ${OBJ} ${LIBFT}
	@echo "${YEL}LINKING PROCESS ...${NC}"
	@echo "${GRN}COMPILATION COMPLETE${NC}"
	@${CC} ${MLX_FLAGS} $^  -o ${NAME}

$(OBJDIR)/%.o : %.c ${HEADER}
	@mkdir -p $(dir $@)
	@${CC} ${FLAGS} -c $< -o $@
	@echo "${BLU}MAKING ::	$@${NC}"

clean : 
	@rm -rf ${OBJDIR}
	@make clean -C ${MAKE_LIBFT}

fclean : clean
	@rm -f ${NAME}
	@make fclean -C ${MAKE_LIBFT}

re : fclean all

.PHONY : bonus clean fclean all

# ---------------------------- #

# --- Terminal Color Codes --- #

NC		:= \033[31;0m
RED 	:= \033[0;31;1m
YEL 	:= \033[0;33;1m
GRA		:= \033[0;37;1m
CYN 	:= \033[0;36;1m
GRN 	:= \033[0;32;1m
MGN		:= \033[0;35;1m
BLU 	:= \033[0;34;1m

# ---------------------------- #
