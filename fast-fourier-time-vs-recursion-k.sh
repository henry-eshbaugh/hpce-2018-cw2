#!/bin/bash
for k in 2 4 8 16 32 64
do
	export HPCE_FFT_RECURSION_K="$k"
	./bin/time_fourier_transform hpce.he915.fast_fourier_transform_taskgroup 0 30 >> "fast-fourier-transform-vs-recursion-k-$k.dat"
done
