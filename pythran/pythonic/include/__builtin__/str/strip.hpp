#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_STRIP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_STRIP_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      types::str strip(types::str const &self,
                       types::str const &to_del = " \n");

      PROXY_DECL(pythonic::__builtin__::str, strip);
    }
  }
}
#endif
