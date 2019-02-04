#!/bin/bash
for k in $(seq 1 16)
do
	export HPCE_DIRECT_INNER_K="$k"
	./bin/time_fourier_transform hpce.he915.direct_fourier_transform_parfor_inner 0 30 >> direct-inner-vs-k.dat
done
