<img width="501" height="434" alt="image" src="https://github.com/user-attachments/assets/ce41af6c-840d-49f1-b2f9-e09d758adf20" />  

Open file with IDA, read carefully and we can see this code (Assembly is hard af )   

<img width="927" height="504" alt="image" src="https://github.com/user-attachments/assets/90b5ae8d-21e9-4e97-8c3e-34fc9a6ad7f6" />  

```assembly
mov rcx, 0x22
Set counter = 0x22 (34). Loop 34 times

lea rsi, [rip+0x6a]   ; => rsi = RIP + 0x6a
Load Effective Address: get the address of the encoded data (at 0x12c7 in the binary). This is the encrypted string.

.loop:
mov al, [rsi+r8]
Get 1 byte from the address rsi + r8 (i.e. each byte in the string).

Store it in register al.

xor al, 0x23
XOR this byte with 0x23. This is the key for decryption.

mov [rsi+r8], al
Write the XORed byte back to the same location in memory.

inc r8
Increase the index (next byte).

loop .loop
Decrease rcx, if not done then repeat. (rcx initially = 0x22 → run exactly 34 bytes).

jmp  0x12e9
After finishing, jump to the next instruction.
```
It XOR 34 data bytes start from `offset 0x12c7` with `0x23`. That all ... 

```python
path = "./chal"
with open(path, "rb") as f:
    f.seek(0x12c7)
    enc = f.read(0x22)

dec = bytes([b ^ 0x23 for b in enc])
print(dec.decode())
```
Found this flag is really funny 
> CRHC{u_ar3_GDB_k1ng_0r_GPT_klng??} # Yes i am ...
Peace!



