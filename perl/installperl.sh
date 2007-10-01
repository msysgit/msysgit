#!/bin/bash

echo "Downloading perl-5.6.1.tar.gz.md5 ..." 
curl ftp://ftp.funet.fi/pub/CPAN/src/perl-5.6.1.tar.gz.md5 -o perl-5.6.1.tar.gz.md5

test -f perl-5.6.1.tar.gz \
	|| ( echo "Downloading perl-5.6.1.tar.gz ..." \
	&& curl ftp://ftp.funet.fi/pub/CPAN/src/perl-5.6.1.tar.gz -o perl-5.6.1.tar.gz)

echo -n "Verifying md5 sum ..." 
md5sum -c --status perl-5.6.1.tar.gz.md5 \
	|| ( echo "Failed"; exit )
echo "Done"

echo -n "Unpacking perl-5.6.1.tar.gz ..."
tar -xzf perl-5.6.1.tar.gz
echo "Done"

cd perl-5.6.1
git init
git add .
git commit -m "Perl 5.6.1 from perl-5.6.1.tar.gz" > /dev/null
git am ../patches/*
echo "Done"
