/*    mg.h
 *
 *    Copyright (C) 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1999,
 *    2000, 2002, by Larry Wall and others
 *
 *    You may distribute under the terms of either the GNU General Public
 *    License or the Artistic License, as specified in the README file.
 *
 */

#ifdef STRUCT_MGVTBL_DEFINITION
STRUCT_MGVTBL_DEFINITION;
#else
struct mgvtbl {
    int		(CPERLscope(*svt_get))	(pTHX_ SV *sv, MAGIC* mg);
    int		(CPERLscope(*svt_set))	(pTHX_ SV *sv, MAGIC* mg);
    U32		(CPERLscope(*svt_len))	(pTHX_ SV *sv, MAGIC* mg);
    int		(CPERLscope(*svt_clear))(pTHX_ SV *sv, MAGIC* mg);
    int		(CPERLscope(*svt_free))	(pTHX_ SV *sv, MAGIC* mg);
    int		(CPERLscope(*svt_copy))	(pTHX_ SV *sv, MAGIC* mg,
    					SV *nsv, const char *name, int namlen);
    int		(CPERLscope(*svt_dup))	(pTHX_ MAGIC *mg, CLONE_PARAMS *param);
};
#endif

struct magic {
    MAGIC*	mg_moremagic;
    MGVTBL* mg_virtual;	/* pointer to magic functions */
    U16		mg_private;
    char	mg_type;
    U8		mg_flags;
    SV*		mg_obj;
    char*	mg_ptr;
    I32		mg_len;
};

#define MGf_TAINTEDDIR 1        /* PERL_MAGIC_envelem only */
#define MGf_MINMATCH   1        /* PERL_MAGIC_regex_global only */
#define MGf_REFCOUNTED 2
#define MGf_GSKIP      4
#define MGf_COPY       8
#define MGf_DUP        16

#define MgTAINTEDDIR(mg)	(mg->mg_flags & MGf_TAINTEDDIR)
#define MgTAINTEDDIR_on(mg)	(mg->mg_flags |= MGf_TAINTEDDIR)
#define MgTAINTEDDIR_off(mg)	(mg->mg_flags &= ~MGf_TAINTEDDIR)

#define MgPV(mg,lp)		((((int)(lp = (mg)->mg_len)) == HEf_SVKEY) ?   \
				 SvPV((SV*)((mg)->mg_ptr),lp) :		\
				 (mg)->mg_ptr)
#define MgPV_const(mg,lp)	((((int)(lp = (mg)->mg_len)) == HEf_SVKEY) ? \
				 SvPV_const((SV*)((mg)->mg_ptr),lp) :        \
				 (const char*)(mg)->mg_ptr)
#define MgPV_nolen_const(mg)	(((((int)(mg)->mg_len)) == HEf_SVKEY) ?   \
				 SvPV_nolen_const((SV*)((mg)->mg_ptr)) :  \
				 (const char*)(mg)->mg_ptr)

#define SvTIED_mg(sv,how) \
    (SvRMAGICAL(sv) ? mg_find((sv),(how)) : Null(MAGIC*))
#define SvTIED_obj(sv,mg) \
    ((mg)->mg_obj ? (mg)->mg_obj : sv_2mortal(newRV(sv)))
