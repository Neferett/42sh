/*
** main.c for  in /home/scrountchy/PSU_2016_42sh
**
** Made by Sacha PERIN
** Login   <sacha.perin@epitech.eu>
**
** Started on  Wed May  3 14:47:22 2017 Sacha PERIN
** Last update Wed May  3 14:47:24 2017 Sacha PERIN
*/

# include "project.h"
# include <curses.h>
# include <term.h>

void	signal_handling(int signal)
{
  if (signal && !my_printf("\n"))
    prompt();
}

void		set_ret_value(t_shell *shell)
{
  if (set_exists("?", shell->set))
    my_rm_set(&shell->set, "?", &my_strcmp, &my_strlen);
  add_set(init_string("?"),
	  init_string(my_itoa(shell->done == -1 ? shell->ret :
			      shell->done == 1 ? 1 :
			      shell->list->n->delay)), shell->set);
}

void		main_handling(t_shell *shell)
{
  int		i;
  char		*input;
  t_string	*buff;

  i = 0;
  buff = init_string("NULL");
  shell->tmp = shell->list;
  while ((input = get_input(shell)))
    {
      shell->tmp = shell->list;
      buff->recreate(buff, my_epur_str(input));
      set_ret_value(shell);
      shell->done = false;
      if (!buff->first)
 	prompt();
      else
	{
	  if ((!search_in_command_line(buff, shell) || (!look_at_line(buff) &&
	      !my_printf("Invalid null command.\n"))) && ++i)
	    {
	      shell->done = 1;
	      prompt();
	      continue;
	    }
	  good_execution(shell, buff);
	  prompt();
	  i++;
	}
    }
}

int		main(int argc, char **argv, char **ae)
{
  t_shell	*shell;

  if (argc > 1)
	arg_handler(argv, ae);
  shell = init_shell(ae);
  if (!ae || !**argv)
    return (84);
  if (setupterm(get_env("TERM", shell->lenv), 1, (int *)0) < 0)
    exit (84);
  my_printf("%s", tigetstr("smkx"));
  prompt();
  add_set(init_string("0"), init_string(argv[0] + 2), shell->set);
  add_set(init_string("#"), init_string(my_itoa(argc - 1)), shell->set);
  signal(SIGINT, signal_handling);
  main_handling(shell);
  if (isatty(STDIN_FILENO))
    my_printf("exit\n");
  return (shell->done == -1 ? shell->ret : shell->done == 1 ? 1 :
      shell->list->n->delay);
}
