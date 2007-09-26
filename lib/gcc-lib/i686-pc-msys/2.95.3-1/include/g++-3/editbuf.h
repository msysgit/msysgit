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

#ifndef _EDITBUF_H
#define _EDITBUF_H
#ifdef __GNUG__
#pragma interface
#endif
#include <stdio.h>
#include <fstream.h>

extern "C++" {
typedef unsigned long mark_pointer;


typedef /*unsigned*/ char buf_char;


typedef long buf_index;
			

typedef long buf_offset; 

#if 0
struct buf_cookie {
    FILE *file;
    struct edit_string *str;
    struct buf_cookie *next;
    buf_index tell();
};
#endif

struct edit_buffer;
struct edit_mark;





struct edit_string {
    struct edit_buffer *buffer;
    struct edit_mark *start, *end;
    int length() const;
    edit_string(struct edit_buffer *b,
		      struct edit_mark *ms, struct edit_mark *me)
	{ buffer = b; start = ms; end = me; }
/* Make a fresh, contiguous copy of the data in STR.
   Assign length of STR to *LENP.
   (Output has extra NUL at out[*LENP].) */
    buf_char *copy_bytes(int *lenp) const;

    void assign(struct edit_string *src);
};

struct edit_streambuf : public streambuf {
    friend edit_buffer;
    edit_string *str;
    edit_streambuf* next;
    short _mode;
    edit_streambuf(edit_string* bstr, int mode);
    ~edit_streambuf();
    virtual int underflow();
    virtual int overflow(int c = EOF);
    virtual streampos seekoff(streamoff, _seek_dir, int mode=ios::in|ios::out);
    void flush_to_buffer();
    void flush_to_buffer(edit_buffer* buffer);
    int _inserting;
    int inserting() { return _inserting; }
    void inserting(int i) { _inserting = i; }

    int truncate();
    int is_reading() { return gptr() != NULL; }
    buf_char* current() { return is_reading() ? gptr() : pptr(); }
    void set_current(char *p, int is_reading);
  protected:
    void disconnect_gap_from_file(edit_buffer* buffer);
};








struct edit_mark {
    struct edit_mark *chain;
    mark_pointer _pos;
    inline int insert_before() { return _pos & 1; }
    inline unsigned long index_in_buffer(struct edit_buffer *)
	{ return _pos >> 1; }
    inline buf_char *ptr(struct edit_buffer *buf);
    buf_index tell();
    edit_mark() { }
    edit_mark(struct edit_string *str, long delta);
    edit_buffer *buffer();
    ~edit_mark();
};














struct edit_buffer {
    buf_char *data; /* == emacs buffer_text.p1+1 */
    buf_char *_gap_start;
    edit_streambuf* _writer;
    inline buf_char *gap_start()
	{ return _writer ? _writer->pptr() : _gap_start; }
    buf_offset __gap_end_pos;
    /* int gap; implicit: buf_size - size1 - size2 */
    int buf_size;
    struct edit_streambuf *files;
    struct edit_mark start_mark;
    struct edit_mark end_mark;
    edit_buffer();
    inline buf_offset gap_end_pos() { return __gap_end_pos; }
    inline struct edit_mark *start_marker() { return &start_mark; }
    inline struct edit_mark *end_marker() { return &end_mark; }
/* these should be protected, ultimately */
    buf_index tell(edit_mark*);
    buf_index tell(buf_char*);
    inline buf_char *gap_end() { return data + gap_end_pos(); }
    inline int gap_size() { return gap_end() - gap_start(); }
    inline int size1() { return gap_start() - data; }
    inline int size2() { return buf_size - gap_end_pos(); }
    inline struct edit_mark * mark_list() { return &start_mark; }
    void make_gap (buf_offset);
    void move_gap (buf_offset pos);
    void move_gap (buf_char *pos) { move_gap(pos - data); }
    void gap_left (int pos);
    void gap_right (int pos);
    void adjust_markers(mark_pointer low, mark_pointer high,
			int amount, buf_char *old_data);
    void delete_range(buf_index from, buf_index to);
    void delete_range(struct edit_mark *start, struct edit_mark *end);
};

extern buf_char * bstr_copy(struct edit_string *str, int *lenp);



inline buf_char *edit_mark::ptr(struct edit_buffer *buf)
	{ return buf->data + index_in_buffer(buf); }

inline void edit_streambuf::flush_to_buffer()
{
    edit_buffer* buffer = str->buffer;
    if (buffer->_writer == this) flush_to_buffer(buffer);
}
}
#endif /* !_EDITBUF_H*/

