


























#ifndef __STRING_CHAR_TRAITS__
#define __STRING_CHAR_TRAITS__

#ifdef __GNUG__

#pragma interface "std/straits.h"
#endif

#include <cstddef>

extern "C++" {
template <class charT>
struct string_char_traits {
  typedef charT char_type;

 

  static void assign (char_type& c1, const char_type& c2)
    { c1 = c2; }
  static bool eq (const char_type& c1, const char_type& c2)
    { return (c1 == c2); }
  static bool ne (const char_type& c1, const char_type& c2)
    { return !(c1 == c2); }
  static bool lt (const char_type& c1, const char_type& c2)
    { return (c1 < c2); }
  static char_type eos () { return char_type(); }
  static bool is_del(char_type a) { return 0; }
 
  
 

  static int compare (const char_type* s1, const char_type* s2, size_t n)
    {
      size_t i;
      for (i = 0; i < n; ++i)
	if (ne (s1[i], s2[i]))
	  return lt (s1[i], s2[i]) ? -1 : 1;

      return 0;
    }
    
  static size_t length (const char_type* s)
    {
      size_t l = 0;
      while (ne (*s++, eos ()))
	++l;
      return l;
    }

  static char_type* copy (char_type* s1, const char_type* s2, size_t n)
    {
      for (; n--; )
	assign (s1[n], s2[n]);
      return s1;
    }

  static char_type* move (char_type* s1, const char_type* s2, size_t n)
    {
      char_type a[n];
      size_t i;
      for (i = 0; i < n; ++i)
	assign (a[i], s2[i]);
      for (i = 0; i < n; ++i)
	assign (s1[i], a[i]);
      return s1;
    }

  static char_type* set (char_type* s1, const char_type& c, size_t n)
    {
      for (; n--; )
	assign (s1[n], c);
      return s1;
    }
};

class istream;
class ostream;
#include <cctype>
#include <cstring>

struct string_char_traits <char> {
  typedef char char_type;

  static void assign (char_type& c1, const char_type& c2)
    { c1 = c2; }
  static bool eq (const char_type & c1, const char_type& c2)
    { return (c1 == c2); }
  static bool ne (const char_type& c1, const char_type& c2)
    { return (c1 != c2); }
  static bool lt (const char_type& c1, const char_type& c2)
    { return (c1 < c2); }
  static char_type eos () { return 0; }
  static bool is_del(char_type a) { return isspace(a); }

  static int compare (const char_type* s1, const char_type* s2, size_t n)
    { return memcmp (s1, s2, n); }
  static size_t length (const char_type* s)
    { return strlen (s); }
  static char_type* copy (char_type* s1, const char_type* s2, size_t n)
    { return (char_type*) memcpy (s1, s2, n); }
  static char_type* move (char_type* s1, const char_type* s2, size_t n)
    { return (char_type*) memmove (s1, s2, n); }
  static char_type* set (char_type* s1, const char_type& c, size_t n)
    { return (char_type*) memset (s1, c, n); }
};

#if 0
#include <cwctype>
struct string_char_traits <wchar_t> {
  typedef wchar_t char_type;

  static void assign (char_type& c1, const char_type& c2)
    { c1 = c2; }
  static bool eq (const char_type & c1, const char_type& c2)
    { return (c1 == c2); }
  static bool ne (const char_type& c1, const char_type& c2)
    { return (c1 != c2); }
  static bool lt (const char_type& c1, const char_type& c2)
    { return (c1 < c2); }
  static char_type eos () { return 0; }
  static bool is_del(char_type a) { return iswspace(a); }

  static int compare (const char_type* s1, const char_type* s2, size_t n)
    { return wmemcmp (s1, s2, n); }
  static size_t length (const char_type* s)
    { return wcslen (s); }
  static char_type* copy (char_type* s1, const char_type* s2, size_t n)
    { return wmemcpy (s1, s2, n); }
  static char_type* set (char_type* s1, const char_type& c, size_t n)
    { return wmemset (s1, c, n); }
};
#endif
}
#endif
