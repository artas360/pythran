#ifndef PYTHONIC_OS_PATH_JOIN_HPP
#define PYTHONIC_OS_PATH_JOIN_HPP

#include "pythonic/include/os/path/join.hpp"

#include "pythonic/types/str.hpp"

namespace pythonic
{
  namespace os
  {
    namespace path
    {

      template <class T>
      size_t sizeof_string(T const &s)
      {
        return s.size();
      }

      template <class T, class... Types>
      size_t sizeof_string(T const &s, Types &&... tail)
      {
        return s.size() + sizeof_string(std::forward<Types>(tail)...);
      }

      void _join(types::str &buffer)
      {
      }

      template <class T, class... Types>
      void _join(types::str &buffer, T &&head, Types &&... tail)
      {
        if (head[0] == '/')
          buffer = head;
        else if (not buffer or *buffer.rbegin() == '/')
          buffer += head;
        else
          buffer += "/" + head;
        _join(buffer, std::forward<Types>(tail)...);
      }

      template <class T>
      T join(T &&head)
      {
        return head;
      }

      template <class T, class... Types>
      types::str join(T &&head, Types &&... tail)
      {
        types::str p = head;
        p.reserve(sizeof_string(tail...));
        _join(p, std::forward<Types>(tail)...);
        return p;
      }

      PROXY_IMPL(pythonic::os::path, join);
    }
  }
}

#endif
