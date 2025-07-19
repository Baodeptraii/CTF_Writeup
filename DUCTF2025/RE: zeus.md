<img width="828" height="247" alt="image" src="https://github.com/user-attachments/assets/05f52bf8-f420-4811-8444-3bc90589c16f" />  

After download the attachment file, i use command `file` to check if can be execute or not. It's `ELF 64-bit LSB pie executable` so i just run it normaly but only show the text.  
Tried to open it with IDA and read the code:  
<img width="796" height="165" alt="image" src="https://github.com/user-attachments/assets/a98a513c-7c48-40e5-8cff-15dcd12abc9f" />  

It's only run the `if` code if only :  
- There're 3 argument when we input ( first one already `./zeus`)  
- Second argument must be `-invocation`.  
- The third argument must be string `s2`.
  
The completed input will be `./binary -invocation "To Zeus Maimaktes, Zeus who comes when the north wind blows, we offer our praise, we make you welcome!"`
Then you will have the flag.

Peace!

