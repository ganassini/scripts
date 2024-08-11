/*
 *  Script to bind keys to change monitor brightness 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    FILE *file;
    char buffer[32];
    float brightness;
    char cmd[64];

    if ( argc != 2 ||  (strcmp(argv[1], "-d") != 0 &&  strcmp(argv[1], "-i") != 0 &&  strcmp(argv[1], "-k") != 0)) {
        fprintf(stderr, "Usage: %s [-d | -i | -k]\n", argv[0]);
		return 1;
    }

    file = popen("xrandr --verbose --current | grep DP-0 -A5 | awk '/Brightness/ {print $2}'", "r");
    
	if ( file == NULL ) {
        perror("Error opening pipe");
		return EXIT_FAILURE;
    }

    if ( fgets(buffer, sizeof(buffer), file) != NULL ) {
        brightness = atof(buffer);
    }
    pclose(file);

    if ( strcmp(argv[1], "-d") == 0 ) {
        sprintf(cmd, "xrandr --output DP-0 --brightness %.2f", brightness - 0.1);
        system(cmd);
        sprintf(cmd, "xrandr --output HDMI-0 --brightness %.2f", brightness - 0.1);
        system(cmd);
        return 0;
    }
    
    if ( strcmp(argv[1], "-i") == 0 ) {
        sprintf(cmd, "xrandr --output DP-0 --brightness %.2f", brightness + 0.05);
        system(cmd);
        sprintf(cmd, "xrandr --output HDMI-0 --brightness %.2f", brightness + 0.05);
        system(cmd);
        return 0;
    }

	if ( strcmp(argv[1], "-k") == 0 ) {
        system("xrandr --output DP-0 --brightness 1");
        system("xrandr --output HDMI-0 --brightness 1");
        return 0;
    }

    return 0;
}

