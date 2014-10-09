
#include <stdio.h>

#include <ev.h>


/* // form libev's documentation:

   static void
   passwd_cb (struct ev_loop *loop, ev_stat *w, int revents)
   {
     // /etc/passwd changed in some way
     if (w->attr.st_nlink)
       {
         printf ("passwd current size  %ld\n", (long)w->attr.st_size);
         printf ("passwd current atime %ld\n", (long)w->attr.st_mtime);
         printf ("passwd current mtime %ld\n", (long)w->attr.st_mtime);
       }
     else
       // you shalt not abuse printf for puts
       puts ("wow, /etc/passwd is not there, expect problems. "
             "if this is windows, they already arrived\n");
   }

   ...
   ev_stat passwd;

   ev_stat_init (&passwd, passwd_cb, "/etc/passwd", 0.);
   ev_stat_start (loop, &passwd);
*/

static void stat_cb(struct ev_loop *loop, ev_stat *w, int revents)
{
  if (w->attr.st_nlink)
  {
    //printf ("current size  %ld\n", (long)w->attr.st_size);
    printf ("current atime %ld\n", (long)w->attr.st_atime);
    printf ("current mtime %ld\n", (long)w->attr.st_mtime);
  }
  else
  {
    puts("something went wrong");
  }
}

int main()
{
  struct ev_loop *l = ev_default_loop(0);
  ev_stat est;

  ev_stat_init(&est, stat_cb, ".", 0.);
  ev_stat_start(l, &est);

  ev_loop(l, 0);
}

