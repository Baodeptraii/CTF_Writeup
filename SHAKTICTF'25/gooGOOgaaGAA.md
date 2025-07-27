<img width="479" height="153" alt="image" src="https://github.com/user-attachments/assets/9293b592-8437-4012-a92f-ea3085e87599" />  

Code người ta cho :  
```python
def gaga(text, key):
    result = []
    for i in range(len(text)):
        result += chr(ord(text[i]) ^ ord(key[i % len(key)]))
    return result

key = "IWANTMOMOS"

encrypted= [':', '?', ' ', '%', ' ', '$', ',', '9', ')', '(', '+', 'c', '#', '7', '\x06', '~', '9', '\x12', '~', ' ', '\x16', '4', '4', ':', 'g', '0']
inp= input("> ")

if (gaga(inp, key)==encrypted):
    print("YOU DID ITTT :))")
else:
    print("try again :(")
```

Đoạn mã Python này thực hiện một phép mã hóa XOR ký tự với key lặp lại, sau đó so sánh với danh sách encrypted. Để vượt qua điều kiện `gaga(inp, key) == encrypted`, ta chỉ cần giải mã ngược lại.  

Hàm 
```python
gaga(text, key):
  result += chr(ord(text[i]) ^ ord(key[i % len(key)]))
```
Dùng key lặp lại để XOR từng ký tự trong text.  
Trả về danh sách ký tự (không phải chuỗi).  
Cần tìm inp sao cho:  
`gaga(inp, key) == encrypted`  


Sửa lại một tí:  
```python
def gaga_decrypt(enc_list, key):
    result = ""
    for i in range(len(enc_list)):
        c = ord(enc_list[i]) ^ ord(key[i % len(key)])
        result += chr(c)
    return result

key = "IWANTMOMOS"
encrypted = [':', '?', ' ', '%', ' ', '$', ',', '9', ')', '(', '+', 'c', '#', '7', '\x06', '~', '9', '\x12', '~', ' ', '\x16', '4', '4', ':', 'g', '0']

plaintext = gaga_decrypt(encrypted, key)
print("Plaintext:", plaintext)

```
Peace!
