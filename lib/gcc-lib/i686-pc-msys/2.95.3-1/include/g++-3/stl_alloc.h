/*
 * Copyright (c) 1996-1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_ALLOC_H
#define __SGI_STL_INTERNAL_ALLOC_H

#ifdef __SUNPRO_CC
#  define __PRIVATE public
  
  
#else
#  define __PRIVATE private
#endif

#ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG
#  define __USE_MALLOC
#endif









#if 0
#   include <new>
#   define __THROW_BAD_ALLOC throw bad_alloc()
#elif !defined(__THROW_BAD_ALLOC)
#   include <iostream.h>
#   define __THROW_BAD_ALLOC cerr << "out of memory" << endl; exit(1)
#endif

#ifdef __STL_WIN32THREADS
#   include <windows.h>
#endif

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#ifndef __RESTRICT
#  define __RESTRICT
#endif

#if !defined(__STL_PTHREADS) && !defined(__STL_SOLTHREADS) \
 && !defined(_NOTHREADS) \
 && !defined(__STL_SGI_THREADS) && !defined(__STL_WIN32THREADS)
#   define _NOTHREADS
#endif

# ifdef __STL_PTHREADS
   
   
   
#   include <pthread.h>
#   define __NODE_ALLOCATOR_LOCK \
        if (threads) pthread_mutex_lock(&_S_node_allocator_lock)
#   define __NODE_ALLOCATOR_UNLOCK \
        if (threads) pthread_mutex_unlock(&_S_node_allocator_lock)
#   define __NODE_ALLOCATOR_THREADS true
#   define __VOLATILE volatile 
# endif
# ifdef __STL_SOLTHREADS
#   include <thread.h>
#   define __NODE_ALLOCATOR_LOCK \
	if (threads) mutex_lock(&_S_node_allocator_lock)
#   define __NODE_ALLOCATOR_UNLOCK \
        if (threads) mutex_unlock(&_S_node_allocator_lock)
#   define __NODE_ALLOCATOR_THREADS true
#   define __VOLATILE
# endif
# ifdef __STL_WIN32THREADS
   
   
#   define __NODE_ALLOCATOR_LOCK \
        EnterCriticalSection(&_S_node_allocator_lock)
#   define __NODE_ALLOCATOR_UNLOCK \
        LeaveCriticalSection(&_S_node_allocator_lock)
#   define __NODE_ALLOCATOR_THREADS true
#   define __VOLATILE volatile 
# endif /* WIN32THREADS */
# ifdef __STL_SGI_THREADS
   
   
   

    extern "C" {
      extern int __us_rsthread_malloc;
    }



#   define __NODE_ALLOCATOR_LOCK if (threads && __us_rsthread_malloc) \
                { _S_lock(&_S_node_allocator_lock); }
#   define __NODE_ALLOCATOR_UNLOCK if (threads && __us_rsthread_malloc) \
                { _S_unlock(&_S_node_allocator_lock); }
#   define __NODE_ALLOCATOR_THREADS true
#   define __VOLATILE volatile 
# endif
# ifdef _NOTHREADS

#   define __NODE_ALLOCATOR_LOCK
#   define __NODE_ALLOCATOR_UNLOCK
#   define __NODE_ALLOCATOR_THREADS false
#   define __VOLATILE
# endif

__STL_BEGIN_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#endif



#ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG
# ifdef __DECLARE_GLOBALS_HERE
    void (* __malloc_alloc_oom_handler)() = 0;
   
# else
    extern void (* __malloc_alloc_oom_handler)();
# endif
#endif

template <int __inst>
class __malloc_alloc_template {

private:

  static void* _S_oom_malloc(size_t);
  static void* _S_oom_realloc(void*, size_t);

#ifndef __STL_STATIC_TEMPLATE_MEMBER_BUG
  static void (* __malloc_alloc_oom_handler)();
#endif

public:

  static void* allocate(size_t __n)
  {
    void* __result = malloc(__n);
    if (0 == __result) __result = _S_oom_malloc(__n);
    return __result;
  }

