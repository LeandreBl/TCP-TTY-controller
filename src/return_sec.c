/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** stdout -> socket
*/

#include <fcntl.h>
#include <unistd.h>

#include "remote-tty.h"
#include "protocol.h"

#include "my.h"
#include "defines.h"
#include "colors.h"

int		init_return_fd(void)
{
  int		fd;

  fd = open(RETURN_FILE, O_RDWR | O_CREAT | O_TRUNC, 0666);
  if (fd == -1)
  {
    mdprintf(2, "Error : Could not open %Dreturn fd file\n");
    return (-1);
  }
  dup2(1, fd);
  dup2(2, fd);
  return (0);
}

int		send_return_fd(session_info_t *session, int fd)
{
  char		*msg;

  msg = complete_read_lseek(fd);
  close(fd);
  if (msg == NULL)
    return (-1);
  if (send_msg(session, RETURN_FD_CMD, msg) == -1)
    return (-1);
  sfree(&msg);
  return (0);
}
