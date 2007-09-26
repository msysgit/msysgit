


























#ifndef __DCOMPLEX__
#define __DCOMPLEX__

#ifdef __GNUG__
#pragma interface "dcomplex"
#endif

extern "C++" {
class complex<double>
{
public:
  complex (double r = 0, double i = 0): re (r), im (i) { }
  complex (const complex<float>& r): re (r.real ()), im (r.imag ()) { }
  explicit complex (const complex<long double>& r);

  complex& operator+= (const complex& r) { return __doapl (this, r); }
  complex& operator-= (const complex& r) { return __doami (this, r); }
  complex& operator*= (const complex& r) { return __doaml (this, r); }
  complex& operator/= (const complex& r) { return __doadv (this, r); }

  double real () const { return re; }
  double imag () const { return im; }
private:
  double re, im;

  friend complex& __doapl<> (complex *, const complex&);
  friend complex& __doami<> (complex *, const complex&);
  friend complex& __doaml<> (complex *, const complex&);
  friend complex& __doadv<> (complex *, const complex&);

#ifndef __STRICT_ANSI__
  friend inline complex operator + (const complex& x, double y)
    { return operator+<> (x, y); }
  friend inline complex operator + (double x, const complex& y)
    { return operator+<> (x, y); }
  friend inline complex operator - (const complex& x, double y)
    { return operator-<> (x, y); }
  friend inline complex operator - (double x, const complex& y)
    { return operator-<> (x, y); }
  friend inline complex operator * (const complex& x, double y)
    { return operator*<> (x, y); }
  friend inline complex operator * (double x, const complex& y)
    { return operator*<> (x, y); }
  friend inline complex operator / (const complex& x, double y)
    { return operator/<> (x, y); }
  friend inline complex operator / (double x, const complex& y)
    { return operator/<> (x, y); }
  friend inline bool operator == (const complex& x, double y)
    { return operator==<> (x, y); }
  friend inline bool operator == (double x, const complex& y)
    { return operator==<> (x, y); }
  friend inline bool operator != (const complex& x, double y)
    { return operator!=<> (x, y); }
  friend inline bool operator != (double x, const complex& y)
    { return operator!=<> (x, y); }
#endif /* __STRICT_ANSI__ */
};

inline complex<float>::complex (const complex<double>& r)
: re (r.real ()), im (r.imag ())
{ }
}

#endif
