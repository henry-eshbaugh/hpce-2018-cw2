#include "fourier_transform.hpp"

namespace hpce{

// Declare factory functions which are implemented elsewhere.
std::shared_ptr<fourier_transform> Create_fast_fourier_transform();
std::shared_ptr<fourier_transform> Create_direct_fourier_transform();

// TODO : Declare your factories here

namespace he915 {
	std::shared_ptr<fourier_transform> Create_direct_fourier_transform_parfor_inner();
	std::shared_ptr<fourier_transform> Create_direct_fourier_transform_parfor_outer();
	std::shared_ptr<fourier_transform> Create_fast_fourier_transform_taskgroup();
	std::shared_ptr<fourier_transform> Create_fast_fourier_transform_parfor();
	std::shared_ptr<fourier_transform> Create_fast_fourier_transform_combined();
}


void fourier_transform::RegisterDefaultFactories()
{
	static const unsigned MYSTERIOUS_LINE=0; // Don't remove me!

	RegisterTransformFactory("hpce.fast_fourier_transform", Create_fast_fourier_transform);
	RegisterTransformFactory("hpce.direct_fourier_transform", Create_direct_fourier_transform);

	// TODO : Add your factories here
	RegisterTransformFactory("hpce.he915.direct_fourier_transform_parfor_inner", hpce::he915::Create_direct_fourier_transform_parfor_inner);
	RegisterTransformFactory("hpce.he915.direct_fourier_transform_parfor_outer", hpce::he915::Create_direct_fourier_transform_parfor_inner);
	RegisterTransformFactory("hpce.he915.fast_fourier_transform_taskgroup", hpce::he915::Create_fast_fourier_transform_taskgroup);
	RegisterTransformFactory("hpce.he915.fast_fourier_transform_parfor", hpce::he915::Create_fast_fourier_transform_parfor);
	RegisterTransformFactory("hpce.he915.fast_fourier_transform_combined", hpce::he915::Create_fast_fourier_transform_combined);
}

}; // namespace hpce
