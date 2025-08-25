<img width="441" height="353" alt="image" src="https://github.com/user-attachments/assets/bd49ef88-abd6-4c68-b4f8-4b19e580fb9a" />  

Tải ứng dụng giả mạo từ Vir1 về (`svhost.exe`). Kiểm tra thì thấy nó bị đóng gói bằng UPX, giải nén bằng lệnh :  
```
upx -d file.exe -o file_unpacked.exe
```
Mở file và phân tích bằng IDA.  
Hàm quan trọng là `sub_1400016801` (thực hiện kiểm tra và XOR) và mảng dữ liệu `byte_1401436A0` (2920 bytes) -> Dump mảng dữ liệu ra và lấy giá trị Hex.  
Hàm `sub_140001680` kiểm tra mật khẩu = 8 bytes đầu của ảnh (PNG signature) + với hàm XOR trong kia + 2920 bytes nữa => mật khẩu đầy đủ là " _NoCurrentThreats_ ".  
```
Hàm sub + mảng dữ liệu + mật khẩu + sử dụng logic reverse và pwntools, XOR ngược lại và khôi phục ảnh png ---> Chat
```
Ra được cái ảnh png => `zsteg` để kiểm tra thông tin ẩn.  

> Flag: PTITCTF{L3ast_S1gn1f1cant_B1t_M4g1c_1n_3x3}

