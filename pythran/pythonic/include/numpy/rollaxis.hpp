#ifndef PYTHONIC_INCLUDE_NUMPY_ROLLAXIS_HPP
#define PYTHONIC_INCLUDE_NUMPY_ROLLAXIS_HPP

#include "pythonic/numpy/transpose.hpp"
#include "pythonic/numpy/copy.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, N> rollaxis(types::ndarray<T, N> const &a, long axis,
                                  long start = 0);

    NUMPY_EXPR_TO_NDARRAY0_DECL(rollaxis);
    PROXY_DECL(pythonic::numpy, rollaxis);
  }
}

#endif
