#ifndef PYTHONIC_NUMPY_TRI_HPP
#define PYTHONIC_NUMPY_TRI_HPP

#include "pythonic/include/numpy/tri.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class dtype>
    types::ndarray<typename types::numpy_type<dtype>::type, 2>
    tri(int N, int M, int k, dtype d)
    {
      if (M == -1)
        M = N;
      types::ndarray<typename types::numpy_type<dtype>::type, 2> out(
          types::array<long, 2>{{N, M}}, 0);
      for (int i = 0; i < N; ++i)
        for (long j = 0; j < M; ++j)
          if (j - i <= k)
            out[i][j] = 1;
      return out;
    }

    PROXY_IMPL(pythonic::numpy, tri)
  }
}

#endif
