# fractal-cli
A CLI/TUI Application that generates ASCII fractals. Inspired by a C++ project I wrote in college.

# Usage
1. git clone the repository
2. run: make
3. run: ./bin/fractal-cli
4. use listed controls to explore a mandelbrot fractal inside your terminal!

# Features
* Pan the view with vim motions 'h' 'j' 'k' 'l'
* Zoom into details with 'i' and out with 'o'
* Adjust maximum iterations with '\[' and '\]' to increase the details (higher precision may take longer to render)
* Exit the program by pressing 'q'

# Work in progress features
* allow users to choose their terminal width / height to accommodate for different screens
* allow users to pick from multiple color palettes
* allow user to save their current fractal context to a ppm file and upscale it from the terminals low resolution render to a higher resolution for better image quality
* allow the ascii fractal to be copied to the clipboard
* allow multiple fractal images to be saved in a session to create animations of fractal zooms with tools like ffmpeg.

# Known Issues
* At certain levels of zoom the math begins to breakdown (likely due to floating point precision) causing
  large blobs of ascii that remain unchanging even after attempting to zoom back out, or alter maximum iteration count.
