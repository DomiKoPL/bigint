#ifndef FFT_H
#define FFT_H

#define T double

typedef struct complex
{
	T re, im;
} Complex;

Complex complex_constructor();

Complex complex_copy(Complex other);

Complex complex_mult(Complex a, Complex b);

Complex complex_add(Complex a, Complex b);

Complex complex_sub(Complex a, Complex b);

void fft_fft(Complex **A, int n, int dir);

void fft_mult(int *a, int alen, int *b, int blen, int **res, int *rlen, int MOD);

#endif //FFT_H