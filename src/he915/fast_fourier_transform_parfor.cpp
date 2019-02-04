#include "fourier_transform.hpp"

#include <cmath>
#include <cassert>

#include "tbb/parallel_for.h"

static unsigned loopk;

namespace hpce
{
namespace he915 {
class fast_fourier_transform_parfor
	: public fourier_transform
{
protected:
	/* Standard radix-2 FFT only supports binary power lengths */
	virtual size_t calc_padded_size(size_t n) const
	{
		assert(n!=0);

		size_t ret=1;
		while(ret<n){
			ret<<=1;
		}

		return ret;
	}

	virtual void recurse(
		size_t n,	const complex_t &wn,
		const complex_t *pIn, size_t sIn,
		complex_t *pOut, size_t sOut
	) const
	{
		assert(n>0);

		if (n == 1){
			pOut[0] = pIn[0];
		}else if (n == 2){
			pOut[0] = pIn[0]+pIn[sIn];
			pOut[sOut] = pIn[0]-pIn[sIn];
		}else{
			size_t m = n/2;

			recurse(m,wn*wn,pIn,2*sIn,pOut,sOut);
			recurse(m,wn*wn,pIn+sIn,2*sIn,pOut+sOut*m,sOut);

			complex_t w=complex_t(1, 0);

			if (m <= loopk)
			  for (size_t j=0;j<m;j++){
			    complex_t t1 = w*pOut[m+j];
			    complex_t t2 = pOut[j]-t1;
			    pOut[j] = pOut[j]+t1;                 /*  pOut[j] = pOut[j] + w^i pOut[m+j] */
			    pOut[j+m] = t2;                          /*  pOut[j] = pOut[j] - w^i pOut[m+j] */
			    w = w*wn;
			  }
			else
			  tbb::parallel_for(tbb::blocked_range<unsigned>(0u, (unsigned)m, loopk), [&](const tbb::blocked_range<unsigned> chunk){
			  	for (unsigned i = chunk.begin(); i != chunk.end(); i++) {
					complex_t t1 = pow(wn, m+i) * pOut[m+i];
					complex_t t2 = pOut[i] - t1;
					pOut[i] = pOut[i] + t1;
					pOut[i+m] = t2;
				}
			  });
		}
	}

	virtual void forwards_impl(
		size_t n,	const complex_t &wn,
		const complex_t *pIn,
		complex_t *pOut
	) const
	{
		assert(n>0);
		char *v = getenv("HPCE_FFT_LOOP_K");
		if (!v) loopk = 32u;
		else loopk = (unsigned) atoi(v);

		recurse(n,wn,pIn,1,pOut,1);
	}

	virtual void backwards_impl(
		size_t n,	const complex_t &wn,
		const complex_t *pIn,
		complex_t *pOut
	) const
	{
		complex_t reverse_wn=real_t(1)/wn;
		recurse(n, reverse_wn, pIn, 1, pOut, 1);
		
		char *v = getenv("HPCE_FFT_LOOP_K");
		if (!v) loopk = 32u;
		else loopk = (unsigned) atoi(v);

		real_t scale=real_t(1)/n;
		for(size_t i=0;i<n;i++){
			pOut[i]=pOut[i]*scale;
		}
	}

public:
	virtual std::string name() const
	{ return "hpce.he915.fast_fourier_transform_parfor"; }

	virtual bool is_quadratic() const
	{ return false; }
};

std::shared_ptr<fourier_transform> Create_fast_fourier_transform_parfor()
{
	return std::make_shared<fast_fourier_transform_parfor>();
}
}; // namespace he915
}; // namespace hpce
