# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboulif <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/04 23:59:28 by nboulif           #+#    #+#              #
#    Updated: 2019/02/04 23:59:30 by nboulif          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = nboulif.filler

FLAGS = -Wall -Wextra -Werror -O3

LIBFT = libft

DIR_S = srcs

DIR_O = obj

HEADER = includes

SOURCES = filler.c get_next_line.c parse_piece.c parse_map.c solve.c tools.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT)/libft.a -o $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c 
	@mkdir -p $(DIR_O)
	@$(CC) -I $(HEADER) -o $@ -c $<

norme:
	norminette ./libft/
	@echo
	norminette ./$(HEADER)/
	@echo
	norminette ./$(DIR_S)/

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all
