






























#ifndef __GSLICE__
#define __GSLICE__

extern "C++" {

struct _Indexer {
    size_t _M_count;
    size_t _M_start;
    valarray<size_t> _M_size;
    valarray<size_t> _M_stride;
    valarray<size_t> _M_index;
    _Indexer(size_t, const valarray<size_t>&, const valarray<size_t>&);
    void _M_increment_use() { ++_M_count; }
    size_t _M_decrement_use() { return --_M_count; }
};

    
class gslice
{
public:
    gslice ();
    gslice (size_t, const valarray<size_t>&, const valarray<size_t>&);
    gslice(const gslice&);
    ~gslice();

    gslice& operator= (const gslice&);
    size_t           start () const;
    valarray<size_t> size () const;
    valarray<size_t> stride () const;
    
private:
    _Indexer* _M_index;
    
    template<typename _Tp> friend class valarray;
};
    
inline size_t
gslice::start () const
{ return _M_index ? _M_index->_M_start : 0; }

inline valarray<size_t>
gslice::size () const
{ return _M_index ? _M_index->_M_size : valarray<size_t>(); }

inline valarray<size_t>
gslice::stride () const
{ return _M_index ? _M_index->_M_stride : valarray<size_t>(); }

inline gslice::gslice () : _M_index(0) {}

inline
gslice::gslice(size_t __o, const valarray<size_t>& __l,
               const valarray<size_t>& __s)
        : _M_index(new _Indexer(__o, __l, __s)) {}

inline
gslice::gslice(const gslice& __g) : _M_index(__g._M_index)
{ if (_M_index) _M_index->_M_increment_use(); }

inline
gslice::~gslice()
{ if (_M_index && _M_index->_M_decrement_use() == 0) delete _M_index; }

inline gslice&
gslice::operator= (const gslice& __g)
{
    if (__g._M_index) __g._M_index->_M_increment_use();
    if (_M_index && _M_index->_M_decrement_use() == 0) delete _M_index;
    _M_index = __g._M_index;
    return *this;
}


}

#endif