  static void deallocate(void* __p, size_t /* __n */)
  {
    free(__p);
  }

  static void* reallocate(void* __p, size_t /* old_sz */, size_t __new_sz)
  {
    void* __result = realloc(__p, __new_sz);
    if (0 == __result) __result = _S_oom_realloc(__p, __new_sz);
    return __result;
  }

  static void (* __set_malloc_handler(void (*__f)()))()
  {
    void (* __old)() = __malloc_alloc_oom_handler;
    __malloc_alloc_oom_handler = __f;
    return(__old);
  }

};



#ifndef __STL_STATIC_TEMPLATE_MEMBER_BUG
template <int __inst>
void (* __malloc_alloc_template<__inst>::__malloc_alloc_oom_handler)() = 0;
#endif

template <int __inst>
void*
__malloc_alloc_template<__inst>::_S_oom_malloc(size_t __n)
{
    void (* __my_malloc_handler)();
    void* __result;

    for (;;) {
        __my_malloc_handler = __malloc_alloc_oom_handler;
        if (0 == __my_malloc_handler) { __THROW_BAD_ALLOC; }
        (*__my_malloc_handler)();
        __result = malloc(__n);
        if (__result) return(__result);
    }
}

template <int __inst>
void* __malloc_alloc_template<__inst>::_S_oom_realloc(void* __p, size_t __n)
{
    void (* __my_malloc_handler)();
    void* __result;

    for (;;) {
        __my_malloc_handler = __malloc_alloc_oom_handler;
        if (0 == __my_malloc_handler) { __THROW_BAD_ALLOC; }
        (*__my_malloc_handler)();
        __result = realloc(__p, __n);
        if (__result) return(__result);
    }
}

typedef __malloc_alloc_template<0> malloc_alloc;

template<class _Tp, class _Alloc>
class simple_alloc {

public:
    static _Tp* allocate(size_t __n)
      { return 0 == __n ? 0 : (_Tp*) _Alloc::allocate(__n * sizeof (_Tp)); }
    static _Tp* allocate(void)
      { return (_Tp*) _Alloc::allocate(sizeof (_Tp)); }
    static void deallocate(_Tp* __p, size_t __n)
      { if (0 != __n) _Alloc::deallocate(__p, __n * sizeof (_Tp)); }
    static void deallocate(_Tp* __p)
      { _Alloc::deallocate(__p, sizeof (_Tp)); }
};






template <class _Alloc>
class debug_alloc {

private:

  enum {_S_extra = 8}; 
                       
                       

public:

  static void* allocate(size_t __n)
  {
    char* __result = (char*)_Alloc::allocate(__n + _S_extra);
    *(size_t*)__result = __n;
    return __result + _S_extra;
  }

  static void deallocate(void* __p, size_t __n)
  {
    char* __real_p = (char*)__p - _S_extra;
    assert(*(size_t*)__real_p == __n);
    _Alloc::deallocate(__real_p, __n + _S_extra);
  }

  static void* reallocate(void* __p, size_t __old_sz, size_t __new_sz)
  {
    char* __real_p = (char*)__p - _S_extra;
    assert(*(size_t*)__real_p == __old_sz);
    char* __result = (char*)
      _Alloc::reallocate(__real_p, __old_sz + _S_extra, __new_sz + _S_extra);
    *(size_t*)__result = __new_sz;
    return __result + _S_extra;
  }

};


# ifdef __USE_MALLOC

typedef malloc_alloc alloc;
typedef malloc_alloc single_client_alloc;

# else


























#ifdef __SUNPRO_CC

  enum {_ALIGN = 8};
  enum {_MAX_BYTES = 128};
  enum {_NFREELISTS = _MAX_BYTES/_ALIGN};
#endif

