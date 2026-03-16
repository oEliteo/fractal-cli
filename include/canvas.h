#ifndef CANVAS_H
#define CANVAS_H

typedef struct Canvas {
  int width;
  int height;
  char *data;
} canvas_t;

canvas_t *canvas_create(int width, int height);

void canvas_destroy(canvas_t *c);

void canvas_clear(canvas_t *c);

void canvas_set_pixel(canvas_t *c, int x, int y, char ch);

void canvas_draw(const canvas_t *c);

#endif
