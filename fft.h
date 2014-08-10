#ifndef _FFT_H_
#define _FFT_H_

/**
 * Operating environment Processing
 * the FFT code 
 * wirte time : 2013.5.23
 */
#define NUM  128
#define H_NUM NUM/2
// log2(N)
#define SERIES 7

typedef struct {
    float real;
    float imag;
} Complex;

extern Complex data[NUM];

//The complex's imaginary part is set to zero
void imagZero ();
void addComplex(Complex *getResult, Complex *A, Complex *withB);
void subComplex(Complex *getResult, Complex *A, Complex *withB);
void mulComplex(Complex *getResult, Complex *A, Complex *withB);
//input sample array, # of points
void transform();
//bit reversal for resequencing data
//Rader algorithm
//Input reverse
void inReverse ();
void FFT();

#endif