#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define size 200
#define grid_size 0.5
#define outline_Start 10
#define outline_End 22
float get_dimentions(int* normSize , int* doubleSize);
int* gen_mandelbrot(float zoom);
int main(void) {
    int *mandelbrotnormalSize = gen_mandelbrot(1);
    int *mandelbrotDoubleSize = gen_mandelbrot(0.5);
    float dimention = get_dimentions(mandelbrotnormalSize, mandelbrotDoubleSize);
    printf("dimention: %f\n", dimention);
    free(mandelbrotnormalSize),free(mandelbrotDoubleSize);
}
int* gen_mandelbrot(float zoom) {
    int* mandelbrot = malloc(sizeof(int) * size * size);
    for (int py = 0; py < size; py++) {
        for (int px = 0; px < size; px++) {
            float cx = (px - size / 2.0) / (size / 4.0) * zoom;
            float cy = (py - size / 2.0) / (size / 4.0) * zoom;
            float x = 0;
            float y = 0;
            int i = 0;
            for (; i < 1000; i++) {
                float nx = x*x- y*y + cx;
                y = 2*x*y + cy;
                x = nx;
                if (x*x+ y*y > 10.0f) {
                    break;
                }
            }
            mandelbrot[py * size + px] = i;
        }
    }
    return mandelbrot;
}
float get_dimentions(int* normSize , int* doubleSize) {
    int grid_box_size = ceil(size/grid_size);
    int* grid = malloc(sizeof(int) * grid_box_size * grid_box_size);
    for (int py = 0; py < grid_box_size; py++) {
        for (int px = 0; px < grid_box_size; px++) {
            grid[py * grid_box_size + px] = 0;
        }
    }
    int num_touting_grid = 0;
    for (int px = 0; px < size; px++) {
        for (int py = 0; py < size; py++) {
            const int touching_grid = (int)ceil(px / grid_size) * grid_box_size + (int)ceil(py / grid_size);
            int num = normSize[px * size + py];
            if (num > outline_Start && num < outline_End) {
                if ( grid[touching_grid] == 0) {
                    grid[touching_grid] = 1;
                    num_touting_grid++;
                }
                printf("#");

            }else {
                printf(" ");
            }
        }
        printf("\n");
    }
    for (int py = 0; py < grid_box_size; py++) {
        for (int px = 0; px < grid_box_size; px++) {
            grid[py * grid_box_size + px] = 0;
        }
    }
    int num_touting_grid2 = 0;
    for (int px = 0; px < size; px++) {
        for (int py = 0; py < size; py++) {
            const int touching_grid = (int)ceil(px / grid_size) * grid_box_size + (int)ceil(py / grid_size);
            int num = doubleSize[px * size + py];
            if (num > outline_Start && num < outline_End) {
                if (grid[touching_grid] == 0) {
                    grid[touching_grid] = 1;
                    num_touting_grid2++;
                }
                printf("#");

            }else {
                printf(" ");
            }

        }
        printf("\n");
    }
    free(grid);
    return  (float)num_touting_grid2 / (float)num_touting_grid ;
}

