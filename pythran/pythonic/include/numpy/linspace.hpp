#ifndef PYTHONIC_INCLUDE_NUMPY_LINSPACE_HPP
#define PYTHONIC_INCLUDE_NUMPY_LINSPACE_HPP

#include "pythonic/numpy/arange.hpp"

namespace pythonic
{

  namespace numpy
  {

    types::ndarray<double, 1> linspace(double start, double stop, long num = 50,
                                       bool endpoint = true);

    PROXY_DECL(pythonic::numpy, linspace);
  }
}

#endif
