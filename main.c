#include <time.h>
#include "display.h"

int showTime(Window win, GC gc)
{
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	
	char buffer[64];
	strftime(buffer, sizeof(buffer), "%H:%M", t);

	putText(buffer, 00, 100, "-*-helvetica-medium-r-*-*-100-*-*-*-*-*-*-*", win, gc);
	return 1;
}

int main()
{
	if (!setUpX()) return 0;
	// Set yellow colour
	XColor yellow;Colormap cmap = DefaultColormap(dpy, screen);
	XParseColor(dpy, cmap, "yellow", &yellow);
	XAllocColor(dpy, cmap, &yellow);
	unsigned long yellowColor = yellow.pixel;

	Window startframe = newXWindow("Relo", 0, 0, 125, 225, yellowColor, KeyPressMask | EnterWindowMask | LeaveWindowMask );
	GC gc = XCreateGC(dpy, startframe, 0, &gcv);
	XMapWindow(dpy, startframe);

	Atom wmDelete = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(dpy, startframe, &wmDelete, 1);	


	for (;;)
	{
		XNextEvent(dpy, &e);
		switch (e.type)
		{
			case KeyPress:
			case EnterNotify:
				XSetWindowBackground(dpy, startframe, blackColor); 
				XSetForeground(dpy, gc, yellowColor);
				XClearWindow(dpy, startframe);
				showTime(startframe, gc);
				XSync(dpy, False);
				break;

			case LeaveNotify:

				XSetForeground(dpy, gc, whiteColor);
				XSetWindowBackground(dpy, startframe, yellowColor);	
				XClearWindow(dpy, startframe);
				XSync(dpy, False);
				break;

			case ClientMessage:

				if ((Atom)e.xclient.data.l[0] == wmDelete) {
					// close button was pressed
					XDestroyWindow(dpy, startframe);
					XCloseDisplay(dpy);
					return 0;
    				}
				break;
			default: printf("Event type: %d\n", e.type);
		}
		
	}
	XCloseDisplay(dpy);
	return 0;	
}
