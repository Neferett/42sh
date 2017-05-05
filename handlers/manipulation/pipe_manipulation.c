/*
** pipe_manipulation.c for PSU_2016_minishell2
**
** Made by	Jordan Bonaldi
** Login	jordan.bonaldi@epitech.net
**
** Started on	Sun Apr 09 11:49:14 2017 Jordan Bonaldi
** Last update	Sat Apr 22 02:09:33 2017 Jordan Bonaldi
*/

# include "project.h"

static boolean 		exec_pipe2(t_string **lines, t_shell *shell)
{
  int   		p[2];
  int			a;
  int			i;
  boolean		sucess;

  if ((a = open(TMP_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0755)) < 0)
    return (false);
  1 ? sucess = true, i = -1, p[0] = dup(1), p[1] = dup(0) : 0;
  while (lines[++i] && shell_up(shell, lines[i]))
    {
      if (i == 1)
	{
	  dup2(p[0], 1);
	  if ((a = open(TMP_FILE, O_RDONLY)) < 0)
	    return (false);
	  1 ? dup2(a, 0), close(a), search_command(shell),
	  dup2(p[1], 0) : 0;
	  shell->done == 1 ? sucess = false : 0;
	}
      else if (i == 0)
	1 ? dup2(a, 1), search_command(shell), close(a),
      (shell->done == 1 ? sucess = false : 1) : 0;
    }
  return (!sucess ? shell->done = 1 : true);
}

static boolean		exec_pipe_normal(t_string **lines, t_shell *shell)
{
  int   p[2];
  pid_t pid;
  int   fd;
  int		a;
  boolean sucess;

  if (!(a = 0) && (sucess = true) && !(fd = 0)) {}
  while (*lines && shell_up(shell, *lines))
    {
      if (pipe2(p, O_NONBLOCK) < 0 || (pid = fork()) < 0)
	return (true);
      else if (!pid)
	{
	  1 ? dup2(fd, 0), (*(lines + 1) ? dup2(p[1], 1) : 0),
	  search_command(shell), close(p[0]) : 0;
	  exit(shell->done ? 1 : shell->list->n->delay);
	}
      else
	{
	  1 ? wait(&a), close(p[1]), fd = p[0], lines++,
	      (WEXITSTATUS(a) != 0 ? sucess = false : 0) : 0;
	}
    }
  return (!sucess ? shell->done = 1 : true);
}

static boolean		exec_pipe_r_d(t_string **lines, t_shell *shell)
{
  while (*lines && shell_up(shell, *lines))
    {
      good_execution(shell, *lines);
      if (!(shell->done == -1 ? shell->ret : shell->done == 1 ? 1 :
          shell->list->n->delay))
	  break;
      shell->done = 0;
      shell->ret = 0;
      shell->list->n->delay = 0;
      lines++;
    }
  return (true);
}

boolean		exec_pipe(t_string **lines, t_shell *shell)
{
  if (shell->r_d && !(shell->r_d = false))
    return (exec_pipe_r_d(lines, shell));
  else if (st_len(lines) == 2)
    return (exec_pipe2(lines, shell));
  else
    return (exec_pipe_normal(lines, shell));
}
