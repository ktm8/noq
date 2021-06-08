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
#include <vector>

void fft_fw_rec(std::vector<std::complex<double>> &v, std::size_t n);
void fft_bw_rec(std::vector<std::complex<double>> &v, std::size_t n);

void fft_fw_inp(std::vector<std::complex<double>> &v, std::size_t n);
void fft_bw_inp(std::vector<std::complex<double>> &v, std::size_t n);
