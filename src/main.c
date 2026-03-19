#include "../include/canvas.h"
#include "../include/fractal_context.h"

int main() {
  canvas_t *c = canvas_create(160, 50);
  context_t *ctx = context_create();
  for (size_t i = 0; i < c->height; i++) {
    for (size_t j = 0; j < c->width; j++) {
      c_coord_t complex_coord = grid_coord_to_complex_coord(c, ctx, j, i);
      int iterations = iterative_escape(ctx, complex_coord);
      char ascii = ascii_character_to_draw(ctx, iterations);
      canvas_set_pixel(c, j, i, ascii);
    }
  }
  canvas_draw(c);
  canvas_destroy(c);
  return 0;
}
