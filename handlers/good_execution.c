/*
** good_execution.c for PSU_2016_minishell2
**
** Made by	Jordan Bonaldi
** Login	jordan.bonaldi@epitech.net
**
** Started on	Mon Mar 13 16:20:01 2017 Jordan Bonaldi
** Last update	Sat Apr 22 22:50:05 2017 Jordan Bonaldi
*/

# include "project.h"

static void	try_execute(t_shell *shell, char c, t_string **string)
{
  int		i;

  i = -1;
  while (string[++i] && *string[i]->str)
    {
      if (shell->r_d && c == '&' &&
	  (shell->done || shell->list->n->delay != 0))
	break;
      while (string[i]->str[--string[i]->size] == ' ')
	string[i]->str[string[i]->size] = 0;
      if (c == 'r' && builtin_repeat(shell, string[i]))
	continue;
      else if (string[i]->contains(string[i], '&') && is_ok(string[i], '&') &&
	  good_execution(shell, string[i]))
	continue;
      else if ((good_char(string[i], shell) == '>' ||
		good_char(string[i], shell) == '<') &&
	       good_execution(shell, string[i]))
	continue;
      else if (string[i]->contains(string[i], '|') && is_ok(string[i], '|') &&
	       exec_pipe(stw_string(string[i], shell, &c), shell))
	continue;
      if (shell_up(shell, string[i]))
	search_command(shell);
    }
}

boolean		good_execution(t_shell *shell, t_string *line)
{
  char		c;
  t_string	**string;

  c = 0;
  string = NULL;
  shell->done = 0;
  if (!(string = stw_string(line, shell, &c)) || shell->ret)
    return (false);
  if (c == '|')
    return (exec_pipe(string, shell));
  if (!(string = handle_manip(shell, line, &c, string)))
    return (false);
  try_execute(shell, c, string);
  end_handle_manip(shell, line, c);
  return (true);
}
