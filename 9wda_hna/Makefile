NAME = minishell

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
LDFLAGS = -lreadline

CC = cc 

SRC = minishell.c libft/ft_atoll.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putstr_fd.c libft/ft_split.c \
        libft/ft_strchr.c libft/ft_strcmp.c libft/ft_strjoin.c libft/ft_strjoinc.c libft/ft_strlen.c libft/ft_itoa.c \
        libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_memset.c builtins/build_cd.c builtins/build_echo.c builtins/build_exit.c \
        builtins/build_export.c builtins/build_pwd.c builtins/build_unset.c builtins/builtins_cd_utils.c builtins/bulild_env.c \
        libft/ft_strdup.c builtins/builtins_export_utils.c parsing/parsing_syn.c parsing/lexer_handel.c parsing/lexer_quotes.c \
		parsing/free_parsing.c parsing/lexer_tools.c parsing/init_parsing.c parsing/lexer.c  \
        parsing/parsing.c parsing/parsing_tools.c exection/redirection.c exection/open_file.c parsing/config_mini.c \
        exection/builtins_utils.c exection/exection_utils.c exection/exection.c exection/exection_algo.c exection/exection_utils1.c \
        exection/exection_utils2.c exection/build_her_doc.c

OBJS = $(SRC:.c=.o)

all: $(NAME)
    
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	echo "\033[1;34mLaunching build... 🚀\033[0m"
	echo "\033[0;32mmake completed successfully! ✅\033[0m"

clean:
	rm -f $(OBJS)
	echo "\033[1;33mCleaning up... 🧹\033[0m"
	echo "\033[0;32mclean completed successfully! ✅\033[0m"

fclean: clean
	rm -f $(NAME)
	echo "\033[1;31mFull clean initiated... 🔥\033[0m"
	echo "\033[0;32mfclean completed successfully! ✅\033[0m"

re: fclean all
	echo "\033[1;35mRebuilding everything... 🔄\033[0m"
	echo "\033[0;32mre completed successfully! ✅\033[0m"

.PHONY: all clean fclean re


.SILENT:
