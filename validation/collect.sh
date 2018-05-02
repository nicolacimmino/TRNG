#!/bin/bash

if [ $# -lt 1 ]; then
    echo "USAGE: sh $0 data-label [bytes=320]"
    exit 1
fi

WANTED_BYTES=$2
if [ -z $2 ]; then
    WANTED_BYTES=320
fi

WANTED_BLOCKS=`expr $WANTED_BYTES / 32`

mkdir -p data

stty -F /dev/ttyUSB0 115200
cat /dev/ttyUSB0 \
	 | sed -u -e "s/^\.*//g" \
	 | sed -u -e "s/[^a-Z^0-9^\.^\r^\n]*//g" \
	 | dd  iflag=fullblock bs=96 count=$WANTED_BLOCKS status=none \
	 | tee data/$1.hex

