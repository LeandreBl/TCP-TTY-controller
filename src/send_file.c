/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** send file
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "remote-tty.h"
#include "protocol.h"

#include "my.h"
#include "defines.h"
#include "colors.h"

static int	filesize(int fd)
{
  struct stat	sfile;

  if (fstat(fd, &sfile) == -1)
  {
    mdprintf(2, "Error : Count not access to file\n");
    return (-1);
  }
  return (sfile.st_size);
}

static int	read_write_receiver(int fd, session_info_t *session, int size)
{
  char		*buffer;
  int		done;
  int		toread;
  int		rd;

  done = 0;
  buffer = my_calloc(FILE_SIZE_PKT);
  while (done < size)
  {
    if (size - done > FILE_SIZE_PKT)
      toread = FILE_SIZE_PKT;
    else
      toread = size - done;
    rd = read(session->csocket, buffer, toread);
    if (rd == -1)
    {
      sfree(&buffer);
      return (-1);
    }
    if (write(fd, buffer, rd) == -1)
    {
      sfree(&buffer);
      return (-1);
    }
    done += rd;
    zeros(buffer, rd);
  }
  mprintf("\rFile successfully copied\n");
  prompt();
  close(fd);
  sfree(&buffer);
  prompt();
  return (0);
}

int		receive_file(session_info_t *session, header_t *header)
{
  char		size;
  char		*filename;
  int		fd;

  if (read(session->csocket, &size, 1) == -1)
  {
    mdprintf(2, "Error : Failed to receive file\n");
    prompt();
    return (-1);
  }
  filename = my_calloc(size + 1);
  if (read(session->csocket, filename, size + 1) == -1)
    return (-1);
  mprintf("\rReceiving file \"%s%s%s\"\n", BOLDGREEN, filename, RESET);
  prompt();
  if (access(filename, R_OK | W_OK) != -1)
  {
    mdprintf(2, "Error : File \"%s%s%s\" already exist\n",
	     BOLDGREEN, filename, RESET);
    prompt();
    read(session->csocket, NULL, header->pktlen);
    sfree(&filename);
    return (-1);
  }
  fd = open(filename, O_WRONLY | O_CREAT, 0666);
  if (fd == -1)
    return (-1);
  mprintf("\rReceiving file of size %s%d%s\n",
	  BOLDGREEN, header->pktlen, RESET);
  prompt();
  sfree(&filename);
  return (read_write_receiver(fd, session, header->pktlen));
}

static int	read_write_sender(int fd, session_info_t *session, int size)
{
  int		done;
  int		rd;
  char		*buffer;

  buffer = my_calloc(FILE_SIZE_PKT);
  if (buffer == NULL)
    return (-1);
  done = 0;
  while (done < size)
  {
    rd = read(fd, buffer, FILE_SIZE_PKT);
    if (rd == -1)
    {
      sfree(&buffer);
      return (-1);
    }
    if (write(session->csocket, buffer, rd) == -1)
    {
      sfree(&buffer);
      return (-1);
    }
    done += rd;
    zeros(buffer, rd);
  }
  sfree(&buffer);
  return (0);
}

int		send_file(const char *cmd, session_info_t *session)
{
  int		fd;
  int		size;
  char		*filename;

  if (my_strncmp(cmd, "send ", 5))
  {
    mdprintf(2, "Use !send <filename>\n");
    return (-1);
  }
  cmd += 5;
  fd = open(cmd, O_RDONLY);
  if (fd == -1)
  {
    mdprintf(2, "Error : Could not open \"%s%s%s\"\n", BOLDRED, cmd, RESET);
    return (-1);
  }
  while (nb_of(cmd, '/'))
    ++cmd;
  --cmd;
  filename = my_strdup(cmd);
  size = filesize(fd);
  if (send_header(session, FILE, size) == -1)
    return (-1);
  filename[0] = my_strlen(filename) - 1;
  mprintf("Sending \"%s%s%s\" of %s%d%s bytes\n",
	  BOLDGREEN, filename + 1, RESET, BOLDGREEN, size, RESET);
  if (filename[0] <= 0)
    return (-1);
  if (write(session->csocket, filename, my_strlen(filename) + 1) == -1)
    return (-1);
  if (read_write_sender(fd, session, size) == -1)
  {
    mdprintf(2, "Error : Unable to send %s file\n", cmd);
    return (-1);
  }
  mprintf("File successfully sended\n");
  close(fd);
  sfree(&filename);
  return (0);
}
