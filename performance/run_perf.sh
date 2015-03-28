#! /bin/sh
#
# run_perf.sh
# Copyright (C) 2015 liuben <liuben@ubuntu>
#
# Distributed under terms of the MIT license.
#
function total_secods() {
   m=`echo "$1"|awk -F "m" '{print $1}'`
   s=`echo "$1"|awk -F "m|s" '{print $2}'`

   t=`echo "scale=3;$m * 60 + $s"|bc`
   echo $t
}

function speed() {
    if [ "xx$2" == "xx" ] ; then
        (time $1) > time.out 2>&1
    else
        (time $1 $2) > time.out 2>&1
    fi
    v=`cat time.out|grep real|awk '{print $2}'`
    timespan=`total_secods $v`
    speed=`echo "scale=3;$MSG_NUMBER/$timespan"|bc`
    echo "[$which] speed is $speed, message number $MSG_NUMBER, used time $timespan seconds" >> ../test_result.txt
}

function makeit() {
   cd zmq
   make
   cd ..
   cd unixsocket
   make 
   cd ..
   cd socket
   make
   cd ..
   cd msgqueue
   make
   cd ..
   cd file
   make
   cd ..
   cd pipe
   make
   cd ..
}

echo "" > test_result.txt
makeit
which=""
sleeptime=1
MSG_NUMBER=100000
cd zmq
which="zmq"
nohup ./pull > /dev/null 2>&1 &
sleep $sleeptime
speed ./push $MSG_NUMBER
cd ..

cd unixsocket
which="unixsocket"
nohup ./server $MSG_NUMBER  > /dev/null 2>&1 &
sleep $sleeptime
speed ./client
cd ..

cd socket 
which="socket"
nohup ./server $MSG_NUMBER  > /dev/null 2>&1 &
sleep $sleeptime
speed ./client
cd ..

cd pipe 
which="pipe"
nohup ./read  > /dev/null 2>&1 &
sleep $sleeptime
speed ./write $MSG_NUMBER
cd ..

cd msgqueue
which="msgqueue"
nohup ./msgrecv  > /dev/null 2>&1 &
sleep $sleeptime
speed ./msgsend $MSG_NUMBER
cd ..

cd file
which="file-write"
speed ./write $MSG_NUMBER
sleep $sleeptime
which="file-read"
speed ./read
cd ..


echo "run result as follows..."
cat test_result.txt |sort -k 4 -n -r
