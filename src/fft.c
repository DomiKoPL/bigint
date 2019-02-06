////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "fft.h"
#include <math.h>
#include <stdlib.h>

Complex complex_constructor()
{
	Complex res;
	res.re = 0;
	res.im = 0;
	return res;
}

Complex complex_copy(Complex other)
{
	Complex res = complex_constructor();
	res.re = other.re;
	res.im = other.re;
	return res;
}

Complex complex_mult(Complex a, Complex b)
{
	Complex res = complex_constructor();

	res.re = a.re * b.re - a.im * b.im;
	res.im = a.im * b.re + a.re * b.im;

	return res;
}

Complex complex_add(Complex a, Complex b)
{
	Complex res;

	res.re = a.re + b.re;
	res.im = a.im + b.im;

	return res;
}

Complex complex_sub(Complex a, Complex b)
{
	Complex res;

	res.re = a.re - b.re;
	res.im = a.im - b.im;

	return res;
}

#define M_PI 3.14159265358979323846

void fft_fft(Complex **A, int n, int dir)
{	
	Complex *a = *A;
	for (int i = 0, j = 0; i < n; i++)
	{
		if (i > j)
		{
			Complex c = a[i];
			a[i] = a[j];
			a[j] = c;
		}

		for (int k = n >> 1; (j ^= k) < k; k >>= 1);
	}

	for (int p = 2; p <= n; p <<= 1)
	{
		Complex wn = complex_constructor();
		wn.re = cos(2.0 * dir * M_PI / p);
		wn.im = sin(2.0 * dir * M_PI / p);

		for (int k = 0; k < n; k += p)
		{
			Complex w = complex_constructor();
			w.re = 1;

			for (int j = 0; j < (p >> 1); j++)
			{
				Complex xx = a[k + j];
				Complex yy = complex_mult(w, a[k + j + (p >> 1)]);
				a[k + j] = complex_add(xx, yy);
				a[k + j + (p >> 1)] = complex_sub(xx, yy);
				w = complex_mult(w, wn);
			}
		}
	}	
}

void fft_mult(int *a, int alen, int *b, int blen, int **res, int *rlen, int MOD)
{
	int n = (alen > blen ? alen : blen), p = 2;
	while ((p >> 1) < n) p <<= 1;
	Complex *fa = (Complex *)malloc(p * sizeof(Complex));

	for (int i = 0; i < p; i++) fa[i].re = fa[i].im = 0;
	for (int i = 0; i < alen; i++) fa[i].re += a[i];
	for (int i = 0; i < blen; i++) fa[i].im += b[i];

	fft_fft(&fa, p, 1);

	for (int i = 0; i <= p / 2; i++)
	{
		Complex bp = fa[i];
		bp.re += fa[p - i == p ? 0 : p - i].re;
		bp.im -= fa[p - i == p ? 0 : p - i].im;

		Complex _q = fa[p - i == p ? 0 : p - i];
		_q.re -= fa[i].re;
		_q.im += fa[i].im;

		Complex q;
		q.re = _q.im;
		q.im = _q.re;

		Complex temp;
		temp.re = 0.25;
		temp.im = 0;
		fa[i] = complex_mult(bp, q);
		fa[i] = complex_mult(fa[i], temp);

		if (i > 0)
		{
			fa[p - i].re = fa[i].re;
			fa[p - i].im = -fa[i].im;
		}
	}

	fft_fft(&fa, p, -1);

	*rlen = alen + blen - 1;
	*res = (int*)malloc(*rlen * sizeof(int));
	
	long long carry = 0;
	for (int i = 0; i < *rlen; i++)
	{
		carry += round(fa[i].re / p);
		(*res)[i] = carry % MOD;
		carry /= MOD;
	}

	while(carry > 0)
	{
		int *copy = (int*)malloc(*rlen * sizeof(int));
		for(int i = 0; i < *rlen; i++) copy[i] = (*res)[i];

		(*rlen)++;
		(*res) = (int*)malloc(*rlen * sizeof(int));
		for(int i = 0 ; i < *rlen - 1; i++) (*res)[i] = copy[i];
		(*res)[*rlen - 1] = carry % MOD;
		carry /= MOD;
	}
}