#ifndef CANVAS_H
#define CANVAS_H
#include <stdlib.h>
#include <string.h>

typedef struct Pixel {
  char ascii;
  u_int8_t red;
  u_int8_t green;
  u_int8_t blue;
} pixel_t;

typedef struct Canvas {
  size_t width;
  size_t height;
  pixel_t *data;
} canvas_t;

canvas_t *canvas_create(size_t width, size_t height);

void canvas_destroy(canvas_t *c);

void canvas_clear(canvas_t *c);

void canvas_set_pixel(canvas_t *c, size_t x, size_t y, pixel_t pixel);

void canvas_draw(const canvas_t *c);

#endif
