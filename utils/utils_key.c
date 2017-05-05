/*
** utils_key.c for 42sh in /Users/neferett/EPITECH/PSU_2016_42sh/utils/
**
** Made by Jordan Bonaldi
** Login   <Neferett@epitech.eu@epitech.eu>
**
** Started on  Wed May  3 15:23:00 2017 Jordan Bonaldi
** Last update Wed May  3 15:23:00 2017 Jordan Bonaldi
*/

# include "project.h"

char	*prev_cmds(t_shell *sh)
{
  char	*cmd;
  int	i;

  i = -1;
  if (!(cmd = malloc(1)))
    exit(84);
  *cmd = 0;
  if (sh->tmp->n != sh->list)
    {
      while (sh->tmp->n->cmd[++i])
	  cmd = my_strcat(cmd, sh->tmp->n->cmd[i]);
      return (cmd);
    }
  return (NULL);
}

char	*next_cmds(t_shell *sh)
{
  char	*cmd;
  int	i;

  i = -1;
  if (!(cmd = malloc(1)))
    exit(84);
  *cmd = 0;
  if (sh->tmp->p != sh->list)
    {
      while (sh->tmp->p->cmd[++i])
	cmd = my_strcat(cmd, sh->tmp->p->cmd[i]);
      return (cmd);
    }
  return (NULL);
}
