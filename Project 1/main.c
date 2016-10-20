
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "LinkLayer.h"

typedef struct ApplicationLayers {
    int fileDescriptor;
    int mode; /* TRANSMITTER | RECEIVER */
} ApplicationLayer;


int main(int argc, char** argv)
{
    printf("fdfsf\n");
	
	char* port = "/dev/ttyS0";
	
	configLinkLayer(port, BAUDRATE, 3, 5);
	
	if(argv[1][0] == 'T'){
		int fd = llopen(0, TRANSMITTER);

		unsigned char buffer[10];

		buffer[0] = 'a';
		buffer[1] = 'b';
		buffer[2] = F;
		buffer[3] = ESCAPE;
		buffer[4] = 'c';

		printf("Sending msg 1 \n");
		int r = llwrite (fd, buffer, 5);

		printf("%d bytes written\n", r);


		buffer[0] = ESCAPE;
		buffer[1] = ESCAPE;
		buffer[2] = ESCAPE;
		buffer[3] = ESCAPE;
		buffer[4] = ESCAPE;

		printf("Sending msg 2 \n");
		r = llwrite (fd, buffer, 5);

		printf("%d bytes written\n", r);
	}
	else{
		int fd = llopen(0, RECEIVER); 

		int j;
		
		for(j = 0; j < 5; j++){
			unsigned char buffer[100];
			int size = llread (fd, buffer); 
			int i;

			for(i = 0; i < size; i++){
				printf("buffer %02x\n", buffer[i]);
			}
		}
	}   

    return 0;
}
