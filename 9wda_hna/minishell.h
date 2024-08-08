/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:03:14 by yozainan         #+#    #+#             */
/*   Updated: 2024/07/24 13:57:50 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <linux/limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

#define PWD_ERROR_MSG "minishell: pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory"

typedef struct s_env_node
{
    char *name;
    char *value;
    struct s_env_node *next;
} t_env_node;

/**************************************parsing*********************/

#define MAX_TOKENS 100000

typedef enum
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_OR,
    TOKEN_HASHTAG,
    NOT_DEFINE,
    TOKEN_AMBIGUOUS,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_APPEND_OUT,
    TOKEN_HERE_DOC,
    TOKEN_HERE_DOC_NO,
    TOKEN_BACKGROUND,
    TOKEN_AND,
    TOKEN_LPR,
    TOKEN_RPR,
    TOKEN_DQUOTE,
    TOKEN_SQUOTE,
    TOKEN_END
} TokenType;

typedef struct
{
    TokenType type;
    char *value;
} Token;

typedef struct Redirection
{
    TokenType type;
    char *filename;
    struct Redirection *next;
} Redirection;

typedef struct s_cmd
{
    char *value;
    struct s_cmd *next;
}   t_cmd;

typedef struct Command
{
    TokenType type;
    Redirection *redirection; // Output redirection
    Redirection *heredoc;     // Here-doc redirection
    //char **argv;              // Arguments array
    t_cmd *cmd_lst;
    char **av;
    int fdin;                 //
    int fdout;                //
    int redir_erros;            //
    int dup;                  //
    struct Command *next;     // Pointer to next command
} Command;

typedef struct s_data
{
    t_env_node *env_list;
    Command *cmd;
    pid_t pid;
    char **env;
    char **av;
    int ac;
    int fd[2];
    int size_cmds;
    int exit_status;
    int is_pipeline;
	int her_erros;
} t_data;

extern t_data g_data;

typedef struct s_value
{
    int i;
    int flag;
}   t_value;

typedef struct
{
    int in_quotes;
    char quote_char;
    char buffer[100001];
    bool status;
    const char *start;
    int expandit;
    int double_quotes;
    int flag;
    int quote;
    char *expanded_value;
    int buffer_index;
    t_env_node *env;
} QuoteWordParserState;

/************************************************************/

size_t ft_lst_size(t_cmd *cmd);
char **ft_list_to_char(t_cmd *cmmd,int size);
void	add_cmd(t_cmd **head,t_cmd *cmmd);
QuoteWordParserState init_lexer(t_env_node *env);
void handle_special_characters(const char **p, Token *tokens,
							   int *num_tokens);
void handel_q(const char **p, TokenType type, Token *tokens, int *num_tokens);
void doc_or_in(const char **p, TokenType *type, char *special);
int check_here_doc_expand(const char **p);
int splited(Token *tokens, int *num_tokens,
		   QuoteWordParserState *state);
int add_to(const char **p, Token *tokens, int *num_tokens,
		   QuoteWordParserState *state);
void handle_quotes_and_words(const char **p, Token *tokens, int *num_tokens,
							 QuoteWordParserState *state);
void hanv3(const char **p, char *special, TokenType *type);
void handle_v2(const char **p, char *special, TokenType *type);
int handel_dollar_expand(const char **p, QuoteWordParserState *state);
int dollar(const char **p, QuoteWordParserState *state);
int handel_quotes(const char **p, QuoteWordParserState *state);
int check_space(char *s);
void ft_buffer_split(Token *tokens, int *nb, const char *str);
int end_dollar(const char **p, QuoteWordParserState *state);
int check_ambiguous(Token *tokens, int *num_tokens, QuoteWordParserState *state);
char *alloc_token(const char *s, int *r, int i);
void handle_quotes_and_wordsv2(const char **p, QuoteWordParserState **state);
int is_ambiguous(const char *expanded_value);
void	process_token(Token *tokens, t_value *value, Command **current,
Command **head,t_cmd **cmd_head);
int is_token(const char *p);

/*************************************************************/
bool	is_token_invalid(Token *tokens, int i, int nb_tokens);
bool	is_double_token_error(Token *tokens, int i);
bool	is_initial_token_error(Token *tokens, int i);
bool	is_final_token_error(Token *tokens, int i, int nb_tokens);
bool	is_invalid_sequence(Token *tokens, int i);
bool	is_redirection(Token token);
void	process_operator(Token *tokens, int *i, Command **current,Command **head,t_cmd **cmd_head);
bool	is_parenthesis(Token *tokens, int i);
void	handle_syntax_error(void);
void ft_reset_file(Command *cmd);
/********************Dubag************************************/
void print_command_structure(Command *cmd) ;
/************************************************************/