template <bool threads, int inst>
class __default_alloc_template {

private:
 
 
# ifndef __SUNPRO_CC
    enum {_ALIGN = 8};
    enum {_MAX_BYTES = 128};
    enum {_NFREELISTS = _MAX_BYTES/_ALIGN};
# endif
  static size_t
  _S_round_up(size_t __bytes)
    { return (((__bytes) + _ALIGN-1) & ~(_ALIGN - 1)); }

__PRIVATE:
  union _Obj {
        union _Obj* _M_free_list_link;
        char _M_client_data[1];    /* The client sees this.        */
  };
private:
# ifdef __SUNPRO_CC
    static _Obj* __VOLATILE _S_free_list[];
       
# else
    static _Obj* __VOLATILE _S_free_list[_NFREELISTS];
# endif
  static  size_t _S_freelist_index(size_t __bytes) {
        return (((__bytes) + _ALIGN-1)/_ALIGN - 1);
  }

 
  static void* _S_refill(size_t __n);
 
 
  static char* _S_chunk_alloc(size_t __size, int& __nobjs);

 
  static char* _S_start_free;
  static char* _S_end_free;
  static size_t _S_heap_size;

# ifdef __STL_SGI_THREADS
    static volatile unsigned long _S_node_allocator_lock;
    static void _S_lock(volatile unsigned long*);
    static inline void _S_unlock(volatile unsigned long*);
# endif

# ifdef __STL_PTHREADS
    static pthread_mutex_t _S_node_allocator_lock;
# endif

# ifdef __STL_SOLTHREADS
    static mutex_t _S_node_allocator_lock;
# endif

# ifdef __STL_WIN32THREADS
    static CRITICAL_SECTION _S_node_allocator_lock;
    static bool _S_node_allocator_lock_initialized;

  public:
    __default_alloc_template() {


        if (!_S_node_allocator_lock_initialized) {
            InitializeCriticalSection(&_S_node_allocator_lock);
            _S_node_allocator_lock_initialized = true;
        }
    }
  private:
# endif

    class _Lock {
        public:
            _Lock() { __NODE_ALLOCATOR_LOCK; }
            ~_Lock() { __NODE_ALLOCATOR_UNLOCK; }
    };
    friend class _Lock;

public:

  /* __n must be > 0      */
  static void* allocate(size_t __n)
  {
    _Obj* __VOLATILE* __my_free_list;
    _Obj* __RESTRICT __result;

    if (__n > (size_t) _MAX_BYTES) {
        return(malloc_alloc::allocate(__n));
    }
    __my_free_list = _S_free_list + _S_freelist_index(__n);
   
   
   
#       ifndef _NOTHREADS
        /*REFERENCED*/
        _Lock __lock_instance;
#       endif
    __result = *__my_free_list;
    if (__result == 0) {
        void* __r = _S_refill(_S_round_up(__n));
        return __r;
    }
    *__my_free_list = __result -> _M_free_list_link;
    return (__result);
  };

  /* __p may not be 0 */
  static void deallocate(void* __p, size_t __n)
  {
    _Obj* __q = (_Obj*)__p;
    _Obj* __VOLATILE* __my_free_list;

    if (__n > (size_t) _MAX_BYTES) {
        malloc_alloc::deallocate(__p, __n);
        return;
    }
    __my_free_list = _S_free_list + _S_freelist_index(__n);
   
#       ifndef _NOTHREADS
        /*REFERENCED*/
        _Lock __lock_instance;
#       endif /* _NOTHREADS */
    __q -> _M_free_list_link = *__my_free_list;
    *__my_free_list = __q;
   
  }

  static void* reallocate(void* __p, size_t __old_sz, size_t __new_sz);

} ;

typedef __default_alloc_template<__NODE_ALLOCATOR_THREADS, 0> alloc;
typedef __default_alloc_template<false, 0> single_client_alloc;



