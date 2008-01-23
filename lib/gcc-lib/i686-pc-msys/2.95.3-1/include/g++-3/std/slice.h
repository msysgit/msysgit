






























#ifndef __SLICE__
#define __SLICE__

extern "C++" {

class slice
{
public:
    slice ();
    slice (size_t, size_t, size_t);

    size_t start () const;
    size_t size () const;
    size_t stride () const;

private:
    size_t _M_off;                     
    size_t _M_sz;		
    size_t _M_st;		
};

inline slice::slice () {}

inline slice::slice (size_t __o, size_t __d, size_t __s)
        : _M_off (__o), _M_sz (__d), _M_st (__s) {}

inline size_t
slice::start () const
  { return _M_off; }

inline size_t
slice::size () const
  { return _M_sz; }

inline size_t
slice::stride () const
  { return _M_st; }

}
    
#endif




