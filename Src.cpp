#include <stdlib.h>
#include <time.h>
#include "CLUtils.h"

int main(void)
{
	CLUtilsObject MatrixMultiply;
	MatrixMultiply.CLPlatformStartup();
	MatrixMultiply.CLDeviceStartup(1);
	MatrixMultiply.CLContextStartup();
	MatrixMultiply.ProgFromFile("C:\\Users\\AIPC\\Documents\\Visual Studio 2013\\Projects\\OpenCV\\OpenCV\\kernel.cl");
	
	float *matA, *matB, *matC;
	const unsigned size = 1024;
	matA = new float[size*size];
	matB = new float[size*size];
	matC = new float[size*size];
	for (unsigned i = 0; i != size*size; ++i)
	{
		matA[i] = matB[i] = 2.0f;
	}

	for (unsigned i = 0; i != size; ++i)
	{
		matA[i*size + i] = matB[i*size + i] = 1.0f;
	}

	CLBufferObject A, B, C;
	A.createBuffer(MatrixMultiply.curContext, sizeof(float)*size*size);
	B.createBuffer(MatrixMultiply.curContext, sizeof(float)*size*size);
	C.createBuffer(MatrixMultiply.curContext, sizeof(float)*size*size);

	MatrixMultiply.AddKernel("matMult");
	MatrixMultiply.AddcmdQueue();

	A.feedBuffer(MatrixMultiply.cmdQueue.at(MatrixMultiply.devices[0]).theQueue, sizeof(float)*size*size, matA);
	B.feedBuffer(MatrixMultiply.cmdQueue.at(MatrixMultiply.devices[0]).theQueue, sizeof(float)*size*size, matB);

	MatrixMultiply.FeedKerArgs("matMult", 0, sizeof(cl_mem), &A.memBuffer);
	MatrixMultiply.FeedKerArgs("matMult", 1, sizeof(cl_mem), &B.memBuffer);
	MatrixMultiply.FeedKerArgs("matMult", 2, sizeof(cl_mem), &C.memBuffer);
	size_t globalWorksize[1] = { size };
	size_t computeUnits[1];
	clGetDeviceInfo(MatrixMultiply.devices[0], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(size_t), computeUnits, nullptr);
	size_t localWorksize[1] = { size / computeUnits[0] };
	
	MatrixMultiply.EnqueueNDKernel(MatrixMultiply.cmdQueue.at(MatrixMultiply.devices[0]).theQueue, "matMult", 1, globalWorksize, localWorksize);
	C.fetchBuffer(MatrixMultiply.cmdQueue.at(MatrixMultiply.devices[0]).theQueue, sizeof(float)*size*size, matC);

	std::cout << "Result has been retrieved" << std::endl;
	bool ret = true;
	for (unsigned i = 0; i != size; ++i)
	{
		for (unsigned j = 0; j != size; ++j)
		{
			float res = 0;
			for (unsigned k = 0; k != size; ++k)
			{
				res += matA[i*size + k] * matB[k*size + j];
			}
			if (matC[i*size + j] != res)
			{
				ret = false;
				break;
			}
		}
	}
	if (ret)
	{
		std::cout << "Output ::::: Correct" << std::endl;
	}
	else
	{
		std::cout << "Output ::::: Not Correct" << std::endl;
	}

	delete[] matA;
	delete[] matB;
	delete[] matC;

	A.releaseBuffer();
	B.releaseBuffer();
	C.releaseBuffer();
	MatrixMultiply.CleanUp();
}

