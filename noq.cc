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

#include <complex>
#include <iomanip>
#include <iostream>
#include <vector>

#include "lib.h"
#include "weather.h"

#ifdef TEST
int main(void)
{
	std::vector<std::complex<double>> v = {
		std::complex<double> (1., 2.),
		std::complex<double> (2., 1.),
		std::complex<double> (3., 4.),
		std::complex<double> (4., 3.),
		std::complex<double> (5., 6.),
		std::complex<double> (6., 5.),
		std::complex<double> (7., 8.),
		std::complex<double> (8., 7.),
	};

	std::cout << std::fixed << std::setprecision(1);

	std::cout << "Initial" << std::endl;
	for (std::complex<double> e: v) {
		std::cout << e << std::endl;
	}

	fft_fw_rec(v);

	std::cout << "Forward - Recursive" << std::endl;
	for (std::complex<double> e: v) {
		std::cout << e << std::endl;
	}

	fft_bw_rec(v);

	std::cout << "Backward - Recursive" << std::endl;
	for (std::complex<double> e: v) {
		std::cout << e << std::endl;
	}

	fft_fw_inp(v);

	std::cout << "Forward - In-place" << std::endl;
	for (std::complex<double> e: v) {
		std::cout << e << std::endl;
	}

	fft_bw_inp(v);

	std::cout << "Backward - In-place" << std::endl;
	for (std::complex<double> e: v) {
		std::cout << e << std::endl;
	}

	fft_fw_par(v);

	std::cout << "Forward - Parallel" << std::endl;
	for (std::complex<double> e: v) {
		std::cout << e << std::endl;
	}

	fft_bw_par(v);

	std::cout << "Backward - Parallel" << std::endl;
	for (std::complex<double> e: v) {
		std::cout << e << std::endl;
	}

	return 0;
}

#else /* ! TEST */
int main(void)
{
	std::vector<int> transformed;
	std::size_t M, N, n, K;

	M = weather.size();
	n = lg(M);
	N = 1 << n;
	K = 8000;

	std::cout << "=== Weather Data ===" << std::endl;
	std::cout << "Size: " << M << std::endl;
	std::cout << "Padded: " << N << std::endl;
	std::cout << std::endl;

	std::cout << "=== Approximation ===" << std::endl;
	std::cout << "Keep: " << K << " / " << N << std::endl;

	transformed = compress(weather, K);
	diff(weather, transformed);

	std::cout << "Samples:" << std::endl;
	for (int i = 0; i < 8; i++)
		std::cout << "\t" << weather[i]
			<< "\t" << transformed[i] << std::endl;
	std::cout << std::endl;

	std::cout << "=== Benchmark ===" << std::endl;

	benchmark(weather);

	return 0;
}
#endif /* TEST */
