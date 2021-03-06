#ifndef PYTHONIC_INCLUDE_NUMPY_ABSOLUTE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ABSOLUTE_HPP

#include "pythonic/numpy/abs.hpp"

namespace pythonic
{

  namespace numpy
  {

#define NUMPY_NARY_FUNC_NAME absolute
#define NUMPY_NARY_FUNC_SYM nt2::abs
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
