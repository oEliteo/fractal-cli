#include "../include/fractal_context.h"
#include "../include/complex_coord.h"

context_t *context_create() {
  context_t *ctx = malloc(sizeof(context_t));
  if (ctx == NULL)
    return NULL;
  ctx = init_mandelbrot(ctx);

  return ctx;
}

void context_destroy(context_t *ctx) {
  if (ctx == NULL)
    return;
  free(ctx);
  return;
}

c_coord_t grid_coord_to_complex_coord(canvas_t *c, context_t *ctx, size_t x,
                                      size_t y) {
  // needs correct implementation.
  c_coord_t coord;
  return coord;
}

int iterative_escape(context_t *ctx, size_t x, size_t y);

char ascii_character_to_draw(context_t *ctx, int iterations);

context_t *init_mandelbrot(context_t *ctx) {
  if (ctx == NULL)
    return NULL;
  ctx->real_min = -2.0;
  ctx->real_max = 1.0;
  ctx->imaginary_min = -1.0;
  ctx->imaginary_max = 1.0;
  ctx->max_iterations = 100;
  return ctx;
}
