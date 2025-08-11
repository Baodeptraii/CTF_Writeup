<img width="489" height="574" alt="image" src="https://github.com/user-attachments/assets/e4a7ef75-259e-4809-88bd-3250e982e122" />  

Going around and we found important data.  

<img width="1593" height="255" alt="image" src="https://github.com/user-attachments/assets/33f54584-b1f9-4185-8fc8-ad66238a8727" />  

On Wireshark, go to `File -> Export Object -> FTP (what packet we're looking)`, to export contained data.  

<img width="568" height="166" alt="image" src="https://github.com/user-attachments/assets/bc48b262-e262-4f37-8f59-b6314e12852b" />  

We have one python file, showing the way they encrypt file.  
We have one txt file, showing the cipher text.  
Reversing python file and we have....  

```python
#!/usr/bin/env python3

alphabet = 'abcdefghijklmnopqrstuvwxyz'

def shift_chars(text, pos):
    out = ""
    for letter in text:
        if letter in alphabet:
            letter_pos = (alphabet.find(letter) + pos) % 26
            new_letter = alphabet[letter_pos]
            out += new_letter
        else:
            out += letter
    return out

def decrypt_text(text):
    counter = 0
    decrypted_text = ""

    for i in range(0, len(text), 10):
        counter = (counter + 1) % 26
        decrypted_text += shift_chars(text[i:i+10], -counter)  # Reverse the shift
    return decrypted_text

if __name__ == '__main__':
    filename = "b.txt" # That my file name

    with open(filename, "r") as f:
        data = f.read()

    decrypted_data = decrypt_text(data)

    with open("b_decrypted.txt", "w") as f: # That the file i want to write
        f.write(decrypted_data)

    print("-> b_decrypted.txt")
```

And we have plain text, right?  

```
Recipe Caesar Salad

Ingredients

For the Salad:

- 1 large head of Romaine lettuce, chopped
- 1 cup croutons (homemade or store-bought)
- 0,5 cup Parmesan cheese, shaved or grated

For the Dressing:

- 0,5 cup mayonnaise (or 0,5 cup mayo + 0,5 cup Greek yogurt for a lighter version)
- 2 tbsp lemon juice (freshly squeezed)
- 1 tsp Dijon mustard
- 1 tsp Worcestershire sauce
- 1 garlic clove, minced
- 2 anchovy fillets, finely chopped (or 0,5 tsp anchovy paste, optional)
- 0,25 cup olive oil
- Salt & black pepper, to taste
- a drizzle of flag{ad1c53bf1e00a9239d29edaadcda2964}

Instructions

Make the Dressing

- In a bowl, whisk together mayonnaise, lemon juice, Dijon mustard, Worcestershire sauce, minced garlic, and anchovies.
- Slowly drizzle in the olive oil while whisking to emulsify.
- Add salt and pepper to taste.

Prepare the Salad

- In a large salad bowl, toss chopped Romaine lettuce with croutons and Parmesan cheese.

Assemble

- Drizzle the dressing over the salad and gently toss to coat everything evenly.

Serve Immediately

- Garnish with extra Parmesan and croutons if desired.
- Enjoy with grilled chicken, shrimp, or salmon for a protein boost!
```
Do you see the flag?  
Peace!






