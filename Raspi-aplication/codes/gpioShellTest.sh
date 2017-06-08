#!/bin/sh
while true
do
sensor=`cat /sys/class/gpio/gpio23/value`
sensor2=`cat /sys/class/gpio/gpio17/value`
echo $sensor
echo $sensor2
if [ $sensor -eq 1 ]&&[$sensor2 -eq 1];
then
echo 0 > /sys/class/gpio/gpio22/value
echo 0 > /sys/class/gpio/gpio27/value

sleep 3
echo 1 > /sys/class/gpio/gpio22/value
echo 1 > /sys/class/gpio/gpio27/value
fi
sleep 1
done

