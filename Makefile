build:
	gcc server.c -o server
	i686-w64-mingw32-gcc -o malware.exe malware.c -lwsock32 -lwininet


clean:
	rm server malware.exe