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

void fft_fw_rec(std::vector<std::complex<double>> &v, std::size_t n)
{
	std::size_t N, k;
	std::vector<std::complex<double>> v0, v1;

	N = 1 << n;
	if (N == 1)
		return;

	v0.resize(N / 2);
	v1.resize(N / 2);
	for (k = 0; k < N / 2; k++) {
		v0[k] = v[2 * k];
		v1[k] = v[2 * k + 1];
	}

	fft_fw_rec(v0, n-1);
	fft_fw_rec(v1, n-1);

	for (k = 0; k < N / 2; k++) {
		std::complex<double> tw;

		tw = std::polar(1., -2. * acos(-1) * k / N);

		v[k]         = v0[k] + tw * v1[k];
		v[k + N / 2] = v0[k] - tw * v1[k];
	}

	return;
}

void fft_bw_rec(std::vector<std::complex<double>> &v, std::size_t n)
{
	std::size_t N, k;
	std::vector<std::complex<double>> v0, v1;

	N = 1 << n;
	if (N == 1)
		return;

	v0.resize(N / 2);
	v1.resize(N / 2);
	for (k = 0; k < N / 2; k++) {
		v0[k] = v[2 * k];
		v1[k] = v[2 * k + 1];
	}

	fft_bw_rec(v0, n-1);
	fft_bw_rec(v1, n-1);

	for (k = 0; k < N / 2; k++) {
		std::complex<double> tw;

		tw = std::polar(1., 2. * acos(-1) * k / N);

		v[k]         = (v0[k] + tw * v1[k]) / 2.;
		v[k + N / 2] = (v0[k] - tw * v1[k]) / 2.;
	}

	return;
}
