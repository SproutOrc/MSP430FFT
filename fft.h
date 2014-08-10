#ifndef _FFT_H_
#define _FFT_H_

/**
 * Operating environment Processing
 * the FFT code 
 * wirte time : 2013.5.23
 */
typedef struct {
    float real;
    float imag;
} Complex;

void FFT(Complex *data, Complex const *factor, int num, int series);
#endif