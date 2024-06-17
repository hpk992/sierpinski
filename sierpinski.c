#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SCREEN_WIDTH 55
#define SCREEN_HEIGHT 25

int width = SCREEN_WIDTH + 1;
int height = SCREEN_HEIGHT + 1;

void plotPoint(char screen[height][width], double x, double y) {
  int xi = (int)round(x);
  int yi = (int)round(y);
  if (x >= 0 && x < width && y >= 0 && y < height) {
    screen[yi][xi] = '*';
  }
}

int isInsideTriangle(double x, double y, double x1, double y1, double x2,
                     double y2, double x3, double y3) {
  double area = 0.5 * fabs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
  double w1 = (x1 * (y3 - y1) + (y - y1) * (x3 - x1) - x * (y3 - y1)) /
              ((y2 - y1) * (x3 - x1) - (x2 - x1) * (y3 - y1));
  double w2 = (y - y1 - w1 * (y2 - y1)) / (y3 - y1);

  return w1 >= 0 && w2 >= 0 && ((w1 + w2) <= 1);
}

void drawSierpinski(char screen[height][width], double x, double y, double x1,
                    double y1, double x2, double y2, double x3, double y3,
                    int n) {
  if (n < 1) {
    return;
  } else {
    int choice = rand() % 3;
    double xm, ym;

    switch (choice) {
    case 0:
      xm = (x + x1) / 2;
      ym = (y + y1) / 2;
      break;
    case 1:
      xm = (x + x2) / 2;
      ym = (y + y2) / 2;
      break;
    case 2:
      xm = (x + x3) / 2;
      ym = (y + y3) / 2;
      break;
    }

    plotPoint(screen, xm, ym);

    printf("\x1b[H");
    // Print the screen
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        printf("%c", screen[i][j]);
      }
      printf("\n");
    }

    usleep(2000);

    drawSierpinski(screen, xm, ym, x1, y1, x2, y2, x3, y3, n - 1);
  }
}

int main() {
  char screen[height][width];
  memset(screen, ' ', height * width);

  double x1 = 0, y1 = SCREEN_HEIGHT;
  double x2 = SCREEN_WIDTH, y2 = SCREEN_HEIGHT;
  double x3 = (double)SCREEN_WIDTH / 2, y3 = 0;
  plotPoint(screen, x1, y1);
  plotPoint(screen, x2, y2);
  plotPoint(screen, x3, y3);

  srand(time(NULL));
  double x, y;
  do {
    x = rand() % SCREEN_WIDTH;
    y = rand() % SCREEN_HEIGHT;
  } while (!isInsideTriangle(x, y, x1, y1, x2, y2, x3, y3));
  plotPoint(screen, x, y);

  drawSierpinski(screen, x, y, x1, y1, x2, y2, x3, y3, 9000);

  return 0;
}
