# Use Git Bash and MinGW to build this on Windows
if [ "$1" == "release" ]; then
    rm -f warquest.exe
    if windres resource.rc resource.o; then
        gcc -s -O2 warquest.c resource.o -lole32 -loleaut32 -luuid -Wl,--subsystem,windows -o warquest.exe
        rm resource.o
    fi
else
    rm -f warquest.exe
    if windres -DDEBUG resource.rc resource.o; then
        gcc -g -DDEBUG -Wall -Wextra -Wshadow -Wpedantic --std=c99 warquest.c resource.o -lole32 -loleaut32 -luuid -o warquest.exe
        rm resource.o
    fi
fi
