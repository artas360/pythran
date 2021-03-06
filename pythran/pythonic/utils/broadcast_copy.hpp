#ifndef PYTHONIC_UTILS_BROADCAST_COPY_HPP
#define PYTHONIC_UTILS_BROADCAST_COPY_HPP

#include "pythonic/include/utils/broadcast_copy.hpp"

#include "pythonic/types/tuple.hpp"
#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#endif

#ifdef _OPENMP
#include <omp.h>

// as a macro so that an enlightened user can modify this variable :-)
#ifndef PYTHRAN_OPENMP_MIN_ITERATION_COUNT
#define PYTHRAN_OPENMP_MIN_ITERATION_COUNT 1000
#endif

#endif

namespace pythonic
{

  namespace utils
  {

    template <bool vector_form>
    template <class E, class F, size_t N>
    void _broadcast_copy<vector_form>::
    operator()(E &&self, F const &other, utils::int_<N>, utils::int_<0>)
    {
      long self_size = std::distance(self.begin(), self.end()),
           other_size = std::distance(other.begin(), other.end());
      if (other_size > 0) // empty array sometimes happen when filtering
      {
#ifdef _OPENMP
        if (other_size >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
          for (long i = 0; i < other_size; ++i)
            self.fast(i) = other.fast(i);
        else
#endif
          std::copy(other.begin(), other.end(), self.begin());

        // eventually repeat the pattern
        size_t n = self_size / other_size;
#ifdef _OPENMP
        if (n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
          for (size_t i = 1; i < n; ++i)
            std::copy_n(self.begin(), other_size,
                        self.begin() + i * other_size);
        else
#endif
          for (size_t i = 1; i < n; ++i)
            std::copy_n(self.begin(), other_size,
                        self.begin() + i * other_size);
      }
    }

    // ``D'' is not ``0'' so we should broadcast
    template <bool vector_form>
    template <class E, class F, size_t N, size_t D>
    void _broadcast_copy<vector_form>::
    operator()(E &&self, F const &other, utils::int_<N>, utils::int_<D>)
    {
      self.fast(0) = other;
#ifdef _OPENMP
      long n = self.shape[0];
      if (n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
        for (long i = 1; i < n; ++i)
          self.fast(i) = self.fast(0);
      else
#endif
        std::fill(self.begin() + 1, self.end(), self.fast(0));
    }

#ifdef USE_BOOST_SIMD
    // specialize for SIMD only if available
    // otherwise use the std::copy fallback
    template <class E, class F>
    void _broadcast_copy<true>::operator()(E &&self, F const &other,
                                           utils::int_<1>, utils::int_<0>)
    {
      using T = typename F::dtype;
      using vT = typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>;
      long self_size = std::distance(self.begin(), self.end()),
           other_size = std::distance(other.begin(), other.end());

      if (other_size > 0) // empty array sometimes happen when filtering
      {
        static const std::size_t vN = boost::simd::meta::cardinal_of<vT>::value;
        const long bound = other_size / vN * vN;

        long i;
#ifdef _OPENMP
        if (bound >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
          for (i = 0; i < bound; i += vN)
            self.store(other.load(i), i);
        else
#endif
          for (i = 0; i < bound; i += vN)
            self.store(other.load(i), i);
        for (; i < other_size; ++i)
          self.fast(i) = other.fast(i);

        size_t n = self_size / other_size;
#ifdef _OPENMP
        if (n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
          for (size_t i = 1; i < n; ++i)
            std::copy_n(self.begin(), other_size,
                        self.begin() + i * other_size);
        else
#endif
          for (size_t i = 1; i < n; ++i)
            std::copy_n(self.begin(), other_size,
                        self.begin() + i * other_size);
      }
    }

    template <class E, class F, size_t N>
    void _broadcast_copy<true>::operator()(E &&self, F const &other,
                                           utils::int_<N>, utils::int_<0>)
    {
      long self_size = std::distance(self.begin(), self.end()),
           other_size = std::distance(other.begin(), other.end());
      if (other_size > 0) // empty array sometimes happen when filtering
      {
#ifdef _OPENMP
        if (other_size >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
          for (long i = 0; i < other_size; ++i)
            (*this)(self.fast(i), other.fast(i), utils::int_<N - 1>(),
                    utils::int_<0>());
        else
#endif
          for (long i = 0; i < other_size; ++i)
            (*this)(self.fast(i), other.fast(i), utils::int_<N - 1>(),
                    utils::int_<0>());

        // eventually repeat the pattern
        size_t n = self_size / other_size;
#ifdef _OPENMP
        if (n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
          for (size_t i = 1; i < n; ++i)
            std::copy_n(self.begin(), other_size,
                        self.begin() + i * other_size);
        else
#endif
          for (size_t i = 1; i < n; ++i)
            std::copy_n(self.begin(), other_size,
                        self.begin() + i * other_size);
      }
    }

    // ``D'' is not ``0'' so we should broadcast
    template <class E, class F, size_t N, size_t D>
    void _broadcast_copy<true>::operator()(E &&self, F const &other,
                                           utils::int_<N>, utils::int_<D>)
    {
      (*this)(self.fast(0), other, utils::int_<N - 1>(), utils::int_<D - 1>());
#ifdef _OPENMP
      long n = self.shape[0];
      if (n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
        for (long i = 1; i < n; ++i)
          self.fast(i) = self.fast(0);
      else
#endif
        std::fill(self.begin() + 1, self.end(), self.fast(0));
    }

#endif

    template <class E, class F, size_t N, size_t D, bool vector_form>
    E &broadcast_copy(E &self, F const &other)
    {
      _broadcast_copy<vector_form>{}(self, other, utils::int_<N>(),
                                     utils::int_<D>());
      return self;
    }
  }
}

#endif
