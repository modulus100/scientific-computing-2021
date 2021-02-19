cmake_minimum_required(VERSION 3.17)
project(matrixes C)

set(CMAKE_C_STANDARD 11)

add_executable(matrixes main.c)

# link openblas
set(BLA_VENDER OpenBLAS)
find_package(BLAS REQUIRED)
if(BLAS_FOUND)
    message(${BLAS_LIBRARIES})
    find_path(BLAS_INCLUDE_DIRS cblas.h
            /usr/include
            /usr/local/include
            $ENV{BLAS_HOME}/include)
    target_link_libraries(matrixes ${BLAS_LIBRARIES})
endif(BLAS_FOUND)
