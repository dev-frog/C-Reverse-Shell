build:
	gcc Server.c -o server
	i686-w64-mingw32-gcc reverse.c -o malware.exe  -lwsock32 -lwininet


clean:
	rm server malware.exe