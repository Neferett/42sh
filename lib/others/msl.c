/*
** msl.c for long len in /home/Neferett/PSU_2016_my_printf
**
** Made by Bonaldi Jordan
** Login   <Neferett@epitech.net>
**
** Started on  Fri Apr 28 15:50:33 2017 Jordan Bonaldi Jo Last update Fri Apr 28 15:50:28 2017 Jordan Bonaldi
*/

short int     msl(short int nb)
{
  short int   i;

  i = 0;
  if (nb < 0 && (nb *= -1) && i++) {}
  while (nb > 9)
    if ((nb /= 10) && ++i) {}
  return (++i);
}

long int     mll(long int nb)
{
  long int   i;

  i = 0;
  if (nb < 0 && (nb *= -1) && i++) {}
  while (nb > 9)
    if ((nb /= 10) && ++i) {}
  return (++i);
}
