






























#ifndef __VALARRAY_ARRAY__
#define __VALARRAY_ARRAY__

#include <cstdlib>
#include <cstring>

extern "C++" {






template<typename _Tp>
inline void
__valarray_fill (_Tp* __restrict__ __a, size_t __n, const _Tp& __t)
{ while (__n--) *__a++ = __t; }


template<typename _Tp>
inline void
__valarray_fill (_Tp* __restrict__ __a, size_t __n,
                 size_t __s, const _Tp& __t)
{ for (size_t __i=0; __i<__n; ++__i, __a+=__s) *__a = __t; }


template<typename _Tp>
inline void
__valarray_fill(_Tp* __restrict__ __a, const size_t* __restrict__ __i,
                size_t __n, const _Tp& __t)
{ for (size_t __j=0; __j<__n; ++__j, ++__i) __a[*__i] = __t; }


template<typename _Tp>
inline void
__valarray_copy (const _Tp* __restrict__ __a, size_t __n,
                 _Tp* __restrict__ __b)
{ memcpy (__b, __a, __n * sizeof(_Tp)); }


template<typename _Tp>
inline void
__valarray_copy (const _Tp* __restrict__ __a, size_t __n, size_t __s,
                 _Tp* __restrict__ __b)
{ for (size_t __i=0; __i<__n; ++__i, ++__b, __a += __s) *__b = *__a; }


template<typename _Tp>
inline void
__valarray_copy (const _Tp* __restrict__ __a, _Tp* __restrict__ __b,
                 size_t __n, size_t __s)
{ for (size_t __i=0; __i<__n; ++__i, ++__a, __b+=__s) *__b = *__a; }


template<typename _Tp>
inline void
__valarray_copy (const _Tp* __restrict__ __a,
                 const size_t* __restrict__ __i,
                 _Tp* __restrict__ __b, size_t __n)
{ for (size_t __j=0; __j<__n; ++__j, ++__b, ++__i) *__b = __a[*__i]; }


template<typename _Tp>
inline void
__valarray_copy (const _Tp* __restrict__ __a, size_t __n,
                 _Tp* __restrict__ __b, const size_t* __restrict__ __i)
{ for (size_t __j=0; __j<__n; ++__j, ++__a, ++__i) __b[*__i] = *__a; }







template<typename _Tp> struct _Array {
    
    explicit _Array (size_t);
    explicit _Array (_Tp* const __restrict__);
    explicit _Array (const valarray<_Tp>&);
    _Array (const _Tp* __restrict__, size_t);
    
    void free_data() const;
    _Tp* begin () const;
    
    _Tp* const __restrict__ _M_data;
};

template<typename _Tp>
inline void
__valarray_fill (_Array<_Tp> __a, size_t __n, const _Tp& __t)
{ __valarray_fill (__a._M_data, __n, __t); }

template<typename _Tp>
inline void
__valarray_fill (_Array<_Tp> __a, size_t __n, size_t __s, const _Tp& __t)
{ __valarray_fill (__a._M_data, __n, __s, __t); }

template<typename _Tp>
inline void
__valarray_fill (_Array<_Tp> __a, _Array<size_t> __i, 
                 size_t __n, const _Tp& __t)
{ __valarray_fill (__a._M_data, __i._M_data, __n, __t); }

template<typename _Tp>
inline void
__valarray_copy (_Array<_Tp> __a, size_t __n, _Array<_Tp> __b)
{ __valarray_copy (__a._M_data, __n, __b._M_data); }

template<typename _Tp>
inline void
__valarray_copy (_Array<_Tp> __a, size_t __n, size_t __s, _Array<_Tp> __b)
{ __valarray_copy(__a._M_data, __n, __s, __b._M_data); }

template<typename _Tp>
inline void
__valarray_copy (_Array<_Tp> __a, _Array<_Tp> __b, size_t __n, size_t __s)
{ __valarray_copy (__a._M_data, __b._M_data, __n, __s); }

template<typename _Tp>
inline void
__valarray_copy (_Array<_Tp> __a, _Array<size_t> __i, 
                 _Array<_Tp> __b, size_t __n)
{ __valarray_copy (__a._M_data, __i._M_data, __b._M_data, __n); }

template<typename _Tp>
inline void
__valarray_copy (_Array<_Tp> __a, size_t __n, _Array<_Tp> __b, 
                 _Array<size_t> __i)
{ __valarray_copy (__a._M_data, __n, __b._M_data, __i._M_data); }

template<typename _Tp>
inline
_Array<_Tp>::_Array (size_t __n) : _M_data (new _Tp[__n]) {}

template<typename _Tp>
inline
_Array<_Tp>::_Array (_Tp* const __restrict__ __p) : _M_data (__p) {}

template<typename _Tp>
inline _Array<_Tp>::_Array (const valarray<_Tp>& __v) 
        : _M_data (__v._M_data) {}

template<typename _Tp>
inline
_Array<_Tp>::_Array (const _Tp* __restrict__ __b, size_t __s) 
        : _M_data (new _Tp[__s]) { __valarray_copy (__b, __s, _M_data); }

template<typename _Tp>
inline void
_Array<_Tp>::free_data() const { delete[] _M_data; }

template<typename _Tp>
inline _Tp*
_Array<_Tp>::begin () const
{ return _M_data; }

#define _DEFINE_ARRAY_FUNCTION(_Op, _Name)				\
template<typename _Tp>							\
inline void								\
_Array_augmented_##_Name (_Array<_Tp> __a, size_t __n, const _Tp& __t)	\
{									\
    for (_Tp* __p=__a._M_data; __p<__a._M_data+__n; ++__p) 		\
      *__p _Op##= __t;							\
}									\
									\
template<typename _Tp>							\
inline void								\
_Array_augmented_##_Name (_Array<_Tp> __a, size_t __n, _Array<_Tp> __b)	\
{									\
    _Tp* __p (__a._M_data);						\
    for (_Tp* __q=__b._M_data; __q<__b._M_data+__n; ++__p, ++__q) 	\
      *__p _Op##= *__q;							\
}									\
									\
template<typename _Tp, class _Dom>					\
void									\
_Array_augmented_##_Name (_Array<_Tp> __a, 				\
                         const _Expr<_Dom,_Tp>& __e, size_t __n)	\
{									\
    _Tp* __p (__a._M_data);						\
    for (size_t __i=0; __i<__n; ++__i, ++__p) *__p _Op##= __e[__i];	\
}									\
									\
