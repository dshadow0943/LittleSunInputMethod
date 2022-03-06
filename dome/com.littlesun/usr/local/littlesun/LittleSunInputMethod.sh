#!/bin/sh 
appname=`basename $0 | sed s,\.sh$,,` 
dirname=`dirname $0` 
tmp="${dirname#?}" 
if [ "${dirname%$tmp}" != "/" ]; then 
dirname=$PWD/$dirname 
fi 
 
dbdir=~/.local/share/applications/littesun/chineseBase
if [ ! -d "${dbdir}" ]; then
	mkdir -p "${dbdir}"
fi

if [ ! -e "${dbdir}/chinese.db" ]; then
	cp /usr/local/littlesun/chineseBase/chinese.db "${dbdir}/chinese.db"
fi

LD_LIBRARY_PATH=$dirname 
export LD_LIBRARY_PATH 
$dirname/$appname "$@"
