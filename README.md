## CTF
My CTF games.


## What is this?
In order to learn more about how pwn challenges work I have created some challenges of my own and solved them.

The goal with these challenges is to find the "flag". This could be a file somewhere on the filesystem called flag, or it could be embedded in the binary itself.
It is possible to find the flag by manipulating the input to the programs. Usually during a contest, a binary is provided along with an ip address and a port where the binary is running. The flag may be hidden anywhere, but getting an interactive shell is usually a good start if possible.

##Usage
Binaries compiled for linux x86-64 are provided along with the source code. You may build it yourself on any platform where it builds. Why not build it for a raspberry pi?

You can usually test your solutions by simply piping your data to the binary, `./solution.py | ./ctf`, or you can use netcat and sockets instead.

* If your netcat supports the -e option, `nc -e ./ctf -l 1234` 
* Otherwise `rm /tmp/f; mkfifo /tmp/f; cat /tmp/f | ./ctf -i 2>&1|nc -l  1234 > /tmp/f` works just as well.
* Then connect to 127.0.0.1:1234 with your code.

## Cheat sheet
I've provided cheat sheets for the first and second challenges just to get you on the right track. Only look if you're stuck!
