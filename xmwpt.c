#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/shape.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef VERSION
#define VERSION "dev"
#endif

void setWindowPassthrough(Display *dpy, Window win, int ignore)
{
    if (ignore) {
        XRectangle rect;
        XserverRegion region = XFixesCreateRegion(dpy, &rect, 0);
        XFixesSetWindowShapeRegion(dpy, win, ShapeInput, 0, 0, region);
        XFixesDestroyRegion(dpy, region);
    } else {
        XFixesSetWindowShapeRegion(dpy, win, ShapeInput, 0, 0, None);
    }
}

int main(int argc, char *argv[])
{
    Window win = 0;
    int enable = -1;
    int help = 0;

    int opt;
    extern char *optarg;
    while ((opt = getopt(argc, argv, "hvs:u:")) != -1) {
        switch (opt) {
        case 'h':
            help = 1;
            break;
        case 'v':
            printf("%s\n", VERSION);
            exit(EXIT_SUCCESS);
            break;
        case 's':
            enable = 1;
            win = atoi(optarg);
            break;
        case 'u':
            enable = 0;
            win = atoi(optarg);
            break;
        }
    }

    if (help || argc == 1) {
        printf("xmwpt [-h|-v|-s WIN|-u WIN]\n\
example:\n\
    xmwpt -s WIN\tset passthrough shape for window WIN\n\
    xmwpt -u WIN\tunset shape\n");
        exit(EXIT_SUCCESS);
        return 0;
    }

    if (enable < 0 || (win <= 0)) {
        printf(
            "did you forget an '-s' or are you trying to set shape for root "
            "window? you probably don't want to do this. use '-h' for help\n");
        return 1;
    }

    if (enable) {
        printf("hiding window %lu\n", win);
    } else {
        printf("unhiding window %lu\n", win);
    }

    Display *dpy = XOpenDisplay(NULL);
    setWindowPassthrough(dpy, win, enable);
    XCloseDisplay(dpy);

    return 0;
}