template<typename _Tp>							\
inline void								\
_Array_augmented_##_Name (_Array<_Tp> __a, size_t __n, size_t __s, 	\
			 _Array<_Tp> __b)				\
{					       				\
    _Tp* __q (__b._M_data);						\
    for (_Tp* __p=__a._M_data; __p<__a._M_data+__s*__n; __p+=__s, ++__q) \
      *__p _Op##= *__q;							\
}									\
									\
template<typename _Tp>							\
inline void								\
_Array_augmented_##_Name (_Array<_Tp> __a, _Array<_Tp> __b, 		\
			 size_t __n, size_t __s)			\
{									\
    _Tp* __q (__b._M_data);						\
    for (_Tp* __p=__a._M_data; __p<__a._M_data+__n; ++__p, __q+=__s)	\
      *__p _Op##= *__q;							\
}									\
									\
template<typename _Tp, class _Dom>					\
void									\
_Array_augmented_##_Name (_Array<_Tp> __a, size_t __s,			\
                          const _Expr<_Dom,_Tp>& __e, size_t __n)	\
{									\
    _Tp* __p (__a._M_data);						\
    for (size_t __i=0; __i<__n; ++__i, __p+=__s) *__p _Op##= __e[__i];	\
}									\
									\
template<typename _Tp>							\
inline void								\
_Array_augmented_##_Name (_Array<_Tp> __a, _Array<size_t> __i,		\
                          _Array<_Tp> __b, size_t __n)			\
{									\
    _Tp* __q (__b._M_data);						\
    for (size_t* __j=__i._M_data; __j<__i._M_data+__n; ++__j, ++__q)	\
        __a._M_data[*__j] _Op##= *__q;					\
}									\
									\