void handle_word(Token *tokens, int *i, Command **current);
void add_command_to_list(Command **head, Command *current);
Command *create_command();
void init_command(Command *cmd);
Command	*parse(Token *tokens);

/********************lex**************************/
int lex(const char *input, Token *tokens, int *num_tokens, t_env_node *env);
void handle_special_characters(const char **p, Token *tokens, int *num_tokens);
void handle_v2(const char **p, char *special, TokenType *type);
void handle_quotes_and_words(const char **p, Token *tokens, int *num_tokens, QuoteWordParserState *state);
int check_syntaxe(Token *tokens, int nb_tokens);
int ft_size(char **argv);

/**********************redirection_parisng***********************/
void add_token(Token *tokens, int *num_tokens, TokenType type, char *value);
void skip_whitespace(const char **p);
void handle_redirection(Token *tokens, int *i, Command **current);
void finalize_command(Command **current);
char *expand_variable(const char *start, int length, t_env_node *env);
void handle_heredoc(t_data *data, Redirection *redir);

/********************************free_parsing************************************/
void free_all_resources(Command *head);
void free_redirection(Redirection *redir);
void free_all_v2(Command *current);

/*****************************REIRECTION_OPEN_FILE*****************************************/
void redirection_in_out(t_data *data, Command *cmd);
void open_check_redirections(t_data *data);
void	add_redirection(Redirection **redir_list, Redirection *redir);

/********************parsing_tools********************/
void ft_strncpy(char *dest, const char *src, int n);

/*****************builtins_utils*****************/
void append_to_existing_env(t_env_node *current, char *name, char *value);
void update_or_add_env(t_env_node **env_list, char *name, char *value);
void existing_env(t_env_node **env_list, char *name, char *value);
void update_env_var(t_env_node **env_list, char *name, char *new);
void ft_init_minishell(int ac, char **av, char **env, t_data *data);
char *find_command_path(const char *command, t_env_node *env_list);
char *get_env_value(t_env_node *env, const char *name);
void change_directory(t_data *data, const char *path);
void handle_new_env(t_env_node **env_list, char *arg);
void handle_export(t_env_node **env_list, char *arg);
char *ft_getenv(t_env_node *env, const char *name);
t_env_node *find_env(t_env_node *env, const char *name);
int handle_redirection_and_errors(t_data *data);
void print_oldpwd_and_pwd(t_env_node *env_list);
void ft_swap_env(t_env_node *a, t_env_node *b);
void free_env_list(t_env_node *env_list);
void print_sorted_env(t_env_node *env);
int validation_home(t_env_node *env);
t_env_node *create_env_list(char **s_env);
void sort_env(t_env_node *tmp_env);
void swap_pwd_oldpwd(t_data *data);
int is_valid_identifier(char *s);
void set_oldpwd(t_env_node *env);
void print_av(char **av, int n, int fd);
void set_pwd(t_env_node *env);
void check_option(char **av, int fd);
void go_home(t_data *data);
int check_number(char *s);
int check_n(char *str);
int check_is_builtin(t_data data);
void init_execution(t_data *data, int *status);
void singel_cmd(t_data *data, int *status);
void multiple_cmd(t_data *data, int *status);
void handle_sigint(int sig);
void	herd_sig(int sig);
t_data *get_global_data(void);
int ft_strlnode(Command *cmd);
int count_env_nodes(t_env_node *env_list);
void	fill_cmd(t_data *data);
void wating_processes(t_data *data, int *status);
void init_execution(t_data *data, int *status);
void execution(t_data *data);
char *build_executable_path(char *path, char *cmd);
char *check_cmd(char *cmd);
void clear_tab(char **tab);
char *find_path(char *cmd, char **env);
char **list_to_char(t_env_node *env_list);
void run_execution(t_data *data);
int check_is_builtin(t_data data);
int execute_builtin(t_data *data);
void run_builtin(t_data *data, int *status);
void run_builtin(t_data *data, int *status);

/***********************builtin*******************/
void build_export(t_data *data);
void build_unset(t_data *data);
void build_echo(t_data *data);
void build_env(t_data *data);
void build_pwd(t_data *data);
void build_cd(t_data *data);
void build_exit(char **av);

#endif
