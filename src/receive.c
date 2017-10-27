/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** receive sequence
*/

#include <unistd.h>

#include "remote-tty.h"
#include "protocol.h"

#include "my.h"
#include "defines.h"

static void		add_fction(int action,
				   int (*fction)(session_info_t *info, header_t *header),
				   rcv_ptr_tab_t *index)
{
  index->action = action;
  index->fction = fction;
}

static void		init_tab(rcv_ptr_tab_t tab[])
{
  add_fction(WELCOME, (void *)receive_welcome, &tab[0]);
  add_fction(SIMPLE_MSG, (void *)receive_msg, &tab[1]);
  add_fction(LEAVE, (void *)receive_leave, &tab[2]);
  add_fction(RQ_COMMAND, (void *)receive_command, &tab[3]);
  add_fction(RETURN_FD_CMD, (void *)receive_command_return, &tab[4]);
}

static int		get_header(session_info_t *session, header_t *header)
{
  int			magic = 0;

  while (magic != MAGIC_NUMBER)
  {
    if (read(session->csocket, &magic, sizeof(int)) == -1)
    {
      session->status = COM_ERROR;
      return (-1);
    }
  }
  if (read(session->csocket, header, sizeof(header_t)) == -1)
  {
    session->status = COM_ERROR;
    return (-1);
  }
  return (0);
}

int			receive(session_info_t *session)
{
  static rcv_ptr_tab_t	tab[NB_FCTION];
  static int		calls;
  header_t		header;
  int			i;

  i = 0;
  if (calls == 0)
    init_tab(tab);
  ++calls;
  if (get_header(session, &header) == -1)
    return (-1);
  while (i < NB_FCTION)
  {
    if (header.action == tab[i].action)
      return (tab[i].fction(session, &header));
    ++i;
  }
  return (0);
}
