






























#ifndef __INDIRECT_ARRAY__
#define __INDIRECT_ARRAY__

extern "C++" {

template <class _Tp> class indirect_array
{
public:
    typedef _Tp value_type;
    
    void operator=  (const valarray<_Tp>&) const;
    void operator*= (const valarray<_Tp>&) const;
    void operator/= (const valarray<_Tp>&) const;
    void operator%= (const valarray<_Tp>&) const; 
    void operator+= (const valarray<_Tp>&) const;
    void operator-= (const valarray<_Tp>&) const;  
    void operator^= (const valarray<_Tp>&) const;
    void operator&= (const valarray<_Tp>&) const;
    void operator|= (const valarray<_Tp>&) const;
    void operator<<= (const valarray<_Tp>&) const;
    void operator>>= (const valarray<_Tp>&) const; 
    void operator= (const _Tp&);
    
    template<class _Dom>
    void operator=  (const _Expr<_Dom, _Tp>&) const;
    template<class _Dom>
    void operator*= (const _Expr<_Dom, _Tp>&) const;
    template<class _Dom>
    void operator/= (const _Expr<_Dom, _Tp>&) const;
    template<class _Dom>
    void operator%= (const _Expr<_Dom, _Tp>&) const;
    template<class _Dom>
    void operator+= (const _Expr<_Dom, _Tp>&) const;
    template<class _Dom>
    void operator-= (const _Expr<_Dom, _Tp>&) const;
    template<class _Dom>
    void operator^= (const _Expr<_Dom, _Tp>&) const;
    template<class _Dom>
    void operator&= (const _Expr<_Dom, _Tp>&) const;
    template<class _Dom>
    void operator|= (const _Expr<_Dom, _Tp>&) const;
    template<class _Dom>
    void operator<<= (const _Expr<_Dom, _Tp>&) const;
    template<class _Dom>
    void operator>>= (const _Expr<_Dom, _Tp>&) const; 
    
private:
    indirect_array (const indirect_array&);
    indirect_array (_Array<_Tp>, size_t, _Array<size_t>);
    
    friend class valarray<_Tp>;
    friend class gslice_array<_Tp>;
    
    const size_t 	 _M_sz;
    const _Array<size_t> _M_index;
    const _Array<_Tp> 	 _M_array;
    
   
    indirect_array ();
    indirect_array& operator= (const indirect_array&);
};

template<typename _Tp>
inline indirect_array<_Tp>::indirect_array(const indirect_array<_Tp>& __a)
        : _M_sz (__a._M_sz), _M_index (__a._M_index),
          _M_array (__a._M_array) {}

template<typename _Tp>
inline
indirect_array<_Tp>::indirect_array (_Array<_Tp> __a, size_t __s, 
                                     _Array<size_t> __i)
        : _M_sz (__s), _M_index (__i), _M_array (__a) {}


template<typename _Tp>
inline void
indirect_array<_Tp>::operator= (const _Tp& __t)
{ __valarray_fill(_M_array, _M_index, _M_sz, __t); }

template<typename _Tp>
inline void
indirect_array<_Tp>::operator= (const valarray<_Tp>& __v) const
{ __valarray_copy (_Array<_Tp> (__v), _M_sz, _M_array, _M_index); }

template<typename _Tp>
template<class _Dom>
inline void
indirect_array<_Tp>::operator= (const _Expr<_Dom,_Tp>& __e) const
{ __valarray_copy (__e, _M_sz, _M_array, _M_index); }

#undef _DEFINE_VALARRAY_OPERATOR
#define _DEFINE_VALARRAY_OPERATOR(op, name)				\
template<typename _Tp>							\
inline void								\
indirect_array<_Tp>::operator##op##= (const valarray<_Tp>& __v) const	\
{									\
  _Array_augmented_##name (_M_array, _M_index, _Array<_Tp> (__v), _M_sz); \
}									\
									\
template<typename _Tp> template<class _Dom>				\
inline void								\
indirect_array<_Tp>::operator##op##= (const _Expr<_Dom,_Tp>& __e) const \
{									\
  _Array_augmented_##name (_M_array, _M_index, __e, _M_sz);		\
}

_DEFINE_VALARRAY_OPERATOR(*, multiplies)
_DEFINE_VALARRAY_OPERATOR(/, divides)
_DEFINE_VALARRAY_OPERATOR(%, modulus)
_DEFINE_VALARRAY_OPERATOR(+, plus)
_DEFINE_VALARRAY_OPERATOR(-, minus)
_DEFINE_VALARRAY_OPERATOR(^, xor)
_DEFINE_VALARRAY_OPERATOR(&, and)
_DEFINE_VALARRAY_OPERATOR(|, or)
_DEFINE_VALARRAY_OPERATOR(<<, shift_left)
_DEFINE_VALARRAY_OPERATOR(>>, shift_right)

#undef _DEFINE_VALARRAY_OPERATOR

}

#endif




