#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_REVERSE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_REVERSE_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/none.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace list
    {

      template <class T>
      types::none_type reverse(types::list<T> &seq);

      PROXY_DECL(pythonic::__builtin__::list, reverse);
    }
  }
}
#endif
