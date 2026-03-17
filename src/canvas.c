#include "../include/canvas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

canvas_t *canvas_create(size_t width, size_t height) {
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

void canvas_set_pixel(canvas_t *c, size_t x, size_t y, char ch) {
  if (x >= c->width)
    return;
  if (y >= c->height)
    return;

  size_t index = y * c->width + x;
  c->data[index] = ch;
  return;
}

void canvas_draw(const canvas_t *c) {
  for (size_t i = 0; i < c->height; i++) {
    for (size_t j = 0; j < c->width; j++) {
      printf("%c", c->data[i * c->width + j]);
    }
    printf("\n");
  }
  return;
}
