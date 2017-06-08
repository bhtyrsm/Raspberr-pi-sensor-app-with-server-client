#ifndef SURUCU_H
#define SURUCU_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>




int GPIORead(int pin);    //read sensor value 0 or 1
int GPIOWrite(int pin, int value);  //set given pin LOW or HIGHH


#endif
