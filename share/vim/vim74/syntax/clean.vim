" Vim syntax file
" Language:		Clean
" Author:		Pieter van Engelen <pietere@sci.kun.nl>
" Co-Author:	Arthur van Leeuwen <arthurvl@sci.kun.nl>
" Last Change:	2013 Jun 19 by Jurriën Stutterheim

" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

let s:cpo_save = &cpo
set cpo&vim

" Some Clean-keywords
syn keyword cleanConditional if case
syn keyword cleanLabel let! with where in of
syn keyword cleanSpecial Start
syn keyword cleanKeyword infixl infixr infix
syn keyword cleanBasicType Int Real Char Bool String
syn keyword cleanSpecialType World ProcId Void Files File
syn keyword cleanModuleSystem module implementation definition system
syn keyword cleanTypeClass class instance export

" Import highlighting
syn region cleanIncludeRegion start="^\s*\(from\|import\|\s\+\(as\|qualified\)\)" end="\n" contains=cleanIncludeKeyword keepend
syn keyword cleanIncludeKeyword contained from import as qualified

" To do some Denotation Highlighting
syn keyword cleanBoolDenot True False
syn region  cleanStringDenot start=+"+ end=+"+
syn match cleanCharDenot "'.'"
syn match cleanCharsDenot "'[^'\\]*\(\\.[^'\\]\)*'" contained
syn match cleanIntegerDenot "[+-~]\=\<\(\d\+\|0[0-7]\+\|0x[0-9A-Fa-f]\+\)\>"
syn match cleanRealDenot "[+-~]\=\<\d\+\.\d+\(E[+-~]\=\d+\)\="

" To highlight the use of lists, tuples and arrays
syn region cleanList start="\[" end="\]" contains=ALL
syn region cleanRecord start="{" end="}" contains=ALL
syn region cleanArray start="{:" end=":}" contains=ALL
syn match cleanTuple "([^=]*,[^=]*)" contains=ALL

" To do some Comment Highlighting
syn region cleanComment start="/\*"  end="\*/" contains=cleanComment
syn match cleanComment "//.*"

" Now for some useful typedefinitionrecognition
syn match cleanFuncTypeDef "\([a-zA-Z].*\|(\=[-~@#$%^?!+*<>\/|&=:]\+)\=\)[ \t]*\(infix[lr]\=\)\=[ \t]*\d\=[ \t]*::.*->.*" contains=cleanSpecial

" Define the default highlighting.
" For version 5.7 and earlier: only when not done already
" For version 5.8 and later: only when an item doesn't have highlighting yet
if version >= 508 || !exists("did_clean_syntax_init")
  if version < 508
    let did_clean_syntax_init = 1
    command -nargs=+ HiLink hi link <args>
  else
    command -nargs=+ HiLink hi def link <args>
  endif

   " Comments
   HiLink cleanComment      Comment
   " Constants and denotations
   HiLink cleanCharsDenot   String
   HiLink cleanStringDenot  String
   HiLink cleanCharDenot    Character
   HiLink cleanIntegerDenot Number
   HiLink cleanBoolDenot    Boolean
   HiLink cleanRealDenot    Float
   " Identifiers
   " Statements
   HiLink cleanTypeClass    Keyword
   HiLink cleanConditional  Conditional
   HiLink cleanLabel		Label
   HiLink cleanKeyword      Keyword
   " Generic Preprocessing
   HiLink cleanIncludeKeyword      Include
   HiLink cleanModuleSystem PreProc
   " Type
   HiLink cleanBasicType    Type
   HiLink cleanSpecialType  Type
   HiLink cleanFuncTypeDef  Typedef
   " Special
   HiLink cleanSpecial      Special
   HiLink cleanList			Special
   HiLink cleanArray		Special
   HiLink cleanRecord		Special
   HiLink cleanTuple		Special
   " Error
   " Todo

  delcommand HiLink
endif

let b:current_syntax = "clean"

let &cpo = s:cpo_save
unlet s:cpo_save
" vim: ts=4
