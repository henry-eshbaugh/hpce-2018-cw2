#include "fourier_transform.hpp"

#include <cmath>
#include <cassert>

#include "tbb/parallel_for.h"

namespace hpce
{
	namespace he915
	{

class direct_fourier_transform_parfor_inner
	: public fourier_transform
{
protected:
	/*! We can do any size transform */
	virtual size_t calc_padded_size(size_t n) const
	{
		return n;
	}

	virtual void forwards_impl(
		size_t n,	const complex_t &wn,
		const complex_t *pIn,
		complex_t *pOut
	) const
	{
		assert(n>0);

		char *v = getenv("HPCE_DIRECT_INNER_K");
		unsigned int k = (unsigned int) atoi(v);

		const real_t PI2=2*3.1415926535897932384626433832795;

		// = -i*2*pi / n
		complex_t neg_im_2pi_n=-complex_t(0, 1)*PI2 / (real_t)n;

		// Fill the output array with zero
		std::fill(pOut, pOut+n, 0);

		for(size_t ii=0;ii<n;ii++){
			tbb::parallel_for(tbb::blocked_range<unsigned>((unsigned int)0u, (unsigned int)n, k), [&](const tbb::blocked_range<unsigned> &chunk){
				for (unsigned i = chunk.begin(); i != chunk.end(); i++) {
					pOut[i] += pIn[ii] * exp( neg_im_2pi_n * (double)i * (double)ii );
				}
			});
		}
	}

	virtual void backwards_impl(
		size_t n,	const complex_t &/*wn*/,
		const complex_t *pIn,
		complex_t *pOut
	) const
	{
		assert(n>0);

		char *v = getenv("HPCE_DIRECT_INNER_K");
		unsigned int k = (unsigned int) atoi(v);

		const real_t PI2=2*3.1415926535897932384626433832795;

		// = i*2*pi / n
		complex_t im_2pi_n=complex_t(0, 1)*PI2 / (real_t)n;
		const real_t scale=real_t(1)/n;

		// Fill the output array with zero
		std::fill(pOut, pOut+n, 0);

		for(size_t ii=0;ii<n;ii++){
			tbb::parallel_for(tbb::blocked_range<unsigned>((unsigned int)0u, (unsigned int)n, k), [&](const tbb::blocked_range<unsigned> &chunk){
				for (unsigned i = chunk.begin(); i != chunk.end(); i++)
					pOut[i] += pIn[ii] * exp( im_2pi_n * (double)i * (double)ii ) * scale;
			});
		};
	}

public:
	virtual std::string name() const
	{ return "hpce.he915.direct_fourier_transform_parfor_inner"; }

	virtual bool is_quadratic() const
	{ return true; }
};

std::shared_ptr<fourier_transform> Create_direct_fourier_transform_parfor_inner()
{
	return std::make_shared<direct_fourier_transform_parfor_inner>();
}
}; // namespace he915
}; // namespace hpce
