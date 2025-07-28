<img width="499" height="462" alt="image" src="https://github.com/user-attachments/assets/16f6712c-1969-43a2-be65-d03c7a7dd35b" />  

# Cre: 1ynchee

Receiving base64 file with a lot of short base64 string.  
Found [this article](https://hexarcana.ch/b/2024-08-16-base64-beyond-encoding/).  
The keyword is: `unused bit`, `2 by 2`, ...  
And we got the script:  
```python
import base64

b64_chunks = [
    "U3==", "T3==", "Un==", "Un==", "WW==", "IG==", "VH==", "SL==", "RX==",
    "Ul==", "RW==", "IO==", "SV==", "U1==", "IH==", "Tj==", "Tz==", "ID==",
    "Rm==", "TE==", "QV==", "R/==", "IG==", "VC==", "Tz==", "IB==", "Qn==",
    "RU==", "IH==", "Rj==", "T1==", "Vf==", "Tj==", "RD==", "IH==", "SB==",
    "RX==", "Ul==", "RT==", "Lk==", "IG==", "UM==", "TH==", "Ra==", "QV==",
    "U/==", "RX==", "ID==", "RH==", "T0==", "ID==", "Tj==", "T2==", "VH==",
    "ID==", "Qw==", "T1==", "Tv==", "VG==", "SW==", "Tn==", "VV==", "RW==",
    "IO==", "TH==", "T9==", "Tw==", "Sw==", "SQ==", "Tg==", "Ry4="
]

#  Base64 →  6 bit
b64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
def char_to_6bit(c):
    return format(b64_table.index(c), '06b')

bitstream = ""

for chunk in b64_chunks:
    if chunk.endswith("==") and len(chunk) == 4:
        # First 2 characters are valid, last 2 are padding
        b1, b2 = chunk[:2]
        bits = char_to_6bit(b1) + char_to_6bit(b2)  # 12 bit
        unused = bits[8:]  # 4 bit unused
        bitstream += unused

# Decode by 8 bit
message = ""
for i in range(0, len(bitstream), 8):
    byte = bitstream[i:i+8]
    if len(byte) == 8:
        message += chr(int(byte, 2))

print("Hidden flag:", message)
```
Or you can use your hand and your brain ...   

<img width="2880" height="2160" alt="image" src="https://github.com/user-attachments/assets/ca5e2b12-2399-49b1-a9f8-5fb32d0cece5" />  

Peace!


