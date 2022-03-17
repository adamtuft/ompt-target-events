#!/bin/bash

# Build OpenMP tool
icx -I.. -g -shared -fPIC ../src/ompt-tool.c -o libtool.so

# Compile matmul example
icx -g -qopenmp -fopenmp-targets=spir64 ../src/matmul-offload.c -o matmul

export OMP_TOOL_LIBRARIES=./libtool.so
export OMP_TARGET_OFFLOAD=MANDATORY
export LIBOMPTARGET_DEBUG=2
export LIBOMPTARGET_INFO=4

echo HOSTNAME=${HOSTNAME} >hostname.${PBS_JOBID}.txt
./matmul
