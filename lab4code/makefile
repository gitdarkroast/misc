# Makefile for ELEC278 Lab 4
# Meant to be used with MSVC nmake command; may not work with Linux or
# other make commands.


avl.exe:	main.obj avl.obj
		cl /nologo /Feavl avl.obj main.obj

main.obj:	main.c avl.h

avl.obj:	avl.c. avl.h

clean:
		del	*.obj
		del *.map
		del *.exe
