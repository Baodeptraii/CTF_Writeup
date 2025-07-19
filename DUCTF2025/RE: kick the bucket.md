<img width="1075" height="671" alt="image" src="https://github.com/user-attachments/assets/045285aa-4c4a-4d6a-8b52-ffb2be6d8b36" />  

After downloading 2 attachments, it's 2 txt file containt 1 URL and 1 XML.  
I tried to access first URL and it's show Access Denied.  
Read the second XML and i guess :  
- The user must be: `"arn:aws:iam::487266254163:user/pipeline"` to access.
- User agent must be: `"aws-sdk-go*"`

With that idea, i tried to put that user agent into the URL using command `curl -A "aws-sdk-go*" <URL>` and it's working.

Peace!
