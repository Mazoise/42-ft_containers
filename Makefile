# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/03 18:59:18 by mchardin          #+#    #+#              #
#    Updated: 2021/10/08 16:18:20 by mchardin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PREFIX				=	./tests/

SRCS				=	$(addprefix $(PREFIX), \
										vector_tests.cpp \
										stack_tests.cpp \
										main.cpp \
										)

OBJS				=	${SRCS:.cpp=.o}

DEPS				=	${OBJS:.o=.d}

CXX					=	clang++

CXXFLAGS			=	-Werror -Wextra -Wall -std=c++98  -D FT -MMD -I $(PREFIX)

CXXFLAGS_STD		=	-Werror -Wextra -Wall -std=c++98 -MMD -I $(PREFIX)

NAME 				=	ft_containers

STD_NAME			=	std_containers

RM					=	rm -f

all:
					${MAKE} ${NAME}

${NAME}:			${OBJS}
					${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

${STD_NAME}:		${OBJS}
					${CXX} ${CXXFLAGS_STD} ${OBJS} -o ${STD_NAME}

run:				all
					./$(NAME)

clean:		
					${RM} ${OBJS}
					${RM} ${DEPS}

fclean:		
					${RM} ${OBJS}
					${RM} ${DEPS}
					${RM} ${NAME}
					${RM} ${STD_NAME}

re:					fclean all

.PHONY: 			all re run clean fclean

-include			${DEPS}