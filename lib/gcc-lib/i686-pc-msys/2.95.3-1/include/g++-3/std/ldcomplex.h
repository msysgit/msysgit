


























#ifndef __LDCOMPLEX__
#define __LDCOMPLEX__

#ifdef __GNUG__
#pragma interface "ldcomplex"
#endif

extern "C++" {
class complex<long double>
{
public:
  complex (long double r = 0, long double i = 0): re (r), im (i) { }
  complex (const complex<float>& r): re (r.real ()), im (r.imag ()) { }
  complex (const complex<double>& r): re (r.real ()), im (r.imag ()) { }

  complex& operator+= (const complex& r) { return __doapl (this, r); }
  complex& operator-= (const complex& r) { return __doami (this, r); }
  complex& operator*= (const complex& r) { return __doaml (this, r); }
  complex& operator/= (const complex& r) { return __doadv (this, r); }

  long double real () const { return re; }
  long double imag () const { return im; }
private:
  long double re, im;

  friend complex& __doapl<> (complex *, const complex&);
  friend complex& __doami<> (complex *, const complex&);
  friend complex& __doaml<> (complex *, const complex&);
  friend complex& __doadv<> (complex *, const complex&);

#ifndef __STRICT_ANSI__
  friend inline complex operator + (const complex& x, long double y)
    { return operator+<> (x, y); }
  friend inline complex operator + (long double x, const complex& y)
    { return operator+<> (x, y); }
  friend inline complex operator - (const complex& x, long double y)
    { return operator-<> (x, y); }
  friend inline complex operator - (long double x, const complex& y)
    { return operator-<> (x, y); }
  friend inline complex operator * (const complex& x, long double y)
    { return operator*<> (x, y); }
  friend inline complex operator * (long double x, const complex& y)
    { return operator*<> (x, y); }
  friend inline complex operator / (const complex& x, long double y)
    { return operator/<> (x, y); }
  friend inline complex operator / (long double x, const complex& y)
    { return operator/<> (x, y); }
  friend inline bool operator == (const complex& x, long double y)
    { return operator==<> (x, y); }
  friend inline bool operator == (long double x, const complex& y)
    { return operator==<> (x, y); }
  friend inline bool operator != (const complex& x, long double y)
    { return operator!=<> (x, y); }
  friend inline bool operator != (long double x, const complex& y)
    { return operator!=<> (x, y); }
#endif /* __STRICT_ANSI__ */
};

inline complex<float>::complex (const complex<long double>& r)
: re (r.real ()), im (r.imag ())
{ }

inline complex<double>::complex (const complex<long double>& r)
: re (r.real ()), im (r.imag ())
{ }
}

#endif
