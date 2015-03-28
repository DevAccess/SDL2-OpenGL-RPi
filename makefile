
CPP_OCH11 = objs
CPP_HCH11 = code
CPP_ICH11 = code

OBJS = ${CPP_OCH11}/main.o ${CPP_OCH11}/Cube.o ${CPP_OCH11}/stb_image.o ${CPP_OCH11}/globals.o ${CPP_OCH11}/OpenGL_Context.o ${CPP_OCH11}/Window.o
CC = g++
CFLAGS = -Wall -c -std=c++0x ${shell sdl2-config --cflags}
LFLAGS = -Wall -lGLU -lGLEW -L/usr/lib -L/opt/vc/lib ${shell sdl2-config --libs}
CFLAGS+= -DSTANDALONE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -DTARGET_POSIX -D_LINUX -fPIC -DPIC -D_REENTRANT -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -U_FORTIFY_SOURCE -Wall -g -DHAVE_LIBOPENMAX=2 -DOMX -DOMX_SKIP64BIT -ftree-vectorize -pipe -DUSE_EXTERNAL_OMX -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM -Wno-psabi
LFLAGS+= -L$(SDKSTAGE)/opt/vc/lib/ -lGLESv2 -lEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt -lm -L../libs/ilclient -L../libs/vgfont

main: ${OBJS}
	${CC} ${OBJS} ${LFLAGS} -o main


${CPP_OCH11}/main.o: ${CPP_ICH11}/main.cpp ${CPP_HCH11}/main.h
	${CC} ${CFLAGS} ${CPP_ICH11}/main.cpp -I ${CPP_HCH11} -o ${CPP_OCH11}/main.o

${CPP_OCH11}/Cube.o: ${CPP_ICH11}/Cube.cpp ${CPP_HCH11}/Cube.h
	${CC} ${CFLAGS} ${CPP_ICH11}/Cube.cpp -I ${CPP_HCH11} -o ${CPP_OCH11}/Cube.o
		
${CPP_OCH11}/stb_image.o: ${CPP_ICH11}/stb_image.cpp ${CPP_HCH11}/stb_image.h
	${CC} ${CFLAGS} ${CPP_ICH11}/stb_image.cpp -I ${CPP_HCH11} -o ${CPP_OCH11}/stb_image.o
		
${CPP_OCH11}/globals.o: ${CPP_ICH11}/globals.cpp ${CPP_HCH11}/globals.h
	${CC} ${CFLAGS} ${CPP_ICH11}/globals.cpp -I ${CPP_HCH11} -o ${CPP_OCH11}/globals.o
		
${CPP_OCH11}/OpenGL_Context.o: ${CPP_ICH11}/OpenGL_Context.cpp ${CPP_HCH11}/OpenGL_Context.h
	${CC} ${CFLAGS} ${CPP_ICH11}/OpenGL_Context.cpp -I ${CPP_HCH11} -o ${CPP_OCH11}/OpenGL_Context.o

${CPP_OCH11}/Window.o: ${CPP_ICH11}/Window.cpp ${CPP_HCH11}/Window.h
	${CC} ${CFLAGS} ${CPP_ICH11}/Window.cpp -I ${CPP_HCH11} -o ${CPP_OCH11}/Window.o

clean:
	rm main ${OBJS}