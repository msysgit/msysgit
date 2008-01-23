

























#ifndef __COMPLEXT__
#define __COMPLEXT__

#ifdef __GNUG__
#pragma interface
#endif

#include <cmath>

#if ! defined (__GNUG__) && ! defined (__attribute__)
#define __attribute__(foo) /* Ignore.  */
#endif

class istream;
class ostream;

extern "C++" {
template <class _FLT> class complex;
template <class _FLT> complex<_FLT>&
  __doapl (complex<_FLT>* ths, const complex<_FLT>& r);
template <class _FLT> complex<_FLT>&
  __doami (complex<_FLT>* ths, const complex<_FLT>& r);
template <class _FLT> complex<_FLT>&
  __doaml (complex<_FLT>* ths, const complex<_FLT>& r);
template <class _FLT> complex<_FLT>&
  __doadv (complex<_FLT>* ths, const complex<_FLT>& r);

template <class _FLT>
class complex
{
public:
  complex (_FLT r = 0, _FLT i = 0): re (r), im (i) { }
  complex& operator += (const complex&);
  complex& operator -= (const complex&);
  complex& operator *= (const complex&);
  complex& operator /= (const complex&);
  _FLT real () const { return re; }
  _FLT imag () const { return im; }
private:
  _FLT re, im;

  friend complex& __doapl<> (complex *, const complex&);
  friend complex& __doami<> (complex *, const complex&);
  friend complex& __doaml<> (complex *, const complex&);
  friend complex& __doadv<> (complex *, const complex&);
};


class complex<float>;
class complex<double>;
class complex<long double>;

template <class _FLT>
inline complex<_FLT>&
__doapl (complex<_FLT>* ths, const complex<_FLT>& r)
{
  ths->re += r.re;
  ths->im += r.im;
  return *ths;
}
template <class _FLT>
inline complex<_FLT>&
complex<_FLT>::operator += (const complex<_FLT>& r)
{
  return __doapl (this, r);
}

template <class _FLT>
inline complex<_FLT>&
__doami (complex<_FLT>* ths, const complex<_FLT>& r)
{
  ths->re -= r.re;
  ths->im -= r.im;
  return *ths;
}
template <class _FLT>
inline complex<_FLT>&
complex<_FLT>::operator -= (const complex<_FLT>& r)
{
  return __doami (this, r);
}

template <class _FLT>
inline complex<_FLT>&
__doaml (complex<_FLT>* ths, const complex<_FLT>& r)
{
  _FLT f = ths->re * r.re - ths->im * r.im;
  ths->im = ths->re * r.im + ths->im * r.re;
  ths->re = f;
  return *ths;
}
template <class _FLT>
inline complex<_FLT>&
complex<_FLT>::operator *= (const complex<_FLT>& r)
{
  return __doaml (this, r);
}

template <class _FLT>
inline complex<_FLT>&
complex<_FLT>::operator /= (const complex<_FLT>& r)
{
  return __doadv (this, r);
}

template <class _FLT> inline _FLT
imag (const complex<_FLT>& x) __attribute__ ((const));

template <class _FLT> inline _FLT
imag (const complex<_FLT>& x)
{
  return x.imag ();
}

template <class _FLT> inline _FLT
real (const complex<_FLT>& x) __attribute__ ((const));

template <class _FLT> inline _FLT
real (const complex<_FLT>& x)
{
  return x.real ();
}

template <class _FLT> inline complex<_FLT>
operator + (const complex<_FLT>& x, const complex<_FLT>& y) __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
operator + (const complex<_FLT>& x, const complex<_FLT>& y)
{
  return complex<_FLT> (real (x) + real (y), imag (x) + imag (y));
}

template <class _FLT> inline complex<_FLT>
operator + (const complex<_FLT>& x, _FLT y) __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
operator + (const complex<_FLT>& x, _FLT y)
{
  return complex<_FLT> (real (x) + y, imag (x));
}

template <class _FLT> inline complex<_FLT>
operator + (_FLT x, const complex<_FLT>& y) __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
operator + (_FLT x, const complex<_FLT>& y)
{
  return complex<_FLT> (x + real (y), imag (y));
}

template <class _FLT> inline complex<_FLT>
operator - (const complex<_FLT>& x, const complex<_FLT>& y) __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
operator - (const complex<_FLT>& x, const complex<_FLT>& y)
{
  return complex<_FLT> (real (x) - real (y), imag (x) - imag (y));
}

template <class _FLT> inline complex<_FLT>
operator - (const complex<_FLT>& x, _FLT y) __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
operator - (const complex<_FLT>& x, _FLT y)
{
  return complex<_FLT> (real (x) - y, imag (x));
}

template <class _FLT> inline complex<_FLT>
operator - (_FLT x, const complex<_FLT>& y) __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
operator - (_FLT x, const complex<_FLT>& y)
{
  return complex<_FLT> (x - real (y), - imag (y));
}

template <class _FLT> inline complex<_FLT>
operator * (const complex<_FLT>& x, const complex<_FLT>& y) __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
operator * (const complex<_FLT>& x, const complex<_FLT>& y)
{
  return complex<_FLT> (real (x) * real (y) - imag (x) * imag (y),
			   real (x) * imag (y) + imag (x) * real (y));
}

template <class _FLT> inline complex<_FLT>
operator * (const complex<_FLT>& x, _FLT y) __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
operator * (const complex<_FLT>& x, _FLT y)
{
  return complex<_FLT> (real (x) * y, imag (x) * y);
}

template <class _FLT> inline complex<_FLT>
operator * (_FLT x, const complex<_FLT>& y) __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
operator * (_FLT x, const complex<_FLT>& y)
{
  return complex<_FLT> (x * real (y), x * imag (y));
}

template <class _FLT> complex<_FLT>
operator / (const complex<_FLT>& x, _FLT y) __attribute__ ((const));

template <class _FLT> complex<_FLT>
operator / (const complex<_FLT>& x, _FLT y)
{
  return complex<_FLT> (real (x) / y, imag (x) / y);
}

template <class _FLT> inline complex<_FLT>
operator + (const complex<_FLT>& x) __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
operator + (const complex<_FLT>& x)
{
  return x;
}

template <class _FLT> inline complex<_FLT>
operator - (const complex<_FLT>& x) __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
operator - (const complex<_FLT>& x)
{
  return complex<_FLT> (-real (x), -imag (x));
}

template <class _FLT> inline bool
operator == (const complex<_FLT>& x, const complex<_FLT>& y) __attribute__ ((const));

template <class _FLT> inline bool
operator == (const complex<_FLT>& x, const complex<_FLT>& y)
{
  return real (x) == real (y) && imag (x) == imag (y);
}

template <class _FLT> inline bool
operator == (const complex<_FLT>& x, _FLT y) __attribute__ ((const));

template <class _FLT> inline bool
operator == (const complex<_FLT>& x, _FLT y)
{
  return real (x) == y && imag (x) == 0;
}

template <class _FLT> inline bool
operator == (_FLT x, const complex<_FLT>& y) __attribute__ ((const));

template <class _FLT> inline bool
operator == (_FLT x, const complex<_FLT>& y)
{
  return x == real (y) && imag (y) == 0;
}

template <class _FLT> inline bool
operator != (const complex<_FLT>& x, const complex<_FLT>& y) __attribute__ ((const));

template <class _FLT> inline bool
operator != (const complex<_FLT>& x, const complex<_FLT>& y)
{
  return real (x) != real (y) || imag (x) != imag (y);
}

template <class _FLT> inline bool
operator != (const complex<_FLT>& x, _FLT y) __attribute__ ((const));

template <class _FLT> inline bool
operator != (const complex<_FLT>& x, _FLT y)
{
  return real (x) != y || imag (x) != 0;
}

template <class _FLT> inline bool
operator != (_FLT x, const complex<_FLT>& y) __attribute__ ((const));

template <class _FLT> inline bool
operator != (_FLT x, const complex<_FLT>& y)
{
  return x != real (y) || imag (y) != 0;
}


extern "C" double hypot (double, double) __attribute__ ((const));

template <class _FLT> inline _FLT
abs (const complex<_FLT>& x) __attribute__ ((const));

template <class _FLT> inline _FLT
abs (const complex<_FLT>& x)
{
  return hypot (real (x), imag (x));
}

template <class _FLT> inline _FLT
arg (const complex<_FLT>& x) __attribute__ ((const));

template <class _FLT> inline _FLT
arg (const complex<_FLT>& x)
{
  return atan2 (imag (x), real (x));
}

template <class _FLT> inline complex<_FLT>
polar (_FLT r, _FLT t) __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
polar (_FLT r, _FLT t)
{
  return complex<_FLT> (r * cos (t), r * sin (t));
}

template <class _FLT> inline complex<_FLT>
conj (const complex<_FLT>& x)  __attribute__ ((const));

template <class _FLT> inline complex<_FLT>
conj (const complex<_FLT>& x) 
{
  return complex<_FLT> (real (x), -imag (x));
}

template <class _FLT> inline _FLT
norm (const complex<_FLT>& x) __attribute__ ((const));

template <class _FLT> inline _FLT
norm (const complex<_FLT>& x)
{
  return real (x) * real (x) + imag (x) * imag (x);
}



template <class _FLT> complex<_FLT>
  operator / (const complex<_FLT>&, const complex<_FLT>&) __attribute__ ((const));
template <class _FLT> complex<_FLT>
  operator / (_FLT, const complex<_FLT>&) __attribute__ ((const));
template <class _FLT> complex<_FLT>
  cos (const complex<_FLT>&) __attribute__ ((const));
template <class _FLT> complex<_FLT>
  cosh (const complex<_FLT>&) __attribute__ ((const));
template <class _FLT> complex<_FLT>
  exp (const complex<_FLT>&) __attribute__ ((const));
template <class _FLT> complex<_FLT>
  log (const complex<_FLT>&) __attribute__ ((const));
template <class _FLT> complex<_FLT>
  pow (const complex<_FLT>&, const complex<_FLT>&) __attribute__ ((const));
template <class _FLT> complex<_FLT>
  pow (const complex<_FLT>&, _FLT) __attribute__ ((const));
template <class _FLT> complex<_FLT>
  pow (const complex<_FLT>&, int) __attribute__ ((const));
template <class _FLT> complex<_FLT>
  pow (_FLT, const complex<_FLT>&) __attribute__ ((const));
template <class _FLT> complex<_FLT>
  sin (const complex<_FLT>&) __attribute__ ((const));
template <class _FLT> complex<_FLT>
  sinh (const complex<_FLT>&) __attribute__ ((const));
template <class _FLT> complex<_FLT>
  sqrt (const complex<_FLT>&) __attribute__ ((const));

template <class _FLT> istream& operator >> (istream&, complex<_FLT>&);
template <class _FLT> ostream& operator << (ostream&, const complex<_FLT>&);
}



#include <std/fcomplex.h>
#include <std/dcomplex.h>
#include <std/ldcomplex.h>

#endif
