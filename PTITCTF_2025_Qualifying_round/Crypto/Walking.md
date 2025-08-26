# Cre: Jayce

```python
from pwn import *
from sympy import primepi

def indivisible_primes(cipher: bytes) -> bytes:
    words = [
        ''.join(chr(primepi(n) + 64) for n in map(int, group.split())).capitalize()
        for group in cipher.decode().strip().split("  ")
    ]
    return " ".join(words).encode()

#   https://davidapps.co.uk/braille/ascii/
def braille_8dot(cipher: bytes) -> bytes:
    cipher = cipher.strip().decode()
    a = "⠁⠃⠉⠙⠑⠋⠛⠓⠊⠚⠅⠇⠍⠝⠕⠏⠟⠗⠎⠞⠥⠧⠺⠭⠽⠵⡁⡃⡉⡙⡑⡋⡛⡓⡊⡚⡅⡇⡍⡝⡕⡏⡟⡗⡎⡞⡥⡧⡺⡭⡽⡵ "
    b = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "
    m = {ch: b[i] for i, ch in enumerate(a)}
    return "".join(m[ch] for ch in cipher).encode()


def progressive_cascade(cipher: bytes) -> bytes:
    words = cipher.decode().strip().lower().split()

    def sol(s, n):
        return ''.join(
            chr(((ord(ch) - ord('a') - (n + i)) % 26) + ord('a'))
            for i, ch in enumerate(s)
        ).capitalize()

    res, shift = [], 3
    for w in words:
        res.append(sol(w, shift))
        shift += len(w) + 1

    return " ".join(res).encode()

#   https://en.wikipedia.org/wiki/NATO_phonetic_alphabet
def nato_phonetic(cipher: bytes) -> bytes:
    """
    Decode NATO phonetic code words into capitalized abbreviation strings.
    Example: "Alpha Bravo Charlie" -> "Abc"
    """
    words = cipher.decode().strip().split("  ")
    result = []
    for w in words:
        letters = [token[0] for token in w.split()]
        # Compose the word: first letter uppercase, rest lowercase
        result.append("".join(letters).capitalize())
    return " ".join(result).encode()

#   https://esolangs.org/wiki/Brainfuck
def spoons_brainfuck(cipher: bytes) -> bytes:
    """
    Decode Spoon (binary-coded Brainfuck variant) into Brainfuck and execute it.
    """
    binary = cipher.strip().decode()
    cmds = {
        '1': '+',
        '000': '-',
        '010': '>',
        '011': '<',
        '00100': '[',
        '0011': ']',
        '001010': '.',
        '0010110': ',',
    }

    # Parse binary into Brainfuck program
    prog = []
    i = 0
    while i < len(binary):
        for bits, cmd in cmds.items():
            if binary.startswith(bits, i):
                if cmd:
                    prog.append(cmd)
                i += len(bits)
                break
        else:
            i += 1

    # Execute Brainfuck
    tape = [0] * 30000
    ptr = 0
    pc = 0
    output = []
    stack = []

    while pc < len(prog):
        c = prog[pc]
        if c == '+':
            tape[ptr] = (tape[ptr] + 1) % 256
        elif c == '-':
            tape[ptr] = (tape[ptr] - 1) % 256
        elif c == '>':
            ptr += 1
        elif c == '<':
            ptr -= 1
        elif c == '.':
            output.append(chr(tape[ptr]))
        elif c == '[':
            if tape[ptr] == 0:
                # Jump forward to matching ]
                depth = 1
                while depth and pc + 1 < len(prog):
                    pc += 1
                    if prog[pc] == '[':
                        depth += 1
                    elif prog[pc] == ']':
                        depth -= 1
            else:
                stack.append(pc)
        elif c == ']':
            if tape[ptr] != 0:
                pc = stack[-1]
            else:
                stack.pop()
        pc += 1

    return "".join(output).encode()

#   https://en.wikipedia.org/wiki/Wabun_code
def japanese_morse(cipher):
    cipher = cipher.strip().decode().split("  ")

    m = {'-': 'mu', '--': 'yo', '---': 're', '----': 'ko', '---- ..': 'go', '---.': 'so', '---. ..': 'zo', '---.-': 'su', '--.': 'ri', '--. --': 'ryo', '--. -..--': 'ryu', '--. .--': 'rya', '--.-': 'ne', '--.--': 'a', '--.-.': 'shi', '--.-. --': 'sho', '--.-. -..--': 'shu', '--.-. .--': 'sha', '--..': 'fu', '--.. ..': 'bu', '--.. ..--.': 'pu', '--..-': 'hi', '--..- --': 'hyo', '--..- -..--': 'hyu', '--..- .--': 'hya', '--..- ..': 'bi', '--..- .. --': 'byo', '--..- .. -..--': 'byu', '--..- .. .--': 'bya', '--..- ..--.': 'pi', '--..- ..--. -..--': 'pyu', '--..- ..--. .--': 'pya', '-.': 'ta', '-. ..': 'da', '-.-': 'wa', '-.--': 'ke', '-.-- ..': 'ge', '-.---': 'e', '-.--.': 'ru', '-.-.': 'ni', '-.-. --': 'nyo', '-.-. -..--': 'nyu', '-.-. .--': 'nya', '-.-.-': 'sa', '-.-.- ..': 'za', '-.-..': 'ki', '-.-.. --': 'kyo', '-.-.. -..--': 'kyu', '-.-.. .--': 'kya', '-.-.. ..': 'gi', '-.-.. .. --': 'gyo', '-.-.. .. -..--': 'gyu', '-.-.. .. .--': 'gya', '-..': 'ho', '-.. ..': 'bo', '-.. ..--.': 'po', '-..-': 'ma', '-..--': 'yu', '-..-.': 'mo', '-...': 'ha', '-... ..': 'ba', '-... ..--.': 'pa', '-...-': 'me', '.': 'he', '. ..': 'be', '. ..--.': 'pe', '.-': 'i', '.--': 'ya', '.---': 'wo', '.---.': 'se', '.---. ..': 'ze', '.--.': 'tsu', '.--. ..': 'zu', '.--..': 'we', '.-.': 'na', '.-.-': 'ro', '.-.--': 'te', '.-.-- ..': 'de', '.-.-.': 'n', '.-..': 'ka', '.-.. ..': 'ga', '.-..-': 'wi', '.-...': 'o', '..-': 'u', '..--': 'no', '..-.': 'chi', '..-. --': 'cho', '..-. -..--': 'chu', '..-. .--': 'cha', '..-. ..': 'ji', '..-. .. --': 'jo', '..-. .. -..--': 'ju', '..-. .. .--': 'ja', '..-.-': 'mi', '..-.- --': 'myo', '..-.- -..--': 'myu', '..-.- .--': 'mya', '..-..': 'to', '..-.. ..': 'do', '...': 'ra', '...-': 'ku', '...- ..': 'gu', '....': 'nu'}

    def solve(c):
        c = c.split()
        size = len(c)
        i = 0
        res = ""
        while i < size:
            if "a" <= c[i] <= "z" or "A" <= c[i] <="Z":
                res+=c[i]
                i += 1
                continue
            if (size-i)>=3 and " ".join(c[i:i+3]) in m:
                res += m[" ".join(c[i:i+3])]
                i += 3
                continue
            if (size - i) >= 2 and " ".join(c[i:i + 2]) in m:
                res += m[" ".join(c[i:i + 2])]
                i += 2
                continue
            res += m[c[i]]
            i += 1
        return res
    res = [solve(i) for i in cipher]
    return " ".join(res).encode()


##### ---------------------- Fix --------------
def eastern_twist_abcs(text: bytes) -> bytes:
    plain  = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    cipher = 'XWYAZBCDQEFGHIKLMNOPJRSTUV'
        
    text = text.decode().upper()
    result = ''
    for c in text:
        if c in cipher:
            result += plain[cipher.index(c)]
        else:
            result += c
    print(result.title())
    return result.title().encode()
    


######## ---------------------- FIX --------------------------
def alternating_tones(bibi: bytes) -> bytes:
    bibi_table = {
        'HO':'0','HA':'1','HE':'2','HI':'3',
        'BO':'4','BA':'5','BE':'6','BI':'7',
        'KO':'8','KA':'9','KE':'a','KI':'b',
        'DO':'c','DA':'d','DE':'e','DI':'f'
    }
    
    # Split into 2-letter syllables
    syllables = [bibi[i:i+2].decode() for i in range(0, len(bibi), 2)]
    
    # Map to hex digits
    hex_digits = [bibi_table[s] for s in syllables]
    
    # Join into hex string
    hex_string = ''.join(hex_digits)
    
    # Convert hex to decimal
    number = int(hex_string, 16)
    
    print("Hex:", hex_string)
    print("Decimal:", number)
    return str(number).encode()


def mirror_classical(cipher):
    s = cipher.decode().strip()[:-2] 
    s = s[::-1]  
    res = ' '.join(word.capitalize() for word in s.lower().split())
    return res.encode()


def main():
    conn = remote("103.197.184.48", 12345)
    cnt = 1000

    while cnt > 0:
        conn.recvuntil(b"hint: ")
        hint = conn.recvline().decode().strip()
        print("[+] Hint: ", hint)

        conn.recvuntil(b"cipher: ")
        cipher = conn.recvline().strip()
        print("[+] Cipher: ", cipher)

        if hint == "the very first of the indivisible":
            conn.sendline(indivisible_primes(cipher))
        elif hint == "Braille encoded in 8-dot cells":
            conn.sendline(braille_8dot(cipher))
        elif hint == "shifting letters in a cascade of threes":
            conn.sendline(progressive_cascade(cipher))
        elif hint == "spelled out in the NATO phonetic alphabet":
            conn.sendline(nato_phonetic(cipher))
        elif hint == "Brainfuck, but with spoons instead of forks":
            conn.sendline(spoons_brainfuck(cipher))
        elif hint == "Morse code with a Japanese accent":
            conn.sendline(japanese_morse(cipher))
        elif hint == "an eastern twist on the ABCs":
            conn.sendline(eastern_twist_abcs(cipher))
        elif hint == "encoded as pairs of alternating tones":
            conn.sendline(alternating_tones(cipher))
        elif hint == "mirror it, then add a touch of classical Latin":
            conn.sendline(mirror_classical(cipher))
        else:
            print("[!] Unknown hint: ", hint)
            break

        cnt -= 1

    print("[+] Round: ", 1000 - cnt)
    conn.interactive()

if __name__ == "__main__":
    main()

# Congratulations!
# Here is your flag: PTITCTF{running_on_the_server_is_so_crazy}
```
