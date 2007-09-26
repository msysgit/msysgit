#! /bin/sh
#############################################################################
# msysrls.sh - Create an MSYS release                             .	    #
# Copyright (C) 2002  Earnie Boyd  <earnie@users.sf.net>                    #
#                                                                           #
# This file is part of msysDVLPR                                            #
#   http://www.mingw.org/msysDVLPR.shtml                                    #
#                                                                           #
#############################################################################

#FIXME: Need to use getopts to control PRODUCTION release, SNAPDATE, SUBVERSION,
#       etc.

# User changeable values section.
PACKAGE=msys
MAJORVER=1
MINORVER=0
PATCHVER=8
STOREROOT=/${PACKAGE}/store
RLSROOT=/${PACKAGE}/rls
RLSDEPOT=/${PACKAGE}/depot/binary/${PACKAGE}/${SHORTVER}
ARC=$1
SNAPDATE=\-`date +%Y.%m.%d`
#SNAPDATE=\-rc
#SNAPDATE=
SUBVERSION=\-1
#SUBVERSION=
#END User changeable values section.

VERSION=${MAJORVER}.${MINORVER}.${PATCHVER}
SHORTVER=${MAJORVER}.${MINORVER}
RLSOUTPUTDIR="`p2w ${RLSROOT}/${VERSION}`"

if [ -z "$SNAPDATE" ]
then
    RELEASE="Production Release${SUBVERSION}"
elif [ "x${SNAPDATE}" == "x-rc" ]
then
    RELEASE="Release Candidate${SUBVERSION}"
else
    RELEASE="Snapshot${SNAPDATE}${SUBVERSION}"
fi

istore=${STOREROOT}/${ARC}
noarchstore=${STOREROOT}/noarch
miscstore=${STOREROOT}/misc
datastore=${STOREROOT}/var

INFOBEFOREFILE="`p2w ${RLSDEPOT}/doc/msys/MSYS-${VERSION}-changes.rtf`"
INFOAFTERFILE="`p2w ${RLSDEPOT}/doc/msys//MSYS_WELCOME.rtf`"
LICENSEFILE="`p2w ${RLSDEPOT}/doc/msys/MSYS_LICENSE.rtf`"
RLSSOURCEDIR="`p2w $RLSDEPOT`"

exe_LIST="`cat ${datastore}/exe.dat`"
etc_LIST="`cat ${datastore}/etc.dat`"
dll_LIST="`cat ${datastore}/dll.dat`"
doc_LIST="`cat ${datastore}/doc.dat` MSYS-${VERSION}-changes.rtf"
misc_LIST="`cat ${datastore}/misc.dat`"
pi_LIST="`cat ${datastore}/pi.dat`"
script_LIST="`cat ${datastore}/script.dat`"

if [ ! -d ${RLSDEPOT} ]
then
  mkdir -p ${RLSDEPOT}
fi

rm -rf ${RLSDEPOT}/*

if [ ! -d ${RLSDEPOT}/bin ]
then
  mkdir ${RLSDEPOT}/bin
fi

for I in ${exe_LIST}
do
  cp ${istore}/bin/${I} ${RLSDEPOT}/bin/
done

for I in ${dll_LIST}
do
  cp ${istore}/bin/${I} ${RLSDEPOT}/bin/
done

if [ ! -d ${RLSDEPOT}/doc/msys ]
then
  mkdir -p ${RLSDEPOT}/doc/msys
fi

for I in ${doc_LIST}
do
  cat ${noarchstore}/doc/msys/${I} | sed -c -e "s/@VERSION@/$VERSION/g" -e "s/@RELEASE@/$RELEASE/g" > ${RLSDEPOT}/doc/msys/$I
done

if [ ! -d ${RLSDEPOT}/etc ]
then
  mkdir ${RLSDEPOT}/etc
fi

for I in ${etc_LIST}
do
  cp ${noarchstore}/etc/${I} ${RLSDEPOT}/etc/
done

for I in ${script_LIST}
do
  cp ${noarchstore}/bin/${I} ${RLSDEPOT}/bin/
done

for I in ${misc_LIST}
do
  case $I in
  msys.bat)
    cp ${noarchstore}/bin/${I} ${RLSDEPOT}
    ;;
  msys.ico | m.ico)
    cp ${noarchstore}/${I} ${RLSDEPOT}
    ;;
  esac
done

if [ ! -d ${RLSDEPOT}/postinstall ]
then
  mkdir ${RLSDEPOT}/postinstall
fi

for I in ${pi_LIST}
do
  cp ${noarchstore}/pi/${I} ${RLSDEPOT}/postinstall/
done

if [ ! -f ${RLSOUTPUTDIR} ]
then
  mkdir -p ${RLSOUTPUTDIR}
fi

cat msys.iss.in | \
  sed -c \
      -e "s/@VERSION@/$VERSION/g" \
      -e "s/@ARC@/$ARC/g" \
      -e "s/@SNAPDATE@/$SNAPDATE/g" \
      -e "s/@SUBVERSION@/$SUBVERSION/g" \
      -e "s%@LICENSEFILE@%${LICENSEFILE}%g" \
      -e "s%@INFOBEFOREFILE@%${INFOBEFOREFILE}%g" \
      -e "s%@INFOAFTERFILE@%${INFOAFTERFILE}%g" \
      -e "s%@RLSSOURCEDIR@%${RLSSOURCEDIR}%g" \
      -e "s%@RLSOUTPUTDIR@%${RLSOUTPUTDIR}%g" \
  > msys.iss

/c/InnoSetup2/iscc "msys.iss"
rm msys.iss
