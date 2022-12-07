# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rubennijhuis <rubennijhuis@student.coda      +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/02 20:54:00 by rubennijhui   #+#    #+#                  #
#    Updated: 2022/07/24 20:16:32 by rubennijhui   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#======= General =======#
CC			=	g++

SRC_DIR		=	src
OBJS_DIR	=	objs
BIN_DIR		=	bin
INCLUDE_DIR	=	include
EXEC_NAME	=	webserv
NAME		=	$(BIN_DIR)/$(EXEC_NAME)
OUTPUT		=	$(BIN_DIR)/$(EXEC_NAME)

#======== SRCS =========#

INC			= 	-I $(INCLUDE_DIR)

SRCS		=	serverConfig.cpp \
				main.cpp \
				server.cpp \
				parseUtils.cpp \

OBJS		=	$(addprefix $(OBJS_DIR)/,$(SRCS:.cpp=.o))

#== Compilation stuff ==#

CFLAGS		=	-Wall -Wextra -Werror $(INC)

#======= Rules =========#

objs/%.o:src/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^
	@echo "🔨 Compiling: $^"
	
all: $(NAME)

$(NAME):$(OBJS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(OBJS) -o $(OUTPUT)
	@echo "Finished building: $@"

run: $(NAME)
	./$(OUTPUT)

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: run all clean fclean re