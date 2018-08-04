#!/bin/bash

if [ $# -lt 1 ]; then
    echo "USAGE: sh $0 data-label [bytes=320]"
    exit 1
fi

WANTED_BYTES=$2
if [ -z $2 ]; then
    WANTED_BYTES=320
fi

mkdir -p data

START=`date +%s`

stty -F /dev/ttyUSB0 115200
cat /dev/ttyUSB0 \
	 | dd  count=$WANTED_BYTES status=none \
	 | tee data/$1.bin

STOP=`date +%s`
SPEED="$(( $WANTED_BYTES * 8 / ( $STOP - $START ) ))"

echo "$SPEED bit/s"
