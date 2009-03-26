#ifdef WIN32
/*
 * While the definitions in the original header are technically the
 * same as the definitions in 'zlibDecls.h' on Windows they are not,
 * in a small detail: DLLEXPORT vs. DLLIMPORT. As our artificial
 * definitions do the right thing we use the macro definitions below
 * to move the original definitionsd out of the way. We do retain the
 * inclusion of all the type definitions, etc.
 */
#define zlibVersion	__mask_zlibVersion
#define zError	__mask_zError
#define crc32	__mask_crc32
#define adler32	__mask_adler32
#define deflateInit_	__mask_deflateInit_
#define deflateInit2_	__mask_deflateInit2_
#define deflate	__mask_deflate
#define deflateEnd	__mask_deflateEnd
#define deflateSetDictionary	__mask_deflateSetDictionary
#define deflateCopy	__mask_deflateCopy
#define deflateReset	__mask_deflateReset
#define deflateParams	__mask_deflateParams
#define compress	__mask_compress
#define compress2	__mask_compress2
#define inflateInit_	__mask_inflateInit_
#define inflateInit2_	__mask_inflateInit2_
#define inflate	__mask_inflate
#define inflateEnd	__mask_inflateEnd
#define inflateSetDictionary	__mask_inflateSetDictionary
#define inflateSync	__mask_inflateSync
#define inflateReset	__mask_inflateReset
#define uncompress	__mask_uncompress
#define gzopen	__mask_gzopen
#define gzdopen	__mask_gzdopen
#define gzsetparams	__mask_gzsetparams
#define gzread	__mask_gzread
#define gzwrite	__mask_gzwrite
#define gzputs	__mask_gzputs
#define gzgets	__mask_gzgets
#define gzputc	__mask_gzputc
#define gzgetc	__mask_gzgetc
#define gzflush	__mask_gzflush
#define gzseek	__mask_gzseek
#define gzrewind	__mask_gzrewind
#define gztell	__mask_gztell
#define gzeof	__mask_gzeof
#define gzclose	__mask_gzclose
#define gzerror	__mask_gzerror
#endif /* WIN32 */
