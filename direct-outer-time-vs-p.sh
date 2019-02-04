#!/bin/bash
export HPCE_DIRECT_INNER_K="8"
./bin/time_fourier_transform hpce.he915.direct_fourier_transform_parfor_outer 1 30 > direct-outer-vs-p-1.dat
./bin/time_fourier_transform hpce.he915.direct_fourier_transform_parfor_outer 2 30 > direct-outer-vs-p-2.dat
./bin/time_fourier_transform hpce.he915.direct_fourier_transform_parfor_outer 3 30 > direct-outer-vs-p-3.dat
./bin/time_fourier_transform hpce.he915.direct_fourier_transform_parfor_outer 4 30 > direct-outer-vs-p-4.dat
./bin/time_fourier_transform hpce.he915.direct_fourier_transform_parfor_outer 5 30 > direct-outer-vs-p-5.dat
./bin/time_fourier_transform hpce.he915.direct_fourier_transform_parfor_outer 6 30 > direct-outer-vs-p-6.dat
./bin/time_fourier_transform hpce.he915.direct_fourier_transform_parfor_outer 7 30 > direct-outer-vs-p-7.dat
./bin/time_fourier_transform hpce.he915.direct_fourier_transform_parfor_outer 8 30 > direct-outer-vs-p-8.dat
