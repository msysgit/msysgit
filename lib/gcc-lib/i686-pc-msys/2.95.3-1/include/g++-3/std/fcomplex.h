


























#ifndef __FCOMPLEX__
#define __FCOMPLEX__

#ifdef __GNUG__
#pragma interface "fcomplex"
#endif

extern "C++" {
class complex<float>
{
public:
  complex (float r = 0, float i = 0): re (r), im (i) { }
  explicit complex (const complex<double>& r);
  explicit complex (const complex<long double>& r);

  complex& operator+= (const complex& r) { return __doapl (this, r); }
  complex& operator-= (const complex& r) { return __doami (this, r); }
  complex& operator*= (const complex& r) { return __doaml (this, r); }
  complex& operator/= (const complex& r) { return __doadv (this, r); }

  float real () const { return re; }
  float imag () const { return im; }
private:
  float re, im;

  friend complex& __doapl<> (complex *, const complex&);
  friend complex& __doami<> (complex *, const complex&);
  friend complex& __doaml<> (complex *, const complex&);
  friend complex& __doadv<> (complex *, const complex&);

#ifndef __STRICT_ANSI__
  friend inline complex operator + (const complex& x, float y)
    { return operator+<> (x, y); }
  friend inline complex operator + (float x, const complex& y)
    { return operator+<> (x, y); }
  friend inline complex operator - (const complex& x, float y)
    { return operator-<> (x, y); }
  friend inline complex operator - (float x, const complex& y)
    { return operator-<> (x, y); }
  friend inline complex operator * (const complex& x, float y)
    { return operator*<> (x, y); }
  friend inline complex operator * (float x, const complex& y)
    { return operator*<> (x, y); }
  friend inline complex operator / (const complex& x, float y)
    { return operator/<> (x, y); }
  friend inline complex operator / (float x, const complex& y)
    { return operator/<> (x, y); }
  friend inline bool operator == (const complex& x, float y)
    { return operator==<> (x, y); }
  friend inline bool operator == (float x, const complex& y)
    { return operator==<> (x, y); }
  friend inline bool operator != (const complex& x, float y)
    { return operator!=<> (x, y); }
  friend inline bool operator != (float x, const complex& y)
    { return operator!=<> (x, y); }
#endif /* __STRICT_ANSI__ */
};
}

#endif
