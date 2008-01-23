/* This is part of libio/iostream, providing -*- C++ -*- input/output.
Copyright (C) 1993 Free Software Foundation

This file is part of the GNU IO Library.  This library is free
software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option)
any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this library; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

As a special exception, if you link this library with files
compiled with a GNU compiler to produce an executable, this does not cause
the resulting executable to be covered by the GNU General Public License.
This exception does not however invalidate any other reasons why
the executable file might be covered by the GNU General Public License.

Written by Per Bothner (bothner@cygnus.com). */

#ifndef PARSESTREAM_H
#define PARSESTREAM_H
#ifdef __GNUG__
#pragma interface
#endif
#include "streambuf.h"

extern "C++" {








class parsebuf : public streambuf {
  protected:
    _IO_off_t pos_at_line_start;
    long _line_length;
    unsigned long __line_number;
    char *buf_start;
    char *buf_end;

  public:
    parsebuf *chain;

   
   
    virtual int tell_in_line();

   
   
   
    virtual int seek_in_line(int i);

   

   
   
    int line_number() { return __line_number; }

   
    int line_length() { return _line_length; }
   
    virtual char* current_line();
    virtual streampos seekoff(streamoff, _seek_dir, int mode=ios::in|ios::out);
    virtual streambuf* setbuf(char* p, int len);
  protected:
    parsebuf() { chain= NULL;
	__line_number = 0; pos_at_line_start = 0; _line_length = -1; }
    virtual int pbackfail(int c);
};



class string_parsebuf : public parsebuf {
  public:
    int do_delete;
    string_parsebuf(char *str, int len, int delete_at_close=0);
    virtual int underflow();
    virtual char* current_line();
    virtual int seek_in_line(int i);
    virtual int tell_in_line();
    char *left() const { return base(); }
    char *right() const { return ebuf(); }

};
















typedef char *(*CharReader)(void *arg);
class istream;

class func_parsebuf : public parsebuf {
  public:
    void *arg;
    CharReader read_func;
    int backed_up_to_newline;
    func_parsebuf(CharReader func, void *argm = NULL);
    int underflow();
    virtual int tell_in_line();
    virtual int seek_in_line(int i);
    virtual char* current_line();
};




class general_parsebuf : public parsebuf {
  public:
    streambuf *sbuf;
    int delete_buf;
    general_parsebuf(streambuf *buf, int delete_arg_buf = 0);
    int underflow();
    virtual int tell_in_line();
    virtual int seek_in_line(int i);
    ~general_parsebuf();
    virtual char* current_line();
};

#if 0
class parsestream : public istream {
    streammarker marks[2];
    short _first;
    int _lineno;
    int first() { return _first; }
    int second() { return 1-_first; }
    int line_length() { marks[second].delta(marks[first]); }
    int line_length() { marks[second].delta(marks[first]); }
    int seek_in_line(int i);
    int tell_in_line();
    int line_number();
};
#endif
}
#endif /*!defined(PARSESTREAM_H)*/
