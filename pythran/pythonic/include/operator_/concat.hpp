#ifndef PYTHONIC_INCLUDE_OPERATOR_CONCAT_HPP
#define PYTHONIC_INCLUDE_OPERATOR_CONCAT_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    auto concat(A const &a, B const &b) -> decltype(a + b);

    PROXY_DECL(pythonic::operator_, concat);
  }
}

#endif
