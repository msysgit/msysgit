#!/bin/sh
MSYSTEM=MSYS

cd /perl/perl-5.6.1

./Configure -de

LIB= make
