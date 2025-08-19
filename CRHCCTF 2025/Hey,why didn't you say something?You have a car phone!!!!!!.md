<img width="491" height="487" alt="image" src="https://github.com/user-attachments/assets/a74bf1c5-7eb8-4c96-8003-29724c9d9cfe" />  

# Cre : Grzechu ( romdom guy on disc )

The title suggests that this has something to do with old mobile phones and SMS messages.

The given string is in SMS PDU (Protocol Data Unit) format.
In the GSM standard, SMS messages are encoded into a binary format, usually represented in hex. Old GSM modems required sending/receiving SMS in this format using AT commands.

00 | 11 | 00 | 0A | 81 | 90 88 78 77 66 | 00 | 00 | 0B | 30 | ...
00 – SMSC length (0 means default SMS center).
11 – First octet: SMS-SUBMIT.
00 – Message reference.
0A – Destination address length (10 digits).
81 – Type of address (national number).
90 88 78 77 66 – Encoded destination number. In GSM semi-octet representation this becomes: 09 88 87 77 66 → 0988877766

00 – PID.
00 – Data coding scheme (GSM 7-bit).
0B – Validity period (relative, not important here).
30 – User data length = 48 septets.
The rest is the user data.

46 76 F8 0C 4A CF 41 C4 F2 9C 9E 76 87 E9 E9 B7 1B E4 AC B7 C5 65 39 28 EC 26 83 B0 7A 2B DD 89 15 AE C9 D6 5C 5B 4C 94 BA 5D

This is encoded in GSM 7-bit default alphabet.
After unpacking the septets (GSP_7-bit.py), the decoded text is: Flag is Destination Number and XzVtNXBkdV9mbDRn.

From base64: XzVtNXBkdV9mbDRn  →  _5m5pdu_fl4g

0988877766_5m5pdu_fl4g -> CRHC{0988877766_5m5pdu_fl4g}

```python
def gsm7_decode(userdata_hex, udl):

    # Convert hex string to byte array
    userdata = bytes.fromhex(userdata_hex)

    # Unpack septets from packed GSM 7-bit
    bits = ""
    for b in userdata:
        bits += f"{b:08b}"[::-1]  # reverse each byte (LSB first)

    septets = []
    for i in range(udl):
        septets.append(bits[i*7:(i+1)*7][::-1])  # 7 bits each

    chars = []
    for sept in septets:
        if sept == "":
            continue
        val = int(sept, 2)
        if val == 0x00:
            chars.append('@')
        elif val == 0x20:
            chars.append(' ')
        else:
            try:
                chars.append(bytes([val]).decode('gsm03.38'))  # needs 'gsm03.38' codec (Python 3.11+)
            except:
                # fallback: map most ASCII directly
                chars.append(chr(val))
    return "".join(chars)


if __name__ == "__main__":
    # Example from your challenge
    ud_hex = "4676F80C4ACF41C4F29C9E7687E9E9B71BE4ACB7C5653928EC2683B07A2BDD8915AEC9D65C5B4C94BA5D"
    udl = 48  # user data length in septets

    decoded = gsm7_decode(ud_hex, udl)
    print(decoded)
```
