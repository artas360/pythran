#ifndef PYTHONIC_BUILTIN_DICT_POP_HPP
#define PYTHONIC_BUILTIN_DICT_POP_HPP

#include "pythonic/include/__builtin__/dict/pop.hpp"

#include "pythonic/__dispatch__/pop.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {

      ALIAS(pop, pythonic::__dispatch__::pop);

      PROXY_IMPL(pythonic::__builtin__::dict, pop);
    }
  }
}

#endif
