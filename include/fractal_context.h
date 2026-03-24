#ifndef FRACTAL_CONTEXT_H
#define FRACTAL_CONTEXT_H
#include "canvas.h"
#include "complex_coord.h"
#include <stdlib.h>

typedef struct Context {
  long double real_min;
  long double real_max;
  long double imaginary_min;
  long double imaginary_max;
  int max_iterations;
} context_t;

context_t *context_create();

void context_destroy(context_t *ctx);

c_coord_t grid_coord_to_complex_coord(canvas_t *c, context_t *ctx, size_t x,
                                      size_t y);

int iterative_escape(context_t *ctx, c_coord_t coord);

pixel_t pixel_to_draw(context_t *ctx, int iterations);

context_t *init_mandelbrot(context_t *ctx);

#endif
