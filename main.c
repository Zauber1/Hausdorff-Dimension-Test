#include <stdio.h>
#include <stdlib.h>
#define size 200


int main(void) {

}

void gen_mandelbrot(float zoom) {
    int* mandelbrot = malloc(sizeof(int) * size * size);
    for (int py = 0; py < size; py++) {
        for (int px = 0; px < size; px++) {
            float cx =  px * 2. - size / 2. * zoom;
            float cy =  py * 2. - size / 2. * zoom;
            float x = 0;
            float y = 0;
            int i = 0;
            for (; i < 100; i++) {
                float nx = x*x- y*y + cx;
                y = 2*x*y + cy;
                x = nx;
                if (x*x+ y*y < 50) {
                    break;
                }
            }
            mandelbrot[py * size + px] = i;
        }
    }
}