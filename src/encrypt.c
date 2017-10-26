/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** encrypt
*/

int		encrypt(char *msg, int pktlen)
{
  int		i;

  i = 0;
  while (i < pktlen)
  {
    msg[i] = -msg[i];
    ++i;
  }
  return (0);
}

int		unencrypt(char *msg, int pktlen)
{
  int		i;

  i = 0;
  while (i < pktlen)
  {
    msg[i] = -msg[i];
    ++i;
  }
  return (0);
}
