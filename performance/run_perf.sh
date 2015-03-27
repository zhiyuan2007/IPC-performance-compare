#! /bin/sh
#
# run_perf.sh
# Copyright (C) 2015 liuben <liuben@ubuntu>
#
# Distributed under terms of the MIT license.
#

MSG_NUMBER=1000
#echo "run zmq test..."
#cd zmq
#make
#nohup ./pull &
#sleep 1
#echo "zeromq send message $MSG_NUMBER"
#time ./push  $MSG_NUMBER
#cd ..


#echo  "run unix socket test..."
#
#cd unixsocket
#make
#nohup ./server $MSG_NUMBER &
#sleep 1
#echo  "unix socket send message $MSG_NUMBER"
#time ./client
#cd ..

cd socket 
make
nohup ./server $MSG_NUMBER &
sleep 1
echo  "socket send message $MSG_NUMBER"
time ./client
cd ..

cd pipe 
make
nohup ./read &
sleep 1
echo  "pipe send message $MSG_NUMBER"
time ./write $MSG_NUMBER
cd ..

cd msgqueue
make
nohup ./msgrecv &
sleep 1
echo  "msg queue send message $MSG_NUMBER"
time ./msgsend $MSG_NUMBER
cd ..
