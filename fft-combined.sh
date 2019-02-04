#!/bin/bash
# case 1
export HPCE_FFT_LOOP_K=1
export HPCE_FFT_RECURSION_K=1
./bin/time_fourier_transform hpce.he915.fast_fourier_transform_combined 0 30 > results/fft-comb-case1.dat
# case 2
export HPCE_FFT_LOOP_K=16
export HPCE_FFT_RECURSION_K=1
./bin/time_fourier_transform hpce.he915.fast_fourier_transform_combined 0 30 > results/fft-comb-case2.dat
# case 3
export HPCE_FFT_LOOP_K=1
export HPCE_FFT_RECURSION_K=32
./bin/time_fourier_transform hpce.he915.fast_fourier_transform_combined 0 30 > results/fft-comb-case3.dat
# case 4
export HPCE_FFT_LOOP_K=16
export HPCE_FFT_RECURSION_K=32
./bin/time_fourier_transform hpce.he915.fast_fourier_transform_combined 0 30 > results/fft-comb-case4.dat
