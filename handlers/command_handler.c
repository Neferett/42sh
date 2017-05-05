/*
** command_handler.c for 42sh in /Users/neferett/EPITECH/PSU_2016_42sh/handlers/
**
** Made by Jordan Bonaldi
** Login   <Neferett@epitech.eu@epitech.eu>
**
** Started on  Sat Apr 22 22:49:09 2017 Jordan Bonaldi
** Last update	Sat Apr 22 23:17:51 2017 Jordan Bonaldi
*/

# include "project.h"

static void	handle_historic_searching(t_shell *shell)
{
  boolean	sucess;
  t_list_cmd	*tmp;
  char		**array;
  int		i;
  int		j;

  if ((tmp = shell->list) && !(i = 0) && (j = -1) && !(sucess = false)) {}
  while (tmp->n != shell->list)
    {
      if (!my_strncmp(*shell->cmd + 1, *tmp->n->cmd,
		      my_strlen(*shell->cmd + 1)))
	{
	  array = malloc(sizeof(tmp->n->cmd) + sizeof(shell->cmd + 1));
	  1 ? array = tmp->n->cmd, j = tab_len(tmp->n->cmd) - 1 : 0;
	  while (shell->cmd[++i])
	    array[++j] = shell->cmd[i];
	  1 ? array[++j] = NULL, shell->cmd = array,
	      my_show_wordtab(shell->cmd, ' '), my_printf("\n") : 0;
	  sucess = true;
	  break;
	}
      tmp = tmp->n;
    }
  if (!sucess && !my_printf("%s: Event not found\n", *shell->cmd + 1) &&
      (shell->done = 1)) {}
}

static void	handle_historic_prev(t_shell *shell)
{
  char		**array;
  int		i;
  int		j;

  if (!(i = 0) && (j = -1)) {}
  array = malloc(sizeof(shell->list->n->cmd) + sizeof(shell->cmd + 1));
  1 ? array = shell->list->n->cmd, j = tab_len(shell->list->n->cmd) - 1 : 0;
  while (shell->cmd[++i])
    array[++j] = shell->cmd[i];
  1 ? array[++j] = NULL, shell->cmd = array,
      my_show_wordtab(shell->cmd, ' '), my_printf("\n") : 0;
}

boolean		shell_up(t_shell *shell, t_string *str)
{
  char		**cmd;
  char		**alias_tab;
  t_string	*alias;
  int		i;
  int		j;

  i = -1;
  j = -1;
  shell->cmd = str->towordtab(str, ' ');
  if (**shell->cmd == '!' && shell->cmd[0][1] && shell->cmd[0][1] != '!')
    handle_historic_searching(shell);
  else if (**shell->cmd == '!' && shell->cmd[0][1] && shell->cmd[0][1] == '!')
    handle_historic_prev(shell);
  is_globbing(shell);
  if ((alias = alias_exists(*shell->cmd, shell->alias)))
    {
      alias_tab = alias->towordtab(alias, ' ');
      cmd = malloc(sizeof(char *) * (tab_len(shell->cmd)
			  + tab_len(alias_tab) + 1));
      while (alias_tab[++i])
	cmd[++j] = alias_tab[i];
      i = 0;
      while (shell->cmd[++i])
	cmd[++j] = shell->cmd[i];
      cmd[++j] = 0;
      shell->cmd = cmd;
    }
  return (true);
}
