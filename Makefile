all:
	gcc -o relo main.c -static -lX11 -lpthread -lxcb -lXau -lXdmcp
