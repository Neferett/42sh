/*
** project.h for project_header in /home/Neferett/bin/IMPORT/include
**
** Made by Bonaldi Jordan
** Login   <Neferett@epitech.net>
**
** Started on  Mon Nov 21 01:13:04 2016 Bonaldi Jordan
** Last update	Sat Apr 22 23:29:31 2017 Jordan Bonaldi
*/

#ifndef H_CHECK
# define H_CHECK

# define _DEFAULT_SOURCE
# define _GNU_SOURCE

# include <termios.h>
# include <string.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <glob.h>
# include "lib.h"

# define TMP_FILE	".mysh"

typedef struct		s_read
{
  char	*str;
  int	error;
  int	i;
}			t_read;

typedef struct		s_pos_dir
{
  char			*before;
  char			*after;
}			t_pos_dir;

typedef struct		s_list_cmd
{
  pid_t			pid;
  int			delay;
  char			**cmd;
  boolean		succes;
  struct s_list_cmd	*n;
  struct s_list_cmd	*p;
}			t_list_cmd;

typedef struct		s_list
{
  char			*data;
  struct s_list		*n;
  struct s_list		*p;
}			t_list;

typedef struct		s_set
{
  t_string		*var;
  t_string		*data;
  struct s_set		*n;
  struct s_set		*p;
}			t_set;

typedef struct s_shell t_shell;

typedef struct		s_builtin
{
  char			*cmd;
  void			(*builtin)(t_shell *);
}			t_builtin;

typedef struct		s_manip
{
  int			righttmp;
  int			righttmpfd;
  int			lefttmp;
  int			lefttmpfd;
}			t_manip;

typedef struct 		s_alias
{
  t_string		*cmd;
  t_string		*alias;
  struct s_alias	*n;
  struct s_alias	*p;
}			t_alias;

struct			s_shell
{
  int			ret;
  int			done;
  t_string		**string;
  t_manip		*manip;
  boolean		r_d;
  boolean 		pipe;
  boolean		left;
  boolean 		right;
  boolean		first;
  boolean		and_s;
  t_alias		*alias;
  char			**tenv;
  t_list		*lenv;
  t_set			*set;
  char			**cmd;
  char			**path;
  t_list_cmd		*tmp;
  t_list_cmd		*list;
  t_builtin		*builtin;
  t_read		*read;
};

boolean	is_valid(t_string *line);
boolean			is_ok(t_string *line, char c);
boolean		shell_up(t_shell *shell, t_string *str);
void		replace_that_str(char *initial, char *replace, char *toreplace);
t_string	**handle_manip(t_shell *shell, t_string *line,
			       char *c, t_string **);
void		end_handle_manip(t_shell *shell, t_string *line, char c);
t_string	**start_d_left(t_shell *shell, t_string **);
void		end_d_left(t_shell *shell);
t_string	**start_nd_left(t_shell *shell, t_string **);
void		end_nd_left(t_shell *shell);
t_string	**start_d_right(t_shell *shell, t_string **);
void		end_d_right(t_shell *shell);
boolean		exec_pipe(t_string **ln, t_shell *shell);
t_string	**start_nd_right(t_shell *shell, t_string **);
void		end_nd_right(t_shell *shell);
boolean		look_at_line(t_string *line);
int		st_len(t_string **string);
void		free_tab(t_shell *);
void		search_command(t_shell *);
t_shell		*init_shell(char **);
char		**get_paths(t_shell *);
void		add_cmd(t_shell *, char **, pid_t);
int		get_read(t_shell *);
boolean		is_in_list(t_shell *);
t_alias		*init_alias();
char		*get_input(t_shell *);
void		add_alias(t_string *cmdalias, t_string *cmd, t_alias *al);
void		replace_that(char *initial, char *replace, t_shell *shell);
void		my_rm_alias(t_alias **l, void *data,
			    int (*cmp)(), int (*len)());
t_string	*alias_exists(char *cmd, t_alias *alias);
t_builtin	*init_builtin();
void		builtin_cd(t_shell *);
void		builtin_set(t_shell *);
void		builtin_unset(t_shell *);
void		builtin_env(t_shell *);
void		builtin_exit(t_shell *);
void		builtin_alias(t_shell *);
void		builtin_which(t_shell *);
void		builtin_where(t_shell *);
void		builtin_echo(t_shell *);
void		builtin_set_var(t_shell *);
boolean		builtin_repeat(t_shell *sh, t_string *str);
char		*get_env(char *, t_list *);
void		prompt();
t_list		*env_to_list(char **);
void		show_env(t_list *);
void		add_env(char *, t_list *);
void		add_end_env(char *, t_list *);
void		my_rm_list(t_list **, void *, int (*)(), int (*)());
void		segfault(t_shell *);
void		signal_handling(int);
boolean		get_permission(char *);
t_list		*init_list();
char		good_char(t_string *line, t_shell *);
boolean		good_execution(t_shell *shell, t_string *line);
t_string	**stw_string(t_string *line, t_shell *shell, char *);
boolean		search_in_command_line(t_string *line, t_shell *shell);
t_set		*init_list_set();
t_string	*set_exists(char *cmd, t_set *s);
void		add_set(t_string *var, t_string *data, t_set *s);
void		my_rm_set(t_set **l, void *data,
			  int (*cmp)(), int (*len)());
void		is_globbing(t_shell *);

typedef struct	s_script
{
  char		**argv;
  int		argc;
  char		**var;
  char		**tab;
}		t_script;

int     my_strccmp(char *s1, char *s2, char c);
char	**set_variable(char **var, char *name, char *value);
char	*set_value(char *name, char *value);
int	scripting(t_shell *shell);
int     my_tablen(char **tab);
char    **cpy_tab(char **ae);
char    **realloc_tab(char **ae);
char	**read_file(char *name);
void	my_freetab(char **tab);
int	exec_script(t_script *s, t_shell *shell);
boolean	is_shebang(char *name);
void	arg_handler(char **av, char **ae);

#endif
