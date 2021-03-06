#ifndef PYTHONIC_INCLUDE_NUMPY_SEARCHSORTED_HPP
#define PYTHONIC_INCLUDE_NUMPY_SEARCHSORTED_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/utils/int_.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/asarray.hpp"

#include <algorithm>

namespace pythonic
{

  namespace numpy
  {

    template <class T, class U>
    typename std::enable_if<!types::is_numexpr_arg<T>::value, long>::type
    searchsorted(U const &a, T const &v, types::str const &side = "left");

    template <class E, class I0, class I1>
    void _search_sorted(E const &a, I0 ibegin, I0 iend, I1 obegin,
                        types::str const &side, utils::int_<1>);

    template <class E, class I0, class I1, size_t N>
    void _search_sorted(E const &a, I0 ibegin, I0 iend, I1 obegin,
                        types::str const &side, utils::int_<N>);

    template <class E, class T>
    typename std::enable_if<
        types::is_numexpr_arg<E>::value,
        types::ndarray<long, types::numpy_expr_to_ndarray<E>::N>>::type
    searchsorted(T const &a, E const &v, types::str const &side = "left");

    PROXY_DECL(pythonic::numpy, searchsorted);
  }
}

#endif
