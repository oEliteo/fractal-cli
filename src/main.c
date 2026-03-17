#include "../include/canvas.h"

int main() {
  canvas_t *c = canvas_create(20, 10);
  for (size_t i = 0; i < c->height; i++) {
    for (size_t j = 0; j < c->width; j++) {
      canvas_set_pixel(c, j, i, '#');
    }
  }
  canvas_draw(c);
  canvas_destroy(c);
  return 0;
}