/* We allocate memory in large chunks in order to avoid fragmenting     */
/* the malloc heap too much.                                            */
/* We assume that size is properly aligned.                             */
/* We hold the allocation lock.                                         */
template <bool __threads, int __inst>
char*
__default_alloc_template<__threads, __inst>::_S_chunk_alloc(size_t __size,
                                                            int& __nobjs)
{
    char* __result;
    size_t __total_bytes = __size * __nobjs;
    size_t __bytes_left = _S_end_free - _S_start_free;

    if (__bytes_left >= __total_bytes) {
        __result = _S_start_free;
        _S_start_free += __total_bytes;
        return(__result);
    } else if (__bytes_left >= __size) {
        __nobjs = (int)(__bytes_left/__size);
        __total_bytes = __size * __nobjs;
        __result = _S_start_free;
        _S_start_free += __total_bytes;
        return(__result);
    } else {
        size_t __bytes_to_get =
	  2 * __total_bytes + _S_round_up(_S_heap_size >> 4);
       
        if (__bytes_left > 0) {
            _Obj* __VOLATILE* __my_free_list =
                        _S_free_list + _S_freelist_index(__bytes_left);

            ((_Obj*)_S_start_free) -> _M_free_list_link = *__my_free_list;
            *__my_free_list = (_Obj*)_S_start_free;
        }
        _S_start_free = (char*)malloc(__bytes_to_get);
        if (0 == _S_start_free) {
            size_t __i;
            _Obj* __VOLATILE* __my_free_list;
	    _Obj* __p;
           
           
           
            for (__i = __size; __i <= _MAX_BYTES; __i += _ALIGN) {
                __my_free_list = _S_free_list + _S_freelist_index(__i);
                __p = *__my_free_list;
                if (0 != __p) {
                    *__my_free_list = __p -> _M_free_list_link;
                    _S_start_free = (char*)__p;
                    _S_end_free = _S_start_free + __i;
                    return(_S_chunk_alloc(__size, __nobjs));
                   
                   
                }
            }
	    _S_end_free = 0;
            _S_start_free = (char*)malloc_alloc::allocate(__bytes_to_get);
           
           
           
        }
        _S_heap_size += __bytes_to_get;
        _S_end_free = _S_start_free + __bytes_to_get;
        return(_S_chunk_alloc(__size, __nobjs));
    }
}


/* Returns an object of size __n, and optionally adds to size __n free list.*/
/* We assume that __n is properly aligned.                                */
/* We hold the allocation lock.                                         */
template <bool __threads, int __inst>
void*
__default_alloc_template<__threads, __inst>::_S_refill(size_t __n)
{
    int __nobjs = 20;
    char* __chunk = _S_chunk_alloc(__n, __nobjs);
    _Obj* __VOLATILE* __my_free_list;
    _Obj* __result;
    _Obj* __current_obj;
    _Obj* __next_obj;
    int __i;

    if (1 == __nobjs) return(__chunk);
    __my_free_list = _S_free_list + _S_freelist_index(__n);

    /* Build free list in chunk */
      __result = (_Obj*)__chunk;
      *__my_free_list = __next_obj = (_Obj*)(__chunk + __n);
      for (__i = 1; ; __i++) {
        __current_obj = __next_obj;
        __next_obj = (_Obj*)((char*)__next_obj + __n);
        if (__nobjs - 1 == __i) {
            __current_obj -> _M_free_list_link = 0;
            break;
        } else {
            __current_obj -> _M_free_list_link = __next_obj;
        }
      }
    return(__result);
}

template <bool threads, int inst>
void*
__default_alloc_template<threads, inst>::reallocate(void* __p,
                                                    size_t __old_sz,
                                                    size_t __new_sz)
{
    void* __result;
    size_t __copy_sz;

    if (__old_sz > (size_t) _MAX_BYTES && __new_sz > (size_t) _MAX_BYTES) {
        return(realloc(__p, __new_sz));
    }
    if (_S_round_up(__old_sz) == _S_round_up(__new_sz)) return(__p);
    __result = allocate(__new_sz);
    __copy_sz = __new_sz > __old_sz? __old_sz : __new_sz;
    memcpy(__result, __p, __copy_sz);
    deallocate(__p, __old_sz);
    return(__result);
}

#ifdef __STL_PTHREADS
    template <bool __threads, int __inst>
    pthread_mutex_t
    __default_alloc_template<__threads, __inst>::_S_node_allocator_lock
        = PTHREAD_MUTEX_INITIALIZER;
#endif

