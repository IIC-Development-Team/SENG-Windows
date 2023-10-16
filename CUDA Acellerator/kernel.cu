#include "kernel.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

namespace EXT_CUDA
{
	bool IsCudaCapable()
	{
		return cudaSetDevice(0) == cudaSuccess;
	}
}