<img width="470" height="405" alt="image" src="https://github.com/user-attachments/assets/0de708b3-b40e-4192-999e-85ab0a742b63" />  

Using IDA to view and we see:  

<img width="599" height="246" align="center" alt="image" src="https://github.com/user-attachments/assets/4e3b83fa-8ddd-43cf-9ca2-91c6c7277a20" />    
<br>
<br>
<img width="389" height="202" align="center" alt="image" src="https://github.com/user-attachments/assets/ec632ed1-46b4-4b19-8218-a41533b4c89d" />    
<br>
<br>
<img width="349" height="106" align="center" alt="image" src="https://github.com/user-attachments/assets/64e965f9-adda-4f1b-a27a-514b7a11271f" />   

  
Okay, simple, we let it runs for 1000 times, each time take 1000 seconds, and we got the flag....  

Time is money, let's analyze it.  

It's loop 1000 times, each time, `i` will XOR with `0x1Bui64` ~ `27`. `1000 mod 27 = 1`. That mean it's only XOR **ONE TIME**!  

Okay, let's see what is "XORING".  

<img width="1148" height="171" alt="image" src="https://github.com/user-attachments/assets/64250e25-e3c8-4d47-9240-ea884beb7676" />  

Let's `XOR` it one by one.  

```python
encrypted_flag = [ // Sorry but this data is from `Lazy Code 2.0`, i'm too lazy to write it again :((( 
    0x2A, 0x20, 0x2D, 0x2B, 0x37, 0x2E,
    0x7F, 0x2A, 0x28, 0x2D, 0x78, 0x7D,
    0x7A, 0x28, 0x2D, 0x29, 0x2E, 0x28,
    0x29, 0x2A, 0x7B, 0x2D, 0x79, 0x28,
    0x7B, 0x75, 0x28, 0x29, 0x2E, 0x7C,
    0x7B, 0x2F, 0x78, 0x7F, 0x7F, 0x7B,
    0x79, 0x31, 0x4C
]


xors = [ // Same as above
    0x17, 0x2B, 0x57, 0x6F, 0x7A, 0x00, 0x21, 0x2D, 0x1D, 0x67,
    0x2B, 0x56, 0x16, 0x63, 0x5B, 0x67, 0x38, 0x1D, 0x0B, 0x0A,
    0x3 , 0x70, 0x47, 0x12, 0x36, 0x0C, 0x63
]

def xor_string(data, key):
    return [b ^ key for b in data]

for i in range(1, 1001):
    key = xors[i % 27]
    encrypted_flag = xor_string(encrypted_flag, key)

print("Flag: ", ''.join(chr(b) if 32 <= b <= 126 else '.' for b in encrypted_flag))

```

Peace! 









