## CTF
My CTF games.


## What is this?
In order to learn more about how pwn challenges work I have created some challenges of my own and solved them.

The goal with these challenges are to read the contents of the file "flag" by manipulating the input to the programs. Usually during a contest, a binary is provided along with an ip address and a port where the binary is running. The flag may be hidden elsewhere, but getting an interactive shell is always a good start if possible.

##Usage
Binaries compiled for linux x86-64 are provided along with the source code. You may build it yourself on any platform where it builds. Why not build it for a raspberry pi?

You can usually test your solutions by simply piping your data to the binary, `./solution.py | ./ctf`, or you can use netcat and use sockets instead.

* If your netcat supports the -e option, `nc -e ./ctf -l 1234` 
* Otherwise `rm /tmp/f; mkfifo /tmp/f; cat /tmp/f | ./ctf -i 2>&1|nc -l  1234 > /tmp/f` works just as well.
* Then connect to 127.0.0.1:1234 with your code.

## Cheat sheet
I've provided cheat sheets for the first and second challenges, just to get you on the right track. Only look if you're stuck!
