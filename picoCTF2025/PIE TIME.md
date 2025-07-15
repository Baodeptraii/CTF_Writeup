Description:  
Can you try to get the flag? Beware we have PIE!  
Additional details will be available after launching your challenge instance.  
Hints:  
Can you figure out what changed between the address you found locally and in the server output?  

After downloading all the item, i receive `vuln` - binary file and `vuln.c` - source code.  
Checking `vuln` with IDA and reading `vuln.c` i notice something:  
- The program is running w/ PIE (Position Independent Executable). Everytime you run the program, it will be loaded to diffirent address.
- If you want to bypass it, you need a "base" point to calculate. In this case, it is the `main()` address which shown everytime you run the netcat.
- We need to calculate the offset between `main()` and `win()` ( which stored the flag ).

1. Running it w/o PIE : `gcc -o vuln vuln.c -no-pie`
2. Calc offset : `nm -n vuln | grep -E ' win$| main$'`
3. Calc win() address with this formula:  
   `Offset = T win - T main`  
   `win() = main() + offset `

Your `win()` address is your input while running netcat.  

Peace!
   

