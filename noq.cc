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

int main(void)
{
	std::vector<std::complex<double>> v = {
		std::complex<double> (1., 2.),
		std::complex<double> (3., 4.),
		std::complex<double> (5., 6.),
		std::complex<double> (7., 8.),
	};

	std::cout << std::fixed << std::setprecision(1);

	std::cout << "Initial" << std::endl;
	for (std::complex<double> e: v) {
		std::cout << e << std::endl;
	}

	fft_fw_rec(v, 2);

	std::cout << "Forward" << std::endl;
	for (std::complex<double> e: v) {
		std::cout << e << std::endl;
	}

	fft_bw_rec(v, 2);

	std::cout << "Backward" << std::endl;
	for (std::complex<double> e: v) {
		std::cout << e << std::endl;
	}

	return 0;
}
