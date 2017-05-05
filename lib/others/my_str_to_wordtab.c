/*
** my_str_to_wordtab.c for my_str_to_wordtab in /home/Neferett/CPool_Day08/task04
**
** Made by Bonaldi Jordan
** Login   <Neferett@epitech.net>
**
** Started on  Wed Oct 12 10:53:16 2016 Bonaldi Jordan
** Last update	Sun Apr 09 22:12:08 2017 Jordan Bonaldi
*/

# include "lib.h"

static boolean	get_ini(char c)
{
  return (c == '"' || c == '\'');
}

static char	*fill_up(char *str)
{
  int	i;
  char	*arr;

  i = -1;
  if (!(arr = malloc(my_strlen(str) * 10)))
    exit(84);
  while (str[++i] && !get_ini(str[i]))
    arr[i] = str[i];
  arr[i] = 0;
  return (arr);
}

static boolean	is_in(char *str)
{
  int	i;

  i = 0;
  while (str[++i] && str[i] != '"')
    {
      if (str[i] == '&' || str[i] == '>' || str[i] == '<' ||
	  str[i] == '|' || str[i] == ' ')
	return (true);
    }
  return (false);
}

char	**tab_complete(char **tab, char *str, int i, char c)
{
  int	j;
  boolean	in;
  char	*arr;
  char	ini;

  if ((j = -1) && !(in = false) && !(arr = malloc(my_strlen(str) * 10)))
    return (NULL);
  while (*str && !(i = 0) && (!++(j) ? 1 : 1))
    {
      while (*str && *str == c && (str++)) {}
      while (*str && *str != c)
	{
	  if (!in && get_ini(*str) && is_in(str) && ++str)
	    {
	      ini = *(str - 1) == '\'' ? '\'' : '"';
	      if (c != ' ')
		arr = my_strcat(arr, my_strcat(my_strcatc("", ini), my_strdup(fill_up(str))));
	      else
		arr = my_strcat(arr, my_strdup(fill_up(str)));
	    while (*str && *str != ini && (str++) && ++i) {}
	    ++str;
	      if (c != ' ' && (arr[++i] = ini) && !(arr[++i] = 0))
		continue;
	    }
	  else if (get_ini(*str) && !in && (in = true) && ++str) {}
	  else if (get_ini(*str) && in && !(in = false) && ++str) {}
	if ((arr[i] = *str) && (++i) && !(arr[i] = 0) && (str++)) {}
	}
	  if (*arr && (tab[j] = my_strdup(arr)) && (i = -1))
	    {
	      while (arr[++i])
		arr[i] = 0;
	    }
    }
  tab[++j] = NULL;
  return (tab);
}

char	**my_str_to_wordtab(char *str, char c)
{
  char	**tab;
  int	i;

  i = 0;
  if (!(tab = malloc(my_strlen(str) * 10)))
    return (NULL);
  tab = tab_complete(tab, str, i, c);
  return (tab);
}
