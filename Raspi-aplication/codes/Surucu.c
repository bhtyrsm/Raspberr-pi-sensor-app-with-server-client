#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include"Surucu.h"  //relay


#define LOW 0
#define HIGH 1



int GPIORead(int pin){

	char path[28];
	char value_str[3];
	int fd;
	snprintf(path, 30, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpiovalue for reading!\n");
		return(-1);
	}
	if (-1 == read(fd, value_str, 3)) {
		fprintf(stderr, "Failed to read value!\n");
		return(-1);
	}
	close(fd);
	return(atoi(value_str));

}
int GPIOWrite(int pin, int value) {

	static const char s_values_str[] = "01";
	char path[30];
	int fd;
	snprintf(path, 30, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpiovalue for writing!\n");
		return(-1);
	}
	if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
		fprintf(stderr, "Failed to write value!\n");
		return(-1);
	}
	close(fd);
	return(0);


}