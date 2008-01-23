






























#ifndef __MASK_ARRAY__
#define __MASK_ARRAY__

extern "C++" {

template <class _T> class mask_array
{ 
public:
    typedef _T value_type;
    
    void operator=  (const valarray<_T>&) const;
    void operator*= (const valarray<_T>&) const;
    void operator/= (const valarray<_T>&) const;
    void operator%= (const valarray<_T>&) const;
    void operator+= (const valarray<_T>&) const; 
    void operator-= (const valarray<_T>&) const;
    void operator^= (const valarray<_T>&) const;  
    void operator&= (const valarray<_T>&) const;
    void operator|= (const valarray<_T>&) const;
    void operator<<=(const valarray<_T>&) const;  
    void operator>>=(const valarray<_T>&) const; 
    void operator= (const _T&);
    
    template<class _Dom>
    void operator=  (const _Expr<_Dom,_T>&) const;
    template<class _Dom>
    void operator*= (const _Expr<_Dom,_T>&) const;
    template<class _Dom>
    void operator/= (const _Expr<_Dom,_T>&) const;
    template<class _Dom>
    void operator%= (const _Expr<_Dom,_T>&) const;
    template<class _Dom>
    void operator+= (const _Expr<_Dom,_T>&) const;
    template<class _Dom>
    void operator-= (const _Expr<_Dom,_T>&) const;
    template<class _Dom>
    void operator^= (const _Expr<_Dom,_T>&) const;
    template<class _Dom>
    void operator&= (const _Expr<_Dom,_T>&) const;
    template<class _Dom>
    void operator|= (const _Expr<_Dom,_T>&) const;
    template<class _Dom>
    void operator<<=(const _Expr<_Dom,_T>&) const;
    template<class _Dom>
    void operator>>=(const _Expr<_Dom,_T>&) const; 
    
private:
    mask_array (_Array<_T>, size_t, _Array<bool>);
    friend class valarray<_T>;
    
    const size_t       _M_sz;
    const _Array<bool> _M_mask;
    const _Array<_T>   _M_array;
    
    mask_array (const mask_array&);
    
   
    mask_array ();
    mask_array& operator= (const mask_array&);
};

template<typename _Tp>
inline mask_array<_Tp>::mask_array (const mask_array<_Tp>& a)
        : _M_sz (a._M_sz), _M_mask (a._M_mask), _M_array (a._M_array) {}

template<typename _T>
inline 
mask_array<_T>::mask_array (_Array<_T> __a, size_t __s, _Array<bool> __m)
        : _M_sz (__s), _M_mask (__m), _M_array (__a) {}

template<typename _T>
inline void
mask_array<_T>::operator= (const _T& __t)
{ __valarray_fill (_M_array, _M_sz, _M_mask, __t); }
    
template<typename _T>
inline void
mask_array<_T>::operator= (const valarray<_T>& __v) const
{ __valarray_copy (_Array<_T> (__v), __v.size (), _M_array, _M_mask); }

template<typename _T>
template<class E>
inline void
mask_array<_T>::operator= (const _Expr<E, _T>& __e) const
{ __valarray_copy (__e, __e.size (), _M_array, _M_mask); }

#undef _DEFINE_VALARRAY_OPERATOR
#define _DEFINE_VALARRAY_OPERATOR(op, name)				\
template<typename _T>							\
inline void								\
mask_array<_T>::operator##op##= (const valarray<_T>& __v) const		\
{									\
  _Array_augmented_##name (_M_array, _M_mask, 				\
                           _Array<_T> (__v), __v.size ());		\
}									\
									\
template<typename _T> template<class E>					\
inline void								\
mask_array<_T>::operator##op##= (const _Expr<E, _T>& __e) const		\
{									\
  _Array_augmented_##name (_M_array, _M_mask, __e, __e.size ());	\
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




