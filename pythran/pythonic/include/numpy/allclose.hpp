#ifndef PYTHONIC_INCLUDE_NUMPY_ALLCLOSE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ALLCLOSE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/abs.hpp"
#include "pythonic/numpy/isfinite.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class I0, class I1>
    bool _allclose(I0 begin, I0 end, I1 ibegin, double rtol, double atol,
                   utils::int_<1>);

    template <class I0, class I1, size_t N>
    bool _allclose(I0 begin, I0 end, I1 ibegin, double rtol, double atol,
                   utils::int_<N>);

    template <class U, class V>
    bool allclose(U const &u, V const &v, double rtol = 1e-5,
                  double atol = 1e-8);

    PROXY_DECL(pythonic::numpy, allclose);
  }
}

#endif