#ifdef __STL_SOLTHREADS
    template <bool __threads, int __inst>
    mutex_t
    __default_alloc_template<__threads, __inst>::_S_node_allocator_lock
        = DEFAULTMUTEX;
#endif

#ifdef __STL_WIN32THREADS
    template <bool __threads, int __inst>
    CRITICAL_SECTION
    __default_alloc_template<__threads, __inst>::
      _S_node_allocator_lock;

    template <bool __threads, int __inst>
    bool
    __default_alloc_template<__threads, __inst>::
      _S_node_allocator_lock_initialized
	= false;
#endif

#ifdef __STL_SGI_THREADS
__STL_END_NAMESPACE
#include <mutex.h>
#include <time.h>  /* XXX should use <ctime> */
__STL_BEGIN_NAMESPACE



template <bool __threads, int __inst>
volatile unsigned long
__default_alloc_template<__threads, __inst>::_S_node_allocator_lock = 0;

#if __mips__ < 3 || !(defined (_ABIN32) || defined(_ABI64)) || defined(__GNUC__)
#   define __test_and_set(l,v) test_and_set(l,v)
#endif

template <bool __threads, int __inst>
void
__default_alloc_template<__threads, __inst>::
  _S_lock(volatile unsigned long* __lock)
{
    const unsigned __low_spin_max = 30; 
    const unsigned __high_spin_max = 1000;
    static unsigned __spin_max = __low_spin_max;
    unsigned __my_spin_max;
    static unsigned __last_spins = 0;
    unsigned __my_last_spins;
    unsigned __junk;
#   define __ALLOC_PAUSE \
      __junk *= __junk; __junk *= __junk; __junk *= __junk; __junk *= __junk
    int __i;

    if (!__test_and_set((unsigned long*)__lock, 1)) {
        return;
    }
    __my_spin_max = __spin_max;
    __my_last_spins = __last_spins;
    for (__i = 0; __i < __my_spin_max; __i++) {
        if (__i < __my_last_spins/2 || *__lock) {
            __ALLOC_PAUSE;
            continue;
        }
        if (!__test_and_set((unsigned long*)__lock, 1)) {
           
           
           
           
            __last_spins = __i;
            __spin_max = __high_spin_max;
            return;
        }
    }
   
    __spin_max = __low_spin_max;
    for (__i = 0 ;; ++__i) {
        struct timespec __ts;
        int __log_nsec = __i + 6;

        if (!__test_and_set((unsigned long *)__lock, 1)) {
            return;
        }
        if (__log_nsec > 27) __log_nsec = 27;
		/* Max sleep is 2**27nsec ~ 60msec      */
        __ts.tv_sec = 0;
        __ts.tv_nsec = 1 << __log_nsec;
        nanosleep(&__ts, 0);
    }
}

template <bool __threads, int __inst>
inline void
__default_alloc_template<__threads, __inst>::_S_unlock(
  volatile unsigned long* __lock)
{
#   if defined(__GNUC__) && __mips__ >= 3
        asm("sync");
        *__lock = 0;
#   elif __mips__ >= 3 && (defined (_ABIN32) || defined(_ABI64))
        __lock_release(__lock);
#   else
        *__lock = 0;
       
       
#   endif
}
#endif

template <bool __threads, int __inst>
char* __default_alloc_template<__threads, __inst>::_S_start_free = 0;

template <bool __threads, int __inst>
char* __default_alloc_template<__threads, __inst>::_S_end_free = 0;

template <bool __threads, int __inst>
size_t __default_alloc_template<__threads, __inst>::_S_heap_size = 0;

template <bool __threads, int __inst>
__default_alloc_template<__threads, __inst>::_Obj* __VOLATILE
__default_alloc_template<__threads, __inst> ::_S_free_list[
    _NFREELISTS
] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };




# ifdef __STL_WIN32THREADS
 
 
 
  static alloc __node_allocator_dummy_instance;
# endif

#endif /* ! __USE_MALLOC */









#ifdef __STL_USE_STD_ALLOCATORS

