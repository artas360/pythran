#ifndef PYTHONIC_INCLUDE_DISPATCH_UPDATE_HPP
#define PYTHONIC_INCLUDE_DISPATCH_UPDATE_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __dispatch__
  {

    template <class Any, class... Arg0>
    auto update(Any &&any, Arg0 &&... arg0)
        -> decltype(any.update(std::forward<Arg0>(arg0)...));

    PROXY_DECL(pythonic::__dispatch__, update);
  }
}

#endif
