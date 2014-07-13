
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

#include <ev.h>


#define PORT 4001
#define BUFFER_SIZE 1024


void read_cb(struct ev_loop *l, struct ev_io *eio, int revents)
{
  if (EV_ERROR & revents) { perror("read invalid event"); return; }

  char buffer[BUFFER_SIZE];

  ssize_t r = recv(eio->fd, buffer, BUFFER_SIZE, 0);

  if (r < 0) { perror("read error"); return; }

  if (r == 0)
  {
    ev_io_stop(l, eio);
    free(eio);
    perror("client closing");
    return;
  }

  printf("  >%s<\n", buffer);

  send(eio->fd, buffer, r, 0);
  memset(buffer, 0, r);
}

void accept_cb(struct ev_loop *l, struct ev_io *eio, int revents)
{
  struct sockaddr_in ca; // client address
  socklen_t cal = sizeof(struct sockaddr_in);
  struct ev_io *ceio = calloc(1, sizeof(struct ev_io));

  if (EV_ERROR & revents) { perror("accept invalid event"); return; }

  int csd = accept(eio->fd, (struct sockaddr *)&ca, &cal);

  if (csd < 0) { perror("accept error"); return; }

  // client connected...

  ev_io_init(ceio, read_cb, csd, EV_READ);
  ev_io_start(l, ceio);
}

int main()
{
  struct ev_io eio;
  struct ev_loop *l = ev_default_loop(0);

  int sd = socket(PF_INET, SOCK_STREAM, 0);

  if (sd < 0) { perror("socket error"); return 1; }

  struct sockaddr_in a;
  memset(&a, 0, sizeof(struct sockaddr_in));
  a.sin_family = AF_INET;
  a.sin_port = htons(PORT);
  a.sin_addr.s_addr = INADDR_ANY;

  int r;

  r = bind(sd, (struct sockaddr *)&a, sizeof(struct sockaddr_in));
  if (r != 0) { perror("bind error"); return 2; }

  r = listen(sd, 2);
  if (r < 0) { perror("listen error"); return 3; }

  ev_io_init(&eio, accept_cb, sd, EV_READ);
  ev_io_start(l, &eio);

  ev_loop(l, 0);
}

