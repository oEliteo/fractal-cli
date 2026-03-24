#include "../include/fractal_context.h"
#include "../include/canvas.h"
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
  long double real_x = (long double)x / ((long double)(c->width - 1.0));
  real_x = (real_x * (ctx->real_max - ctx->real_min));
  real_x = real_x + ctx->real_min;
  long double imaginary_y = (long double)y / ((long double)(c->height - 1.0));
  imaginary_y = (imaginary_y * (ctx->imaginary_max - ctx->imaginary_min));
  imaginary_y = imaginary_y + ctx->imaginary_min;

  c_coord_t coord;
  coord.imaginary = imaginary_y;
  coord.real = real_x;
  return coord;
}

int iterative_escape(context_t *ctx, c_coord_t coord) {
  long double z_real = 0.0;
  long double z_imaginary = 0.0;
  int iterations = 0;

  while (iterations < ctx->max_iterations) {
    long double new_real = (z_real * z_real) - (z_imaginary * z_imaginary);
    long double new_imaginary = 2 * z_real * z_imaginary;
    z_real = new_real + coord.real;
    z_imaginary = new_imaginary + coord.imaginary;

    if ((z_real * z_real) + (z_imaginary * z_imaginary) > 4.0) {
      break;
    }
    iterations += 1;
  }
  return iterations;
}

pixel_t pixel_to_draw(context_t *ctx, int iterations) {
  const pixel_t pixelPalette[11] = {
      {'.', 30, 30, 46},    {':', 88, 91, 112},   {'-', 147, 153, 178},
      {'=', 180, 190, 254}, {'@', 137, 180, 250}, {' ', 30, 30, 46},
      {'@', 137, 180, 250}, {'=', 180, 190, 254}, {'-', 147, 153, 178},
      {':', 88, 91, 112},   {'.', 30, 30, 46},
  };
  pixel_t pixel;
  int index =
      (iterations * (sizeof(pixelPalette) / sizeof(pixelPalette[0]) - 1)) /
      ctx->max_iterations;
  pixel = pixelPalette[index];
  return pixel;
}

context_t *init_mandelbrot(context_t *ctx) {
  if (ctx == NULL)
    return NULL;
  ctx->real_min = -2.0;
  ctx->real_max = 1.0;
  ctx->imaginary_min = -1.0;
  ctx->imaginary_max = 1.0;
  ctx->max_iterations = 15;
  return ctx;
}
