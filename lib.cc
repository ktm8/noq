/*
   Copyright (C) 2021 Minh Khoa Tran

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */

#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

#include "lib.h"

std::size_t lg(std::size_t N)
{
	std::size_t n;

	n = 0;
	while ((std::size_t) (1 << n) < N)
		n += 1;

	return n;
}

std::vector<std::complex<double>> pad(std::vector<int> v)
{
	std::vector<std::complex<double>> res;
	std::size_t M, N, n, k;

	M = v.size();
	n = lg(M);
	N = 1 << n;

	res.resize(N);
	for (k = 0; k < N; k++) {
		std::complex<double> e;

		if (k < M)
			e = std::complex<double> (v[k], 0);
		else
			e = std::complex<double> (0, 0);

		res[k] = e;
	}

	return res;
}

std::vector<int> compress(std::vector<int> v, std::size_t K)
{
	std::vector<int> res;
	std::vector<std::complex<double>> dat;
	std::size_t M, N, k;

	M   = v.size();
	dat = pad(v);
	N   = dat.size();

	fft_fw_inp(dat);

	/* DEBUG */
	double foo = 0;
	for (k = 0; k < N; k++) {
		foo += norm(dat[k]);
	}
	std::cout << "DEBUG: Avg norm = " << foo / N << std::endl;
	/* END */

	for (k = K; k < N; k++)
		dat[k] = std::complex<double> (0, 0);

	fft_bw_inp(dat);

	res.resize(M);
	for (k = 0; k < M; k++)
		res[k] = dat[k].real();

	return res;
}

void diff(std::vector<int> v1, std::vector<int> v2)
{
	std::size_t N, k;
	int total, max_d;

	N = v1.size();
	if (v2.size() != N)
		return;

	total = 0;
	max_d = 0;
	for (k = 0; k < N; k++) {
		int d = abs(v1[k] - v2[k]);

		total += d;
		max_d  = std::max<int>(max_d, d);
	}

	std::cout << "Differences: " << std::endl;
	std::cout << "\tAverage: " << (double) total / N << std::endl;
	std::cout << "\tMaximum: " << max_d << std::endl;

	return;
}

void fft_fw_rec(std::vector<std::complex<double>> &v)
{
	std::size_t N, k;
	std::vector<std::complex<double>> v0, v1;

	N = v.size();
	if (N == 1)
		return;

	v0.resize(N / 2);
	v1.resize(N / 2);
	for (k = 0; k < N / 2; k++) {
		v0[k] = v[2 * k];
		v1[k] = v[2 * k + 1];
	}

	fft_fw_rec(v0);
	fft_fw_rec(v1);

	for (k = 0; k < N / 2; k++) {
		std::complex<double> tw;

		tw = std::polar(1., -2. * acos(-1) * k / N);

		v[k]         = v0[k] + tw * v1[k];
		v[k + N / 2] = v0[k] - tw * v1[k];
	}

	return;
}

void fft_bw_rec(std::vector<std::complex<double>> &v)
{
	std::size_t N, k;
	std::vector<std::complex<double>> v0, v1;

	N = v.size();
	if (N == 1)
		return;

	v0.resize(N / 2);
	v1.resize(N / 2);
	for (k = 0; k < N / 2; k++) {
		v0[k] = v[2 * k];
		v1[k] = v[2 * k + 1];
	}

	fft_bw_rec(v0);
	fft_bw_rec(v1);

	for (k = 0; k < N / 2; k++) {
		std::complex<double> tw;

		tw = std::polar(1., 2. * acos(-1) * k / N);

		v[k]         = (v0[k] + tw * v1[k]) / 2.;
		v[k + N / 2] = (v0[k] - tw * v1[k]) / 2.;
	}

	return;
}

/*
 * Fast Bit-Reversal Algorithms - Anne Cathrine Elster, Cornell University
 * https://folk.idi.ntnu.no/elster/pubs/elster-bit-rev-1989.pdf
 */

void fft_fw_inp(std::vector<std::complex<double>> &v)
{
	std::size_t N, L, s, k;
	std::vector<std::size_t> brp;

	N = v.size();
	if (N == 1)
		return;

	brp.resize(N);
	brp[0] = 0;
	brp[1] = N / 2;
	for (k = 1; k < N / 2; k++) {
		brp[2 * k]     = brp[k] / 2;
		brp[2 * k + 1] = brp[2 * k] + N / 2;
	}

	for (std::size_t i = 0; i < N; i++) {
		if (i < brp[i])
			std::swap(v[i], v[brp[i]]);
	}

	for (L = 2; L <= N; L *= 2) for (s = 0; s < N; s += L) {
		for (k = 0; k < L / 2; k++) {
			std::complex<double> tx, ty, tw;

			tx = v[s + k];
			ty = v[s + k + L / 2];
			tw = std::polar(1., -2. * acos(-1) * k / L);

			v[s + k]         = tx + tw * ty;
			v[s + k + L / 2] = tx - tw * ty;
		}
	}
}

void fft_bw_inp(std::vector<std::complex<double>> &v)
{
	std::size_t N, L, s, k;
	std::vector<std::size_t> brp;

	N = v.size();
	if (N == 1)
		return;

	brp.resize(N);
	brp[0] = 0;
	brp[1] = N / 2;
	for (std::size_t i = 1; i < N / 2; i++) {
		brp[2 * i]     = brp[i] / 2;
		brp[2 * i + 1] = brp[2 * i] + N / 2;
	}

	for (std::size_t i = 0; i < N; i++) {
		if (i < brp[i])
			std::swap(v[i], v[brp[i]]);
	}

	for (L = 2; L <= N; L *= 2) for (s = 0; s < N; s += L) {
		for (k = 0; k < L / 2; k++) {
			std::complex<double> tx, ty, tw;

			tx = v[s + k];
			ty = v[s + k + L / 2];
			tw = std::polar(1., 2. * acos(-1) * k / L);

			v[s + k]         = (tx + tw * ty) / 2.;
			v[s + k + L / 2] = (tx - tw * ty) / 2.;
		}
	}
}
