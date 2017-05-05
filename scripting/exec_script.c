/*
** exec_script.c for 42sh in /home/benki/Epitech/PSU_2016_42sh/scripting/
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Sat Apr 22 01:16:51 2017 Lucas Benkemoun
** Last update Sat Apr 29 15:24:41 2017 Lucas Benkemoun
*/

#include "project.h"

boolean	is_shebang(char *name)
{
  char	**tab;

  if (!(tab = read_file(name)))
    return (1);
  if (tab[0][0] == '#' && tab[0][1] == '!')
    return (1);
  return (0);
}

int		exec_script(t_script *s, t_shell *shell)
{
  int		i;
  t_string	*buff;

  i = -1;
  if (s->tab[0][0] == '#' && s->tab[0][1] == '!')
    i++;
  buff = init_string("");
  while (s->tab[++i])
    {
      if (!s->tab[i][0])
	continue;
      buff->recreate(buff, s->tab[i]);
      if ((!search_in_command_line(buff, shell) ||
	   (!look_at_line(buff) &&
	    !my_printf("Invalid null command.\n"))) && (shell->done = 1))
      	  continue;
      good_execution(shell, buff);
    }
  return (0);
}
