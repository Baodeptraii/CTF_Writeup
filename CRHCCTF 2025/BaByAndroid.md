<img width="498" height="378" alt="image" src="https://github.com/user-attachments/assets/95070044-f8e8-4b2c-9880-3fc8d6738c22" />  

My first apk-android chall ever solved.  

After searching how to do apk chall in CTF, i found out some knowledge.  
1. You need a virtual machine that run Android (cuz apk file only work for Android ?!)
2. A reverse-engineering tool for apk file, i chose `Jadx`.
3. Command line tool called `apktool`.

Okay, let's get started.  

After download apk file, i run it with `apktool` to extract every folder in it.  
```vim
apktool d app-release
```
As you can see the result:  

<img width="829" height="127" alt="image" src="https://github.com/user-attachments/assets/04b80353-e2d6-4da3-9eb9-5e76078b366c" />  

Open folder with Jadx and read the code.  

<img width="1691" height="829" alt="image" src="https://github.com/user-attachments/assets/1dee9a21-330d-4a58-8923-d630b1d321a1" />  

All the code is reverse to Java code. Normally, we need to read `MainActivity` class at `com/` folder. Let's see if there is a flag here.  

<img width="510" height="139" alt="image" src="https://github.com/user-attachments/assets/a11c0cde-d028-4617-9e6a-7ea780fd6354" />  

First, we have AES and IV (CBC) key to encrypt message.  

<img width="1140" height="155" alt="image" src="https://github.com/user-attachments/assets/4621b0db-f4e2-4fb3-b5a6-ffd8f43289fe" />  

This is how it encrypt message. Using AES/CBC/PKCS5Padding, then encode Base64.  

<img width="718" height="64" alt="image" src="https://github.com/user-attachments/assets/68ef2b69-d525-401d-badc-8e40872b6bfa" />  

That ours encrypted message.  
Our rev should be:
```
Encrypted message -> decode Base64 -> decrypt AES/CBC/PKCS5Padding using given key.
```
Here is the script to get the flag:
```python
from Crypto.Cipher import AES
import base64

key = b"6c77a920b3232ef5"
iv  = b"a36edc9a25527dbc"
target = "/Ht9CWzMAB1eeQVhMTnAEDVJHUzL77Iuiil3uUiR12E="

cipher_bytes = base64.b64decode(target)
cipher = AES.new(key, AES.MODE_CBC, iv)
plain = cipher.decrypt(cipher_bytes)

pad_len = plain[-1]
plain = plain[:-pad_len]
print(plain.decode())

```
Peace!








