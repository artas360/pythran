#ifndef PYTHONIC_INCLUDE_NUMPY_SORTCOMPLEX_HPP
#define PYTHONIC_INCLUDE_NUMPY_SORTCOMPLEX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/sort.hpp"

namespace pythonic
{

  namespace numpy
  {

    ALIAS_DECL(sort_complex, sort)
    PROXY_DECL(pythonic::numpy, sort_complex);
  }
}

#endif