template <class _Tp>
class allocator {
  typedef alloc _Alloc;         
public:
  typedef size_t     size_type;
  typedef ptrdiff_t  difference_type;
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;
  typedef _Tp        value_type;

  template <class _Tp1> struct rebind {
    typedef allocator<_Tp1> other;
  };

  allocator() __STL_NOTHROW {}
  allocator(const allocator&) __STL_NOTHROW {}
  template <class _Tp1> allocator(const allocator<_Tp1>&) __STL_NOTHROW {}
  ~allocator() __STL_NOTHROW {}

  pointer address(reference __x) const { return &__x; }
  const_pointer address(const_reference __x) const { return &__x; }

 
 
  _Tp* allocate(size_type __n, const void* = 0) {
    return __n != 0 ? static_cast<_Tp*>(_Alloc::allocate(__n * sizeof(_Tp)))
                    : 0;
  }

 
  void deallocate(pointer __p, size_type __n)
    { _Alloc::deallocate(__p, __n * sizeof(_Tp)); }

  size_type max_size() const __STL_NOTHROW
    { return size_t(-1) / sizeof(_Tp); }

  void construct(pointer __p, const _Tp& __val) { new(__p) _Tp(__val); }
  void destroy(pointer __p) { __p->~_Tp(); }
};

template<>
class allocator<void> {
  typedef size_t      size_type;
  typedef ptrdiff_t   difference_type;
  typedef void*       pointer;
  typedef const void* const_pointer;
  typedef void        value_type;

  template <class _Tp1> struct rebind {
    typedef allocator<_Tp1> other;
  };
};


template <class _T1, class _T2>
inline bool operator==(const allocator<_T1>&, const allocator<_T2>&)
{
  return true;
}

template <class _T1, class _T2>
inline bool operator!=(const allocator<_T1>&, const allocator<_T2>&)
{
  return false;
}








template <class _Tp, class _Alloc>
struct __allocator {
  _Alloc __underlying_alloc;

  typedef size_t    size_type;
  typedef ptrdiff_t difference_type;
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;
  typedef _Tp        value_type;

  template <class _Tp1> struct rebind {
    typedef __allocator<_Tp1, _Alloc> other;
  };

  __allocator() __STL_NOTHROW {}
  __allocator(const __allocator& __a) __STL_NOTHROW
    : __underlying_alloc(__a.__underlying_alloc) {}
  template <class _Tp1>
  __allocator(const __allocator<_Tp1, _Alloc>& __a) __STL_NOTHROW
    : __underlying_alloc(__a.__underlying_alloc) {}
  ~__allocator() __STL_NOTHROW {}

  pointer address(reference __x) const { return &__x; }
  const_pointer address(const_reference __x) const { return &__x; }

 
  _Tp* allocate(size_type __n, const void* = 0) {
    return __n != 0
        ? static_cast<_Tp*>(__underlying_alloc.allocate(__n * sizeof(_Tp)))
        : 0;
  }

 
  void deallocate(pointer __p, size_type __n)
    { __underlying_alloc.deallocate(__p, __n * sizeof(_Tp)); }

  size_type max_size() const __STL_NOTHROW
    { return size_t(-1) / sizeof(_Tp); }

  void construct(pointer __p, const _Tp& __val) { new(__p) _Tp(__val); }
  void destroy(pointer __p) { __p->~_Tp(); }
};

template <class _Alloc>
class __allocator<void, _Alloc> {
  typedef size_t      size_type;
  typedef ptrdiff_t   difference_type;
  typedef void*       pointer;
  typedef const void* const_pointer;
  typedef void        value_type;

  template <class _Tp1> struct rebind {
    typedef __allocator<_Tp1, _Alloc> other;
  };
};

