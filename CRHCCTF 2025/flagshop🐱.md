<img width="492" height="488" alt="image" src="https://github.com/user-attachments/assets/7cf5a170-9196-4b40-ac0d-d3ae6895c11d" />  

<img width="655" height="242" alt="image" src="https://github.com/user-attachments/assets/e65d4325-82d7-46e0-9b32-e5674bdb9285" />  

Let's see if we can buy the flag.  

<img width="684" height="195" alt="image" src="https://github.com/user-attachments/assets/e871bfa0-0901-4207-9b9a-3d06e70f75df" />  

This really deadend, the flag maybe hidden inside the stack.   

<img width="497" height="206" alt="image" src="https://github.com/user-attachments/assets/4a3751d8-3e60-4d09-840d-509af1af759c" />  

That `check_flag` function, let's keep looking ...  

<img width="997" height="166" alt="image" src="https://github.com/user-attachments/assets/c3290d5d-3c5b-4350-a34e-56c46738c568" />  

Finally, i found secret !  

Let XOR the secret like the `check_flag` function.   

```python
secret = [
    0x40, 0x73, 0x77, 0x1E, 0x24, 0x08, 0xC4, 0xDE, 0xCE, 0xEA,
    0x84, 0x126, 0x172, 0x151, 0x10C, 0x105, 0x144, 0x1A2,
    0x1F0, 0x1AB, 0x1FE, 0x1D9, 0x26C, 0x276, 0x243, 0x279,
    0x210, 0x2DA, 0x2E3, 0x294, 0x2A7, 0x2BE, 0x296, 0x35E,
    0x37B, 0x30D, 0x360, 0x36C, 0x30F, 0x3A6, 0x3A4, 0x386,
    0x3E8, 0x3CA, 0x3C8, 0x468
]

flag = []
for i in range(len(secret)):
    key_part = 23 * i + 3 + 7 * (i % 4)
    char = secret[i] ^ key_part
    flag.append(chr(char))

print(''.join(flag))
```

Peace!




