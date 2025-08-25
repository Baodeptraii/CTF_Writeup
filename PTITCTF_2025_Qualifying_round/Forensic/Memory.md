<img width="452" height="398" alt="image" src="https://github.com/user-attachments/assets/35853686-e76d-463c-9c30-470c6de8f53c" />  

Dùng Volatility tool để tìm tất cả tiến trình nghi ngờ bằng `psList` -> thấy tiến trình của `notepad` có thằng `real.txt` -> dump nó ra nhưng yêu cầu mật khẩu để mở.  
Vẫn là `psList` thấy thằng `KeePass` có cái database gì gì đấy. Dump nó ra thì yêu cầu KEY.  
`strings` cả cái file raw to đùng ra (13tr dòng :V), `Ctrl F` tìm theo KEY, AES_KEY thì ra 3 cái: 
```python
import base64
from Crypto.Cipher import AES

AES_KEY = b"PTIT_CTF2025_KEY"       # 16 bytes
AES_IV = b"InitializationVe"        # 16 bytes
AES_ENC_DATA = "rNxBkug3ri07khz2rKqQY+bv6GyhHZD/gbM4y2lUAUDENzGNDYeu1eNCWl9cTkyo"

# decode base64
ciphertext = base64.b64decode(AES_ENC_DATA)

# tạo AES cipher (CBC mode)
cipher = AES.new(AES_KEY, AES.MODE_CBC, AES_IV)
plaintext = cipher.decrypt(ciphertext)

# bỏ padding PKCS7
pad_len = plaintext[-1]
plaintext = plaintext[:-pad_len]

print(plaintext.decode(errors="ignore"))

```

Hợp thành 1 key duy nhất => PassDB: NoCurrentThreatsInVirus&Protection  

Mở khóa database bằng cái pass kia -> Tìm được thêm cái pass nữa -> Đổi tên cái `real.txt` thành `.docx` -> Mở ra là thấy flag.  

> Flag: PTITCTF{M3m0ry_Dumppppppppp!}
