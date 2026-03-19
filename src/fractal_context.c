#include "../include/fractal_context.h"
#include "../include/complex_coord.h"
#include <string.h>

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
  double real_x = (double)x / ((double)(c->width - 1.0));
  real_x = (real_x * (ctx->real_max - ctx->real_min));
  real_x = real_x + ctx->real_min;
  double imaginary_y = (double)y / ((double)(c->height - 1.0));
  imaginary_y = (imaginary_y * (ctx->imaginary_max - ctx->imaginary_min));
  imaginary_y = imaginary_y + ctx->imaginary_min;

  c_coord_t coord;
  coord.imaginary = imaginary_y;
  coord.real = real_x;
  return coord;
}

int iterative_escape(context_t *ctx, c_coord_t coord) {
  double z_real = 0.0;
  double z_imaginary = 0.0;
  int iterations = 0;

  while (iterations < ctx->max_iterations) {
    double new_real = (z_real * z_real) - (z_imaginary * z_imaginary);
    double new_imaginary = 2 * z_real * z_imaginary;
    z_real = new_real + coord.real;
    z_imaginary = new_imaginary + coord.imaginary;

    if ((z_real * z_real) + (z_imaginary * z_imaginary) > 4.0) {
      break;
    }
    iterations += 1;
  }
  return iterations;
}

char ascii_character_to_draw(context_t *ctx, int iterations) {
  const char *characters = " .:-=+*#%$@";
  char ascii = '#';
  if (iterations == ctx->max_iterations) {
    iterations = iterations - 1;
  }
  int index = (iterations * (strlen(characters) - 1)) / ctx->max_iterations;
  ascii = characters[index];
  return ascii;
}

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
