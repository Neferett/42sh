/*
** utils_prompt.c for  in /home/scrountchy/PSU_2016_42sh
** 
** Made by Sacha PERIN
** Login   <sacha.perin@epitech.eu>
** 
** Started on  Wed May  3 14:47:39 2017 Sacha PERIN
** Last update Wed May  3 14:47:40 2017 Sacha PERIN
*/

#include "project.h"
#include "lib.h"
#include <curses.h>
#include <term.h>

char    *insert_str(char *str, char *ins, int pos)
{
  char  *new;
  int   o;
  int   i;
  int   j;

  if (!(new = malloc(my_strlen(str) + my_strlen(ins) + 1)))
    return (NULL);
  o = 0;
  i = 0;
  j = 0;
  while (str[i] && i < pos)
    new[j++] = str[i++];
  while (ins[o])
    new[j++] = ins[o++];
  while (str[i])
    new[j++] = str[i++];
  new[j] = 0;
  return (new);
}

char	*delchar_atpos(char *str, int pos)
{
  char	*new;
  int	i;

  i = -1;
  new = malloc(my_strlen(str));
  while (str[++i] && i < pos)
    new[i] = str[i];
  while (str[i])
    {
      new[i] = str[i + 1];
      i++;
    }
  return (new);
}

char		*handle_events(t_shell *sh, char *buff)
{
  while (sh->read->error == -4 && sh->read->i > -my_strlen(buff))
    1 ? my_printf("%s", tparm(tigetstr("cub"), 1, 1)), sh->read->i-- : 0;
  while (sh->read->error == -5 && sh->read->i < 0)
    1 ? my_printf("%s", tparm(tigetstr("cuf"), 1, 1)), sh->read->i++ : 0;
  if (sh->read->error == -1)
    1 ? my_printf("%s", tparm(tigetstr("cub"), 1, 1)), sh->read->i-- : 0;
  if (sh->read->error == -2)
    1 ? my_printf("%s", tparm(tigetstr("cuf"), 1, 1)), sh->read->i++ : 0;
  if (sh->read->error == -3 && -sh->read->i < my_strlen(buff))
    {
      my_printf("%s", tparm(tigetstr("cub"), 1, 1));
      my_printf("%s", tparm(tigetstr("dch"), 1));
      if (buff && *buff)
	buff = delchar_atpos(buff, my_strlen(buff) + sh->read->i - 1);
    }
  while (sh->read->i < -my_strlen(buff))
    1 ? my_printf("%s", tparm(tigetstr("cuf"), 1, 1)), sh->read->i++ : 0;
  while (sh->read->i > 0 && sh->read->i--)
    my_printf("%s", tparm(tigetstr("cub"), 1, 1));
  return (buff);
}

char            *get_input(t_shell *sh)
{
  char		*buff;

  if (!isatty(STDIN_FILENO))
    return (get_next_line(0));
  if (!(buff= malloc(1)))
    exit(84);
  1 ? *buff = 0, sh->read->i = 0 : 0;
  while (get_read(sh))
    {
      if (sh->read->error < 0)
	buff = handle_events(sh, buff);
      else if (sh->read->str && *sh->read->str)
	{
	  if (sh->read->i && *sh->read->str != '\n')
	    my_printf("%s", tparm(tigetstr("ich"), 1));
	  my_printf("%s", sh->read->str);
	  if (*sh->read->str != '\n')
	    buff = insert_str(buff, sh->read->str,
			      my_strlen(buff) + sh->read->i);
	}
      if (sh->read->str && *sh->read->str && nb_of(sh->read->str, '\n'))
	break;
      1 ? (sh->read->str = NULL), (sh->read->error = 0) : 0;
    }
  return (buff);
}

void		prompt()
{
  if (isatty(STDIN_FILENO))
    my_printf("$> ");
}
