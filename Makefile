# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 15:12:04 by seunlee2          #+#    #+#              #
#    Updated: 2023/11/17 08:20:52 by seunlee2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = builtin/builtin_center.c \
		builtin/builtin_cd.c \
		builtin/builtin_cd_utils.c \
		builtin/builtin_echo.c \
		builtin/builtin_env.c \
		builtin/builtin_exit.c \
		builtin/builtin_pwd.c \
		builtin/builtin_export.c \
		builtin/builtin_unset.c \
		check/check.c \
		check/check_validation.c \
		exec/chk_r_redir.c \
		exec/chk_l_redir.c \
		exec/exec_nopipe.c \
		exec/exec_util.c \
		exec/exec.c \
		exec/fork.c \
		exec/set_in_out.c \
		main/do_readline.c \
		main/init.c \
		main/minishell.c \
		parse/check_parse_error.c \
		parse/cmd_list_function.c \
		parse/get_cmd_list.c \
		parse/list_function.c \
		parse/parse.c \
		parse/get_chunk_index.c \
		parse/parse_util.c \
		parse/merge_norm.c \
		parse/token_error.c \
		signal/process_signal.c \
		util/error.c \
		util/free.c \
		util/free2.c \
		util/ft_newjoin.c \
		util/slushjoin.c \
		util/util.c \
		util/util2.c \
		util/get_last.c \
		util/atoi_flag.c \

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
LIBFT = libft
LIBFT_LIB = -L./libft -lft
INCLUDES = -I./include -I./libft/include
READLINE_LIB 	= -lreadline
READLINE_INC	= -I/opt/homebrew/opt/readline/includeclear

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -o $@ -c $<

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_LIB) $(READLINE_LIB)

all: $(NAME)
clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE)

.PHONY: all clean fclean re