/*int main(void)
{
	CLUtilsObject Project;
	Project.CLPlatformStartup();
	Project.CLDeviceStartup(1);
	Project.CLContextStartup();
	Project.AddcmdQueue();
	Project.ProgFromFile("C:\\Users\\AIPC\\Documents\\Visual Studio 2013\\Projects\\OpenCV\\OpenCV\\kernel.txt");
	
	int *A, *B, *C;
	const size_t number = 51200000;
	A = new int[number];
	B = new int[number];
	C = new int[number];
	const size_t datasize = number*sizeof(int);
	for (unsigned i = 0; i != number; ++i)
	{
		A[i] = B[i] = i;
	}

	CLBufferObject bufA, bufB, bufC;
	bufA.createBuffer(Project.curContext, datasize);
	bufB.createBuffer(Project.curContext, datasize);
	bufC.createBuffer(Project.curContext, datasize);

	Project.AddcmdQueue();
	Project.AddKernel("vecadd");

	bufA.feedBuffer(Project.cmdQueue.at(Project.devices[0]).theQueue, datasize, A);
	bufB.feedBuffer(Project.cmdQueue.at(Project.devices[0]).theQueue, datasize, B);

	size_t globalWorkSize[2] = { number , 1 };
	size_t localWorkSize[2] = { 2, 2 };
	Project.FeedKerArgs("vecadd", 0, sizeof(cl_mem), &bufA.memBuffer);
	Project.FeedKerArgs("vecadd", 1, sizeof(cl_mem), &bufB.memBuffer);
	Project.FeedKerArgs("vecadd", 2, sizeof(cl_mem), &bufC.memBuffer);
	Project.EnqueueNDKernel(Project.cmdQueue.at(Project.devices[0]).theQueue, "vecadd", 1, globalWorkSize, nullptr);

	bufC.fetchBuffer(Project.cmdQueue.at(Project.devices[0]).theQueue, datasize, C);

	bool res = true;
	for (unsigned i = 0; i != number; ++i)
	{
		if (C[i] != A[i] + B[i])
		{
			res = false;
			std::cout << "Index " << i << " is not correct!" << std::endl;
			break;
		}
	}

	if (res)
	{
		std::cout << "Output Correct!" << std::endl;
	}
	else
	{
		std::cout << "Output Not Correct!" << std::endl;
	}

	delete[] A;
	delete[] B;
	delete[] C;
	Project.CleanUp();
}*/

/*
int main(void)
{
	int* A = nullptr;
	int* B = nullptr;
	int* C = nullptr;
	const int elements = 20480000;
	size_t datasize = sizeof(int)*elements;

	A = (int*)malloc(datasize);
	B = (int*)malloc(datasize);
	C = (int*)malloc(datasize);

	for (unsigned i = 0; i != elements; ++i)
	{
		A[i] = i;
		B[i] = i;
	}

	cl_int status;
	cl_uint numPlatforms = 0;
	cl_platform_id *platforms = nullptr;
	status = clGetPlatformIDs(0, nullptr, &numPlatforms);
	platforms = (cl_platform_id*)malloc(numPlatforms*sizeof(cl_platform_id));
	status = clGetPlatformIDs(numPlatforms, platforms, nullptr);

	cl_uint numDevices = 0;
	cl_device_id *devices = nullptr;
	status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, nullptr, &numDevices);
	devices = (cl_device_id*)malloc(numDevices*sizeof(cl_device_id));
	status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, numDevices, devices, nullptr);

	cl_context context = nullptr;
	context = clCreateContext(nullptr, numDevices, devices, nullptr, nullptr, &status);
	cl_command_queue cmdQueue;
	cmdQueue = clCreateCommandQueue(context, devices[0], 0, &status);

	cl_mem bufferA, bufferB, bufferC;
	bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, nullptr, &status);
	bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, nullptr, &status);
	bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY, datasize, nullptr, &status);

	status = clEnqueueWriteBuffer(cmdQueue, bufferA, CL_FALSE, 0, datasize, A, 0, nullptr, nullptr);
	status = clEnqueueWriteBuffer(cmdQueue, bufferB, CL_FALSE, 0, datasize, B, 0, nullptr, nullptr);
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&programSource, nullptr, &status);
	status = clBuildProgram(program, numDevices, devices, nullptr, nullptr, nullptr);

	cl_kernel kernel = nullptr;
	kernel = clCreateKernel(program, "vecadd", &status);

	status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufferA);
	status |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufferB);
	status |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufferC);

	size_t globalWorkSize[2];
	globalWorkSize[0] = elements / 2;
	globalWorkSize[1] = 2;

	clock_t time1 = clock();
	status = clEnqueueNDRangeKernel(cmdQueue, kernel, 2, nullptr, globalWorkSize, nullptr, 0, nullptr, nullptr);
	clock_t time2 = clock();
	printf("Time elapsed:%d\n", time2 - time1);

	clEnqueueReadBuffer(cmdQueue, bufferC, CL_TRUE, 0, datasize, C, 0, nullptr, nullptr);

	bool result = true;
	for (unsigned i = 0; i != elements; ++i)
	{
		if (C[i] != 2 * i)
		{
			result = false;
			break;
		}
	}
	if (result)
		printf("Outcome correct\n");
	else
		printf("Outcome incorrect\n");

	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(cmdQueue);
	clReleaseMemObject(bufferA);
	clReleaseMemObject(bufferB);
	clReleaseMemObject(bufferC);
	clReleaseContext(context);

	free(A);
	free(B);
	free(C);
	free(platforms);
	free(devices);
	
	printf("Assets successfully dumped\n");

	return 0;
}*/