template <class _Tp, class _Alloc>
inline bool operator==(const __allocator<_Tp, _Alloc>& __a1,
                       const __allocator<_Tp, _Alloc>& __a2)
{
  return __a1.__underlying_alloc == __a2.__underlying_alloc;
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class _Tp, class _Alloc>
inline bool operator!=(const __allocator<_Tp, _Alloc>& __a1,
                       const __allocator<_Tp, _Alloc>& __a2)
{
  return __a1.__underlying_alloc != __a2.__underlying_alloc;
}
#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */





template <int inst>
inline bool operator==(const __malloc_alloc_template<inst>&,
                       const __malloc_alloc_template<inst>&)
{
  return true;
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <int __inst>
inline bool operator!=(const __malloc_alloc_template<__inst>&,
                       const __malloc_alloc_template<__inst>&)
{
  return false;
}
#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

#ifndef __USE_MALLOC
template <bool __threads, int __inst>
inline bool operator==(const __default_alloc_template<__threads, __inst>&,
                       const __default_alloc_template<__threads, __inst>&)
{
  return true;
}

# ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <bool __threads, int __inst>
inline bool operator!=(const __default_alloc_template<__threads, __inst>&,
                       const __default_alloc_template<__threads, __inst>&)
{
  return false;
}
# endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */
#endif

template <class _Alloc>
inline bool operator==(const debug_alloc<_Alloc>&,
                       const debug_alloc<_Alloc>&) {
  return true;
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class _Alloc>
inline bool operator!=(const debug_alloc<_Alloc>&,
                       const debug_alloc<_Alloc>&) {
  return false;
}
#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */





























template <class _Tp, class _Allocator>
struct _Alloc_traits
{
  static const bool _S_instanceless = false;
  typedef typename _Allocator::__STL_TEMPLATE rebind<_Tp>::other
          allocator_type;
};

template <class _Tp, class _Allocator>
const bool _Alloc_traits<_Tp, _Allocator>::_S_instanceless;



template <class _Tp, class _Tp1>
struct _Alloc_traits<_Tp, allocator<_Tp1> >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, alloc> _Alloc_type;
  typedef allocator<_Tp> allocator_type;
};



template <class _Tp, int __inst>
struct _Alloc_traits<_Tp, __malloc_alloc_template<__inst> >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, __malloc_alloc_template<__inst> > _Alloc_type;
  typedef __allocator<_Tp, __malloc_alloc_template<__inst> > allocator_type;
};

#ifndef __USE_MALLOC
template <class _Tp, bool __threads, int __inst>
struct _Alloc_traits<_Tp, __default_alloc_template<__threads, __inst> >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, __default_alloc_template<__threads, __inst> >
          _Alloc_type;
  typedef __allocator<_Tp, __default_alloc_template<__threads, __inst> >
          allocator_type;
};
#endif

template <class _Tp, class _Alloc>
struct _Alloc_traits<_Tp, debug_alloc<_Alloc> >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, debug_alloc<_Alloc> > _Alloc_type;
  typedef __allocator<_Tp, debug_alloc<_Alloc> > allocator_type;
};




template <class _Tp, class _Tp1, int __inst>
struct _Alloc_traits<_Tp,
                     __allocator<_Tp1, __malloc_alloc_template<__inst> > >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, __malloc_alloc_template<__inst> > _Alloc_type;
  typedef __allocator<_Tp, __malloc_alloc_template<__inst> > allocator_type;
};

#ifndef __USE_MALLOC
template <class _Tp, class _Tp1, bool __thr, int __inst>
struct _Alloc_traits<_Tp,
                      __allocator<_Tp1,
                                  __default_alloc_template<__thr, __inst> > >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, __default_alloc_template<__thr,__inst> >
          _Alloc_type;
  typedef __allocator<_Tp, __default_alloc_template<__thr,__inst> >
          allocator_type;
};
#endif

template <class _Tp, class _Tp1, class _Alloc>
struct _Alloc_traits<_Tp, __allocator<_Tp1, debug_alloc<_Alloc> > >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, debug_alloc<_Alloc> > _Alloc_type;
  typedef __allocator<_Tp, debug_alloc<_Alloc> > allocator_type;
};


#endif /* __STL_USE_STD_ALLOCATORS */

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1174
#endif

__STL_END_NAMESPACE

#undef __PRIVATE

#endif /* __SGI_STL_INTERNAL_ALLOC_H */




