#include "snake_input.h"

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

static int kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

int
snake_input_init(__attribute__((unused)) snake_game_t* p_game)
{
  /* No hace nada */
  return 1;
}

void
snake_input_update_new_heading (snake_game_t* p_game)
{
  p_game->new_heading = p_game->snake.heading;

  //TODO
  int n = kbhit();
  char key = 0;
  while (n > 0) {
    key = getchar();
    n--;
  }

    switch (key) {
      case 'w': // UP
        p_game->new_heading = UP;
        break;
      case 's': // DOWN
        p_game->new_heading = DOWN;
        break;
      case 'a': // LEFT
        p_game->new_heading = LEFT;
        break;
      case 'd': // RIGHT
        p_game->new_heading = RIGHT;
        break;
      default:
        // Ignore other keys
        break;
    }
}

void
snake_input_close(__attribute__((unused)) snake_game_t* p_game)
{
  /* No hace nada */
}
