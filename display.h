#ifndef DISPLAY_H
#define DISPLAY_H

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Display		*dpy;
Window		root;
int		screen;
unsigned long 	blackColor, whiteColor;
XEvent		e;
XGCValues	gcv;

Window newXWindow(char* wtitle, int x, int y, int height, int width, unsigned long backg, long args)
{
	Window mainw = XCreateSimpleWindow(dpy, root, x, y, width, height, 0, blackColor, backg);
	XSelectInput(dpy, mainw, args);
	XStoreName(dpy, mainw, wtitle);
	return mainw;
}

int loadFont(char* fontname, GC gc)
{
	if (fontname != NULL)
	{
		XFontStruct *font = XLoadQueryFont(dpy, fontname);
		
		if (font != NULL) { XSetFont(dpy, gc, font->fid); return 1; }
		else { return 0; }

	} else 	{ return 1; }
}

int putText(char* text, int x, int y, char* fontname, Window win, GC gc)
{
	if (!loadFont(fontname, gc)) return 0;
	XDrawString(dpy, win, gc, x, y, text, strlen(text));
	return 1;
}

int setUpX(void){

	if ((dpy = XOpenDisplay(NULL)) == NULL) return 0;
	root = DefaultRootWindow(dpy);
	screen = DefaultScreen(dpy);
	
	whiteColor = WhitePixel(dpy, screen);
 	blackColor = BlackPixel(dpy, screen);
	return 1;
}

#endif
