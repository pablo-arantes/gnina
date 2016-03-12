/*
 * Header file for gpu code.
 */

#ifndef __GPUCODE_H
#define __GPUCODE_H
//everything is guarded by SMINA_GPU
// CUDA runtime
#include <cuda_runtime.h>
#include <vector>

struct GPUSplineInfo
{
	unsigned n; //number of components
	float **splines; //pointer to spline data in device memory, size is number of components
	float fraction; //how spline is binned
	float cutoff; //where to stop

	GPUSplineInfo(): n(0), splines(NULL), fraction(0), cutoff(0) {}
};

struct GPUNonCacheInfo
{
	unsigned natoms, nrecatoms;
	float cutoff_sq;
	//device pointers for ligand data
	float *coords; //3*n - this is the only thing that actually changes
	float *charges; //n
	unsigned *types; //n
	float *minus_forces; //3*n
	float *energies; //per atom energy
    float *e_penalties;
    float *deriv_penalties;

	//device pointers for grid data
	float3 gridends; //max range of grid
	float3 gridbegins; //min range of grid

	//device pointers for receptor data
	float *recoords;
	float *reccharges;
	unsigned *rectypes;

	//triangular matrix of spline data, indexed by type, device pointer
	unsigned ntypes; //number of atom types; also, dimension of triangular splineInfo
	GPUSplineInfo *splineInfo;
};

void evaluate_splines_host(const GPUSplineInfo& spInfo, float r, float *device_vals, float *device_derivs);
float single_point_calc(GPUNonCacheInfo *dinfo, float *energies, float slope, unsigned natoms, unsigned nrecatoms, float v);


#endif
