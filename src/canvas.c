#include "../include/canvas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

canvas_t *canvas_create(int width, int height) {
  canvas_t *canvas = malloc(sizeof(canvas_t));
  if (canvas == NULL)
    return NULL;
  canvas->data = malloc(sizeof(char) * width * height);
  if (canvas->data == NULL) {
    free(canvas);
    return NULL;
  }

  canvas->height = height;
  canvas->width = width;
  canvas_clear(canvas);

  return canvas;
}

void canvas_destroy(canvas_t *c) {
  if (c == NULL)
    return;

  free(c->data);
  free(c);
  return;
}

void canvas_clear(canvas_t *c) {
  if (c == NULL)
    return;
  memset(c->data, ' ', sizeof(char) * c->height * c->width);
  return;
}

void canvas_set_pixel(canvas_t *c, int x, int y, char ch) {
  if (x < 0 || x >= c->width)
    return;
  if (y < 0 || y >= c->height)
    return;

  int index = y * c->width + x;
  c->data[index] = ch;
  return;
}

void canvas_draw(const canvas_t *c) {
  for (int i = 0; i < c->height; i++) {
    for (int j = 0; j < c->width; j++) {
      printf("%c", c->data[i * c->width + j]);
    }
    printf("\n");
  }
  return;
}
