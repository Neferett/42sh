/*
** set_command.c for shell in /home/Neferett/PSU_2016_minishell1
**
** Made by Bonaldi Jordan
** Login   <Neferett@epitech.net>
**
** Started on  Thu Jan 12 13:58:31 2017 Bonaldi Jordan
** Last update	Sun Apr 23 00:08:38 2017 Jordan Bonaldi
*/

#include "project.h"

static int	check_er(char *name)
{
  if (name && name[0] && ((name[0] < 'a' || name[0] > 'z') &&
			  (name[0] < 'A' || name[0] > 'Z') &&
			  (name[0] != '_')))
    {
      write(2, "set: Variable name must begin with a letter.\n", 47);
      return (1);
    }
  if (my_str_isnum(name))
    {
      write(2, "set: Variable name must contain alphanumeric characters.\n",
            57);
      return (1);
    }
  return (0);
}

static int		loop_set(t_shell *shell, int i, char **tab)
{
  char		*name;
  char		*value;
  int		j;
  int		k;
  t_string	*n;
  t_string	*v;

  k = j = -1;
  name = malloc(strlen(tab[i]) + 1);
  value = malloc(strlen(tab[i]) + 1);
  while (tab[i][++j] && tab[i][j] != '=')
    name[j] = tab[i][j];
  name[j++] = 0;
  while (tab[i][j + ++k])
    value[k] = tab[i][j + k];
  value[k] = 0;
  if (set_exists(name, shell->set))
    my_rm_set(&shell->set, name, &my_strcmp, &my_strlen);
  1 ? n = init_string(name), v = init_string(value) : 0;
  if (check_er(name) && (shell->done = 1))
    return (1);
  add_set(n, v, shell->set);
  free(name);
  free(value);
  return (0);
}

static char		**init_set(char **cmd)
{
  int		i;
  char		*str;
  int		k;
  char		*new;

  k = -1;
  i = 0;
  str = strdup(cmd[0]);
  new = malloc(1024);
  while (cmd[++i])
    {
      str = my_strcat(my_strcat(str, " "), cmd[i]);
    }
  i = -1;
  while (str[++k])
    {
      if (str[k] == ' ' && str[k + 1] == '=')
	continue;
      if (str[k] == ' ' && i > 1 && str[k - 1] == '=')
	continue;
      new[++i] = str[k];
    }
  new[++i] = 0;
  free(str);
  return (my_str_to_wordtab(new, ' '));
}

static void	disp_set(t_shell *shell)
{
  t_set		*set;

  set = shell->set;
  if ((!set || set->n == shell->set) &&
      !my_printf("No alias created\n"))
		return;
  while (set->p != shell->set)
    {
      my_printf("$%s\t->\t%s\n", set->p->var->str,
		set->p->data->str);
      set = set->p;
    }
}

void		builtin_set_var(t_shell *shell)
{
  int		i;
  char		**t;

  i = 0;
  t = init_set(shell->cmd);
  if (*shell->cmd && !shell->cmd[1])
    disp_set(shell);
  while (t[++i])
    {
      if (loop_set(shell, i, t))
	return;
    }
}
