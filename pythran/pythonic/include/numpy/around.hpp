#ifndef PYTHONIC_INCLUDE_NUMPY_AROUND_HPP
#define PYTHONIC_INCLUDE_NUMPY_AROUND_HPP

#include "pythonic/numpy/rint.hpp"
#include <nt2/include/functions/pow.hpp>

namespace pythonic
{

  namespace numpy
  {

    // generic floating point version, pure numpy_expr
    template <class E>
    auto around(E const &a, long decimals = 0) -> typename std::enable_if<
        !std::is_integral<
            typename types::numpy_expr_to_ndarray<E>::type::dtype>::value,
        decltype(
            proxy::rint()(a *nt2::pow(
                typename types::numpy_expr_to_ndarray<E>::type::dtype(10),
                decimals)) /
            nt2::pow(typename types::numpy_expr_to_ndarray<E>::type::dtype(10),
                     decimals))>::type;

    // the integer version is only relevant when decimals < 0
    template <class E>
    auto around(E const &a, long decimals = 0) -> typename std::enable_if<
        std::is_integral<
            typename types::numpy_expr_to_ndarray<E>::type::dtype>::value,
        decltype(a / (long)nt2::pow(typename types::numpy_expr_to_ndarray<
                                        E>::type::dtype(10),
                                    std::max(0L, -decimals)) *
                 (long)nt2::pow(
                     typename types::numpy_expr_to_ndarray<E>::type::dtype(10),
                     std::max(0L, -decimals)))>::type;

    PROXY_DECL(pythonic::numpy, around);
  }
}

#endif
