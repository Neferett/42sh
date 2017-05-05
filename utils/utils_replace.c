/*
** utils_replace.c for PSU_2016_minishell2
**
** Made by	Jordan Bonaldi
** Login	jordan.bonaldi@epitech.net
**
** Started on	Sat Apr 22 01:01:42 2017 Jordan Bonaldi
** Last update	Sun Apr 23 00:10:39 2017 Jordan Bonaldi
*/

# include "project.h"

char			*hse(char *el)
{
  char			*ret;

  if (!(ret = malloc(1)))
    return (NULL);
  while (*el != '=')
    {
      ret = my_strcatc(ret, *el);
      el++;
    }
  return (ret);
}

void		replace_that_env(char *initial, char *replace, t_shell *shell)
{
  char		*tmp;
  char		*lol;

  if (!(tmp = strstr(initial, replace)))
    return;
  lol = get_env(++replace, shell->lenv);
  strncpy(tmp, lol, my_strlen(lol));
}

void		replace_that_str(char *initial, char *replace, char *toreplace)
{
  char		*tmp;

  if (!(tmp = strstr(initial, replace)))
    return;
  strncpy(tmp, toreplace, my_strlen(toreplace) + 1);
}

int	test_tild_return(t_shell *shell, t_string *line, int *ok, boolean ret)
{
  if (!ret && line->contains(line, '~'))
    {
      if (!get_env("HOME", shell->lenv) && (*ok = 2))
	my_printf("No $HOME variable set.\n");
      else
	replace_that_str(line->str, "~", get_env("HOME", shell->lenv));
  }
  else if (ret)
    return (!*ok && line->contains(line, '$') &&
	    line->str[line->placeof(line, '$') + 1] &&
	    line->str[line->placeof(line, '$') + 1] != 27 && is_valid(line) ?
	    my_printf("%s: Undefined variable\n", strstr(line->str, "$") + 1) :
	    *ok == 2 ? 0 : 1);
  return (0);
}

boolean		search_in_command_line(t_string *line, t_shell *shell)
{
  int		ok;
  t_list	*tmp;
  t_set		*tmp2;

  1 ? ok = false, tmp = shell->lenv, tmp2 = shell->set : 0;
  test_tild_return(shell, line, &ok, false);
  if (line->contains(line, '$') && is_valid(line) &&
      line->str[line->placeof(line, '$') + 1] &&
      line->str[line->placeof(line, '$') + 1] != 27 &&
      tmp && tmp->n != shell->lenv)
    {
      while (tmp->p != shell->lenv)
	1 ? (strstr(line->str, hse(tmp->p->data)) ?
	     replace_that_env(line->str,
			      my_strcat("$", hse(tmp->p->data)), shell),
	     (ok = true) : 0), tmp = tmp->p : 0;
      if (!ok && tmp2 && tmp2->n != shell->set)
	while (tmp2->p != shell->set)
		{
		1 ? (strstr(line->str, tmp2->p->var->str) ?
		     replace_that_str(line->str,
				      my_strcat("$", tmp2->p->var->str),
				      tmp2->p->data->str), ok = true : 0),
		tmp2 = tmp2->p : 0;
	}
    }
  return (test_tild_return(shell, line, &ok, true));
}
