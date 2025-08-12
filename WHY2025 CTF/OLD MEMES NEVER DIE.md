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






