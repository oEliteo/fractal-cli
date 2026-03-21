#include "../include/canvas.h"
#include "../include/fractal_context.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void restore_terminal();
static void redraw(canvas_t *c, context_t *ctx);
static struct termios orig_termios;

int main() {
  // Register Cleanup Function
  atexit(restore_terminal);
  // Initial Fractal Context + Render
  canvas_t *c = canvas_create(160, 50);
  context_t *ctx = context_create();
  redraw(c, ctx);

  // Modify Terminal Settings To Allow For Interactions
  tcgetattr(STDIN_FILENO, &orig_termios);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

  // Begin Interactive Loop
  char input_char;
  int changed = 0;
  double pan_distance;
  double zoom_distance;
  double center;
  while (1) {
    if (changed == 0) {
      if (read(STDIN_FILENO, &input_char, 1) == 1) {
        // Exit The Program
        if (input_char == 'q') {
          break;
        }
        // Pan Left
        if (input_char == 'h') {
          pan_distance = (ctx->real_max - ctx->real_min) * 0.1;
          ctx->real_max = ctx->real_max - pan_distance;
          ctx->real_min = ctx->real_min - pan_distance;
          changed = 1;
        }
        // Pan Right
        if (input_char == 'l') {
          pan_distance = (ctx->real_max - ctx->real_min) * 0.1;
          ctx->real_max = ctx->real_max + pan_distance;
          ctx->real_min = ctx->real_min + pan_distance;
          changed = 1;
        }
        // Pan Up
        if (input_char == 'k') {
          pan_distance = (ctx->imaginary_max - ctx->imaginary_min) * 0.1;
          ctx->imaginary_max = ctx->imaginary_max - pan_distance;
          ctx->imaginary_min = ctx->imaginary_min - pan_distance;
          changed = 1;
        }
        // Pan Down
        if (input_char == 'j') {
          pan_distance = (ctx->imaginary_max - ctx->imaginary_min) * 0.1;
          ctx->imaginary_max = ctx->imaginary_max + pan_distance;
          ctx->imaginary_min = ctx->imaginary_min + pan_distance;
          changed = 1;
        }

        // Zoom In
        if (input_char == 'i') {
          // Zoom real axis
          center = (ctx->real_max + ctx->real_min) / 2.0;
          zoom_distance = (ctx->real_max - ctx->real_min) * 0.9;
          ctx->real_max = center + (zoom_distance / 2.0);
          ctx->real_min = center - (zoom_distance / 2.0);
          // Zoom Imaginary axis
          center = (ctx->imaginary_max + ctx->imaginary_min) / 2.0;
          zoom_distance = (ctx->imaginary_max - ctx->imaginary_min) * 0.9;
          ctx->imaginary_max = center + (zoom_distance / 2.0);
          ctx->imaginary_min = center - (zoom_distance / 2.0);
          changed = 1;
        }

        // Zoom Out
        if (input_char == 'o') {
          // Zoom real axis
          center = (ctx->real_max + ctx->real_min) / 2.0;
          zoom_distance = (ctx->real_max - ctx->real_min) * 1.1;
          ctx->real_max = center + (zoom_distance / 2.0);
          ctx->real_min = center - (zoom_distance / 2.0);
          // Zoom Imaginary axis
          center = (ctx->imaginary_max + ctx->imaginary_min) / 2.0;
          zoom_distance = (ctx->imaginary_max - ctx->imaginary_min) * 1.1;
          ctx->imaginary_max = center + (zoom_distance / 2.0);
          ctx->imaginary_min = center - (zoom_distance / 2.0);
          changed = 1;
        }
        // Decrease Precision (Faster)
        if (input_char == '[') {
          ctx->max_iterations = ctx->max_iterations - 5;
          if (ctx->max_iterations < 1) {
            ctx->max_iterations = 1;
          }
          changed = 1;
        }

        // Increase Precision (Slower but more detail)
        if (input_char == ']') {
          ctx->max_iterations = ctx->max_iterations + 5;
          if (ctx->max_iterations > 5000) {
            ctx->max_iterations = 5000;
          }
          changed = 1;
        }
      }
    }
    if (changed) {
      printf("\x1b[H");
      redraw(c, ctx);
      changed = 0;
    }
  }
  // Restore Terminal Settings & Cleanup Canvas In Memory.
  restore_terminal();
  canvas_destroy(c);
  return 0;
}

void redraw(canvas_t *c, context_t *ctx) {
  for (size_t i = 0; i < c->height; i++) {
    for (size_t j = 0; j < c->width; j++) {
      c_coord_t complex_coord = grid_coord_to_complex_coord(c, ctx, j, i);
      int iterations = iterative_escape(ctx, complex_coord);
      pixel_t pixel = pixel_to_draw(ctx, iterations);
      canvas_set_pixel(c, j, i, pixel);
    }
  }
  canvas_draw(c);
  printf("Controls: Pan Left: 'h' | Pan Right: 'l' | Pan Up: 'k' | Pan Down: "
         "'j' | Zoom In:  'i' | Zoom Out:  'o' | Precision Up: ']' | Precision "
         "Down: '[' | Quit: 'q'\n");
  return;
}

void restore_terminal() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); }
