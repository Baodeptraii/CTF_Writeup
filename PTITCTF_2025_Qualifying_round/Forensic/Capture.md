<img width="443" height="417" alt="image" src="https://github.com/user-attachments/assets/666b745a-d180-4ba9-8e3a-2dbdf5d8173b" />  

Export object được 1 folder toàn .txt, sử dụng JohnTheRipper để crack mật khẩu.  
Kiểm tra mấy file cuối cùng, giải mã b64 thì thấy nó là 1 ứng dụng chạy = **.NET**. Base64 decode tất cả các file -> ghép lại thành 1 cái to đùng -> Dịch ngược bằng `dnSpy-net` -> Tìm hàm `main` -> dịch ngược tiếp.  

> Flag: PTITCTF{dotn3t_c4nn0t_mak4it_difficult_f0ry0u}