template<typename _Tp>							\
inline void								\
_Array_augmented_##_Name (_Array<_Tp> __a, size_t __n,			\
                          _Array<_Tp> __b, _Array<size_t> __i)		\
{									\
    _Tp* __p (__a._M_data);						\
    for (size_t* __j=__i._M_data; __j<__i._M_data+__n; ++__j, ++__p)	\
        *__p _Op##= __b._M_data[*__j];					\
}									\
									\
template<typename _Tp, class _Dom>					\
void									\
_Array_augmented_##_Name (_Array<_Tp> __a, _Array<size_t> __i,		\
                          const _Expr<_Dom, _Tp>& __e, size_t __n)	\
{									\
    size_t* __j (__i._M_data);						\
    for (size_t __k=0; __k<__n; ++__k, ++__j) 				\
      __a._M_data[*__j] _Op##= __e[__k];				\
}									\
									\
template<typename _Tp>							\
void									\
_Array_augmented_##_Name (_Array<_Tp> __a, _Array<bool> __m,		\
                          _Array<_Tp> __b, size_t __n)			\
{									\
    bool* ok (__m._M_data);						\
    _Tp* __p (__a._M_data);						\
    for (_Tp* __q=__b._M_data; __q<__b._M_data+__n; ++__q, ++ok, ++__p) { \
        while (! *ok) {							\
            ++ok;							\
            ++__p;							\
        }								\
        *__p _Op##= *__q;						\
    }									\
}									\
									\
template<typename _Tp>							\
void									\
_Array_augmented_##_Name (_Array<_Tp> __a, size_t __n,			\
                         _Array<_Tp> __b, _Array<bool> __m)		\
{									\
    bool* ok (__m._M_data);						\
    _Tp* __q (__b._M_data);						\
    for (_Tp* __p=__a._M_data; __p<__a._M_data+__n; ++__p, ++ok, ++__q) { \
        while (! *ok) {							\
            ++ok;							\
            ++__q;							\
        }								\
        *__p _Op##= *__q;						\
    }									\
}									\
									\
template<typename _Tp, class _Dom>					\
void									\
_Array_augmented_##_Name (_Array<_Tp> __a, _Array<bool> __m,		\
                          const _Expr<_Dom, _Tp>& __e, size_t __n)	\
{									\
    bool* ok(__m._M_data);						\
    _Tp* __p (__a._M_data);						\
    for (size_t __i=0; __i<__n; ++__i, ++ok, ++__p) {			\
        while (! *ok) {							\
            ++ok;							\
            ++__p;							\
        }								\
        *__p _Op##= __e[__i];						\
    }									\
}

_DEFINE_ARRAY_FUNCTION(+, plus)
_DEFINE_ARRAY_FUNCTION(-, minus)
_DEFINE_ARRAY_FUNCTION(*, multiplies)
_DEFINE_ARRAY_FUNCTION(/, divides)
_DEFINE_ARRAY_FUNCTION(%, modulus)
_DEFINE_ARRAY_FUNCTION(^, xor)
_DEFINE_ARRAY_FUNCTION(|, or)
_DEFINE_ARRAY_FUNCTION(&, and)    
_DEFINE_ARRAY_FUNCTION(<<, shift_left)
_DEFINE_ARRAY_FUNCTION(>>, shift_right)

#undef _DEFINE_ARRAY_FUNCTION    

}
    
#ifdef _G_NO_VALARRAY_TEMPLATE_EXPORT
# define export 
# include <std/valarray_array.tcc>    
#endif
           
#endif




