# Writeup — EZRSA 


Từ điều kiện RSA: `e * d ≡ 1 (mod phi(n))`. Với `d = p` ta có:  
`e * p ≡ 1 (mod phi(n))` và vì `(p-1)` là ước của `phi(n)`, suy ra **`e ≡ 1 (mod p-1)`**.

Hệ quả: với mọi số nguyên `a`, theo định lý Fermat nhỏ mở rộng,  
**`a^e ≡ a (mod p)`**.

```
g = gcd(a^e - a, n) = p  
```

```python
# solve.py
from Crypto.Util.number import long_to_bytes, inverse, GCD
import random
n = 17214567828398357229643529894295967114363352499098802199894858334085293863341825287910906544494493686384112698195095225053385794088973371397323458418321666327675916513230636104793989067797717706445529776600856609707677648913780791946460982977782195356212507182820036214949481940068433039225015414875241777158003325764872405881572570496190679493447373849996319019598102288666420853150415056950485849279575818156402816776191856047427152544999688568950736168425290093518129670058413768478973322477524419171082000819854631108321230234176824271796110603234303082618740389203049873976008473621649321173853688102041285596241
e = 15440488000729211957610279418931605805589654711493356743965905209276145425852849809312888310379272967334598801649810510348697070096535739532036297540403392167171881768067441561508337590880822861672290233186985387034942614188538085229808917257385229318625614290922403715134153580735609069998947227062942174142730151517393242131507391704997064499542165892278559404838406852685645008075214053882374401792242411576641746065438480381248624838670256786822650763564060448021994952508633074390074128374060992679707236024844673099693214372403996970791536012149996254474491705964926081420031667815035866895342358734670639887169
c = 2402138959153051396320943729277461170773667922351093944074722376521237389464692434251911375749083878511997619061766771696998680583640661543963425049461931196141770452130968180714299528148635742852818728071800606030028670445222713727143968250556737720752366932414925949892158179243847407401643660893432149798496795739805059615071574403567868520336932612028074092301976357005203460281680124320522122292074540003162762559783225589480645595685851382155354113399084178162200670604735886151583943618933977027880216736502657283592205972435022183995754583696686836691748834990167700258559540373094124937235886762980711070096
def factor_from_e(n, e):
   
    for r in [2, 3, 5, 7, 11, 13, 17, 19]:
        g = GCD(pow(r, e, n) - r, n)
        if 1 < g < n:
            return g, n // g

    for _ in range(128):
        r = random.randrange(2, n-1)
        g = GCD(pow(r, e, n) - r, n)
        if 1 < g < n:
            return g, n // g
    raise RuntimeError("Factorization failed; try more bases.")

p, q = factor_from_e(n, e)
phi = (p - 1) * (q - 1)
d = inverse(e, phi)       
m = pow(c, d, n)
flag = long_to_bytes(m)

print("p =", p)
print("q =", q)
print("flag =", flag)
#PTITCTF{F3rm47_Th30r3m_34zy_t0_cr4ck}

```


# Writeup — BLAKE



Xem cuối chương trình (`main`) thấy luồng xử lý:
```python
h = blake2b(data)           
d = h.digest()               
if getattr(h, "_reveal", False):
    print(FLAG)              # chỉ in FLAG khi _reveal == True
else:
    print(d.hex())
```

Đi vào `blake2b.digest()` thấy trong `_finalize()` có **nhánh kiểm tra RSA** chỉ chạy khi dữ liệu đầu vào ngắn (chưa vượt 1 block 128 byte):
```python
only_key_processed = (self.t0 == (self.BLOCK_SIZE if self._had_key else 0))
if only_key_processed:
    m = bytes_to_long(self.buf)      # buf là đúng bytes nhập
    E = self._exp_from_sigma()       #  lấy từ SIGMA[12]
    if pow(m % N, E, N) == C:        # N, C trong file
        self._reveal = True
```
=> **Điều kiện để chương trình in flag:** tìm chuỗi ASCII `s` sao cho
```
pow(int.from_bytes(s, "big") % N, E, N) == C
```

---



Mã tạo N dùng một prime 256-bit `p` và hai thừa số “đặc chế”:
```
q = (p << 256) | (2^256 - 1)                  # q = p*2^256 + (2^256-1)
r = magicc(p)                                  # mở rộng từng bit của p:
# với magicc: 0 -> 01, 1 -> 11  (mỗi bit p thành 2 bit trong r)
N = q * r
```

```
q ≡ -1 (mod 2^256)  ⇒  N = q*r ≡ -r (mod 2^256).
```
Do đó **256 bit thấp của r** chính là `(-N) mod 2^256`. Mà r được tạo từ cặp bit `01/11`, nên **chỉ cần đọc bit thứ hai của từng cặp** là lấy được **128 bit thấp của p** ngay.

Để lấy đủ 256 bit của `p`, ta “nâng modulo theo lũy thừa của 2”:
- Giả sử đã biết `k` bit thấp của `p`.
- Khi đó:
  ```
  K = q mod 2^(256+k) = (2^256 - 1) + ((p mod 2^k) << 256)
  ```
  `K` là số lẻ ⇒ tồn tại `K^{-1} (mod 2^(256+k))` (tính bằng Newton–Hensel).
- Ta suy được:
  ```
  r mod 2^(256+k) = (N * K^{-1}) mod 2^(256+k)
  ```
  Từ đây đọc được `(256+k)//2` bit thấp của `p`. Lặp lại cho đến khi thu đủ 256 bit.

Cuối cùng đặt bit cao để đảm bảo `p` là 256-bit rồi dựng lại:
```
q = (p << 256) + (2^256 - 1)
r = magicc(p)
```


```python
# solve.py 

N = int("7fed997cfb3a3e8440142aba39d2c62ef03e773f8d98d7d373b3e8336903ca122cdffa11fd4de735776c9aefdd1607c70f0c403bd745d2e3065fede7f22dbfa94ea22b833b2442bd474a88694305b0f389162ca25eddf2673baeb3b6a2855842a0a0a022a2a222a28802a2022888822a8a20aa20a28022a08088200a8a800801", 16)
C = int("16c88a06c4203b9ce6f5f652a52f449ce37347afb5cb25b0a1bf0b105f158246bd64adb2b6f2a563fa747d31b9ba4af54efd9449f6b75b1ea83015fefb1e1d206f20ca31fdf47ee45bbb382c9aa6e7ff7946f9973a2edebdb412bdc48e9a157cb36eb2e599c9c0a27153983d316b0d9ce08ef9d06f536b2ff29cf5393fba056d", 16)
E = 1234567891  # lấy từ SIGMA[12][:10]

def magicc(n: int) -> int:
    return int(''.join('01' if b=='0' else '11' for b in bin(n)[2:]), 2)

def bits_from_magic_r(r_mod, k_bits):
    p = 0
    for i in range(k_bits):
        p |= ((r_mod >> (2*i+1)) & 1) << i
    return p

def inv_mod_2n(a, n):
    assert a & 1
    inv, k = 1, 1
    while k < n:
        inv = (inv * (2 - a * inv)) & ((1 << (2*k)) - 1)
        k *= 2
    return inv & ((1 << n) - 1)


r_mod = (-N) & ((1 << 256) - 1)
p_known = bits_from_magic_r(r_mod, 128)
k = 128


while k < 256:
    mod_bits = 256 + k
    mod = 1 << mod_bits
    K = ((1 << 256) - 1) + ((p_known & ((1 << k) - 1)) << 256)   
    K &= (mod - 1)
    invK = inv_mod_2n(K, mod_bits)
    r_mod = (N * invK) & (mod - 1)
    s = (256 + k) // 2
    p_known = bits_from_magic_r(r_mod, s)
    if s == k:
        break
    k = s
p = p_known | (1 << 255)             
q = (p << 256) + ((1 << 256) - 1)
r = magicc(p)
assert q * r == N

phi = (q - 1) * (r - 1)
d = pow(E, -1, phi)
m = pow(C, d, N)

m_bytes = m.to_bytes((m.bit_length() + 7) // 8, 'big')
print("message bytes:", m_bytes)

#b'ghost_round_sigma12'

```

`FLAG: PTITCTF{ghost_round_sigma_and_coppersmith_is_awesome}`



# Writeup — Corrupted Secret

1) **Mô hình hóa**  
Xem các byte là phần tử **GF(256)**. Dùng hoán vị đầu vào là **nghịch đảo nhân**; map 0→0.

2) **Hệ biến đổi**  
Đặt dãy:  
- `a0 = i`  
- `a_{n+1} = (a_n + k_n)^(-1)`  (nếu `a_n + k_n = 0` thì gán kết quả = 0)  
- Kết quả cuối: `f(i) = a_63 + k_63`.

3) **Möbius tổng quát**  
`x -> x + k` và `x -> 1/x` đều là Möbius ⇒ hợp 63 bước đầu là **Möbius**: `T(x) = (A*x + B) / (C*x + D)`.

4) **Fit T(x)**  
Chọn vài `i` ngẫu nhiên (đa số **không** rơi vào zero‑sequence), lấy `(i, f(i))`, dựng hàng `[i, 1, -(f*i), -f]` trên GF(256), giải **kernel** ⇒ `(A,B,C,D)`.

5) **Zero‑sequence = chỗ “gãy”**  
Nếu có bước `a_n + k_n = 0` ta ép kết quả = 0 ⇒ **không khớp** với `T(i)`.  
Số vị trí “không khớp” trên 256 giá trị = **số zero‑sequences**. Trạng thái thuận lợi: **63**.

6) **Oracle đếm zero để lộ khóa**  
Chưa được 63 → **reroll**. Khi bằng 63:  
- Ở vị trí khóa hiện tại, thử mọi `k`.  
- Cập nhật `T ← T ∘ S_k^{-1}` và miền `x ← (x+k)^(-1)`.  
- **Đúng k** ⇒ số zero‑sequences **giảm đúng 1**. Chốt byte và lặp.

7) **Kết thúc**  
Gỡ xong 63 byte đầu. Byte cuối: `k_63 = i_perm[0] - f_perm[0]` (GF(2): chính là XOR).  
Ghép 64 byte KEY, gửi → nhận **flag**.


```
from sage.all import *
import os
# Workaround for a sage + pwntools bug
import os
os.environ['TERM'] = 'linux'

from pwn import *

F= GF(2 ** 8, name = "x")
x = F.gen()

def to_gf(n):
    return sum(c*x**i for i,c in enumerate(map(int, bin(n % 256)[2:][::-1])))

def from_gf(n):
    return int("".join(map(str, n.list()[::-1])), 2)

def to_hex_string(l):
    return "".join(f"{i:02x}" for i in l)

def compute_pattern(i_perm, f_perm, T):
    """Computes which sequences contain a discrepancy"""
    a, b, c, d = T.list()
    pattern = [0] * 256
    for i, x in enumerate(i_perm):
        if c * x + d != 0:
            res = (a * x + b) / (c * x + d)
        else:
            res = 0
        pattern[i] = int(f_perm[i] != res)
    return pattern

def step_f(perm, k):
    """steps the sequence using k"""
    return [(i + k) ** -1 if (i + k) != 0 else F(0) for i in perm]

def compute_mobius_0(f_perm, N_samples=8):
    """Computes the total mobius transform of f for a non-zero sequence"""
    while True:
        idxs = random.sample(list(range(256)), k=N_samples)
        M = matrix(F, [[F.from_integer(idx), 1, -f_perm[idx]*F.from_integer(idx), -f_perm[idx]] for idx in idxs])
        ker = M.right_kernel_matrix()
        if ker.nrows() != 0:
            break
    a, b, c, d = ker[0]
    return(a, b, c, d)

def mobius_inverse(k):
    """Returns the inverse of some intermediate mobius for some key byte"""
    return Matrix(F, [[-k, 1], [1, 0]])

perm = []
for i in range(256):
    if i == 0:
        perm.append(0)
        continue
    perm.append(from_gf(to_gf(i) ** -1))

assert sorted(perm) == list(range(256))
print(perm)
perm_hex = to_hex_string(perm)
print(perm_hex)

best = 0
attempts = 0

io = process(["python3", "chall.py"])
#io = remote("103.197.184.48", 12348)
print("Trying for favorable conditions...")
while True:
    attempts += 1

    io.recvuntil(b": ")
    io.sendline(perm_hex.encode())
    io.recvuntil(b": ")
    cp = bytes.fromhex(io.recvline().strip().decode())
    f_perm = [to_gf(i) for i in cp]

    i_perm = [to_gf(i) for i in range(256)]
    a, b, c, d = compute_mobius_0(f_perm)
    T_org = Matrix(F, [[a, b], [c, d]])

    pattern = compute_pattern(i_perm, f_perm, T_org)
    n_zeros = sum(pattern)
    if n_zeros > best:
        best = n_zeros

    print(f"Attempts: {attempts}, Zero sequences: {n_zeros}, best: {best}")
    # Small brute for favorable conditions
    if n_zeros != 63:
        io.recvuntil(b"KEY:")
        io.sendline(b"00" * 64)
        continue

    key = [0] * 64
    for key_idx in range(63):
        for k in i_perm:
            # Compose with the inverse of a step to get the mobius transform
            # starting at a later point in the sequence
            T = T_org * mobius_inverse(k)
            new_perm = step_f(i_perm, k)

            pattern2 = compute_pattern(new_perm, f_perm, T)
            if sum(pattern) > sum(pattern2):
                print("Found key byte:", from_gf(k))
                key[key_idx] = from_gf(k)
                T_org = T
                pattern = pattern2
                i_perm = new_perm
                break
        else: # Should not trigger if conditions are favorable
            print(key)
            print("Failed to find key byte: ", key_idx)
            exit()

    # final key is just their difference
    key[-1] = from_gf(i_perm[0] - f_perm[0])
    key_hex = to_hex_string(key)

    print(f"{key = }")
    io.sendlineafter(b"KEY:", key_hex)
    io.interactive()
    exit()

```
`FLAG: PTITCTF{SBOX_IS_JUST_YOUR_PERM}`


# Writeup — CRT 


Bài cho RSA 1024-bit với `e` là prime 72-bit, và rò rỉ **199 bit thấp** của hai mũ CRT:  
```
d1 = d_p mod 2^199, d2 = d_q mod 2^199 với d_p ≡ e^{-1} (mod p-1), d_q ≡ e^{-1} (mod q-1).
```


Vì chỉ biết **low 199 bits** của `d_p, d_q`, ta không khôi phục trực tiếp `d_p, d_q`. Nhưng từ
   ```
   e·d_p = 1 + k·(p-1),   e·d_q = 1 + ℓ·(q-1), d1 ≡ d_p (mod 2^199), d2 ≡ d_q (mod 2^199), gcd(2e, k)=gcd(2e, ℓ)=1, L = e·2^199
   ```
 thu được
   ```
   p ≡ (k - 1 + e·d1)·k^{-1} (mod L)
   q ≡ (ℓ - 1 + e·d2)·ℓ^{-1} (mod L).
   ```
Dùng `pq ≡ n (mod L)` để dựng đa thức bậc hai trong `k,ℓ`:
```
e·u - 1 = k(p-1),    e·v - 1 = ℓ(q-1)    (u=d_p, v=d_q)
```
suy ra
```
0 ≡ (e·u - 1)(e·v - 1) - kℓ(p-1)(q-1)
  = e^2 u v - e(u+v) + 1 - kℓ(pq - p - q + 1).
```
Thay `pq = n` và nhóm theo `k,ℓ`, rồi thay `u ≡ d1 (mod 2^199)`, `v ≡ d2 (mod 2^199)` trong hạng tự do, ta được
   ```
   f(k,ℓ) = (n-1)kℓ - (e·d2 - 1)k - (e·d1 - 1)ℓ + (e(d1+d2) - e^2·d1·d2 - 1) ≡ 0 (mod L).
   ```
Chạy **Coppersmith** với bound tự nhiên `|k|,|ℓ| ≲ e` để tìm nghiệm nhỏ `(k,ℓ)`.
```
import itertools

def coppersmith(f, bounds, m, d):
    R = f.base_ring()
    N = R.cardinality()
    f = f.change_ring(ZZ)
    G = Sequence([], f.parent())
    for i in range(m+1):
        base = N^(m-i) * f^i
        for shifts in itertools.product(range(d), repeat=f.nvariables()):
            g = base * prod(map(power, f.variables(), shifts))
            G.append(g)
    B, monomials = G.coefficients_monomials()
    monomials = vector(monomials)
    factors = [monomial(*bounds) for monomial in monomials]
    for i, factor in enumerate(factors):
        B.rescale_col(i, factor)
    B = B.dense_matrix().LLL()
    B = B.change_ring(QQ)
    for i, factor in enumerate(factors):
        B.rescale_col(i, 1/factor)
    H = Sequence([], f.parent().change_ring(QQ))
    for h in filter(None, B*monomials):
        H.append(h)
        I = H.ideal()
        if I.dimension() == -1:
            H.pop()
        elif I.dimension() == 0:
            roots = []
            for root in I.variety(ring=ZZ):
                root = tuple(R(root[var]) for var in f.variables())
                roots.append(root)
            return roots
    return []

nbit, ebit, xbit = 512, 72, 313
i = nbit - xbit

e = 3861901490145458111477
n = 137940751004272201162025530857221309460632160459760825050993948546951353644661537367241466716134207605941180677339445186374809373126169914952085814238651790654917329627745754957855823684203733978057367731073320325919126044722823912808661328406837065889544747175303400554078161105913582233404911254574255397291
U = 426253526612025179832925751049946669082499321677414766028031
V = 642008917851211925983957051689520126144299807386027966777885
c = 5702925594043607091796366292210348527941801296416767308113143735663770507926323501002906108435688120415615640448870471530599889719303986341471958697402844747584886670216351648836451765234778570348523264995413222075259341742885800243228176906517689414090001575225471912411801189326329785835531555207672363448
l_dp = U
l_dq = V

PR.<x, y> = PolynomialRing(Zmod(e*2**i), 2)
A = e*(l_dp + l_dq) - e**2 * l_dp * l_dq - 1
f = (n-1)*x*y - (e*l_dq-1)*x - (e*l_dp-1)*y + A
k, l = coppersmith(f, bounds=(e,e), m=2, d=3)[0]
print('k, l', k, l)
```

Ý tưởng: chọn `a` dựa vào ràng buộc từ `U` (199 bit thấp của `d_p`) và `k` để tồn tại `h_dp` nhỏ sao cho `p = a + h_dp`. Khi tìm được `h_dp` với `|h_dp| < X` (`X = 2^313`), ta khôi phục `p`.

---

## Code 
```python
nbit, ebit, xbit = 512, 72, 313
i = nbit - xbit
e = 3861901490145458111477
n = 137940751004272201162025530857221309460632160459760825050993948546951353644661537367241466716134207605941180677339445186374809373126169914952085814238651790654917329627745754957855823684203733978057367731073320325919126044722823912808661328406837065889544747175303400554078161105913582233404911254574255397291
U = 426253526612025179832925751049946669082499321677414766028031
V = 642008917851211925983957051689520126144299807386027966777885
c = 5702925594043607091796366292210348527941801296416767308113143735663770507926323501002906108435688120415615640448870471530599889719303986341471958697402844747584886670216351648836451765234778570348523264995413222075259341742885800243228176906517689414090001575225471912411801189326329785835531555207672363448
l_dp = U
l_dq = V
k, l = 2543641529042634142025, 2832842631913163018172

def solve(f, X, m, t): 
    F = []
    S = []
    for j in range(m+1):
        h = f^j*k^(m-j)*n^(max(0,t-j))
        F.append(h)
        S.append(x^j)
    MAT = Matrix(ZZ, len(F))
    for i in range(len(F)):
        f = F[i]
        f = f(x*X)
        coeffs = (f.coefficients())
        for j in range(len(coeffs), len(F)):
            coeffs.append(0)
        coeffs = vector(coeffs)
        MAT[i] = coeffs
    MAT = MAT.LLL()
    ret = []
    for j in range(len(F)):
        f = 0
        for i in range(len(S)):
            f += MAT[j,i]//S[i](X)*S[i]
            roots = f.roots()
            if roots != []:
                ret.append(roots[0][0])
        return ret

R.<x> = QQ[]
a = int((e*l_dp + k - 1) * pow(e*2**i, -1, k*n))
f = x + a
for h_dp in solve(f, X=2**(512-i), m=20, t=10):
    p = gcd(int(f(x=h_dp)), n)
    if is_prime(p):
        print(f'{p = }')
        break
flag = GF(p)(c).nth_root(e)
print(bytes.fromhex(f'{int(flag):x}'))
#PTITCTF{CRT_Exponents_Approximate_Divisor_Multiples_is_Secret}
```

# Writeup — Walking

Ta sẽ đi tìm 9 bảng mapping của 9 thuật toán mã hóa để viết lại tất cả các hàm decode.

## Bibi-binary Code

```python
# bibi.py
BIBI_MAP = {
    '0': 'HO', '1': 'HA', '2': 'HE', '3': 'HI',
    '4': 'BO', '5': 'BA', '6': 'BE', '7': 'BI',
    '8': 'KO', '9': 'KA', 'a': 'KE', 'b': 'KI',
    'c': 'DO', 'd': 'DA', 'e': 'DE', 'f': 'DI'
}
BIBI_INV = {v: k for k, v in BIBI_MAP.items()}
def encode_bibi(n: int) -> str:
    if n < 0:
        raise ValueError("Chỉ hỗ trợ số nguyên không âm.")
    hex_str = format(n, 'x')
    return ''.join(BIBI_MAP[d] for d in hex_str)

def decode_bibi(s: str) -> int:
    s = s.strip()
    if len(s) % 2 != 0:
        raise ValueError("Độ dài chuỗi Bibi phải chẵn (multiples of 2).")
    hex_digits = []  
    for i in range(0, len(s), 2):
        token = s[i:i+2].upper()
        if token not in BIBI_INV:
            raise ValueError(f"Token không hợp lệ tại vị trí {i}: '{token}'")
        hex_digits.append(BIBI_INV[token])
    hex_str = ''.join(hex_digits)
    return int(hex_str, 16)

def main():
    print("=== Bibi-binary Converter ===")
    mode = ''
    while mode not in ('e', 'd'):
        mode = input("(e)ncode base10→Bibi / (d)ecode Bibi→base10: ").strip().lower()

    if mode == 'e':
        s = input("Nhập số nguyên (base10): ").strip()
        if not s.isdigit():
            print("Lỗi: phải nhập số nguyên không âm.")
            return
        n = int(s)
        bibi = encode_bibi(n)
        print(f"\nHex: {format(n, 'x')}")
        print(f"Bibi-binary: {bibi}")
    else:
        s = input("Nhập chuỗi Bibi-binary: ").strip()
        try:
            val = decode_bibi(s)
        except ValueError as e:
            print("Lỗi:", e)
            return
        print(f"\nHex: {format(val, 'x')}")
        print(f"Decimal: {val}")


if __name__ == "__main__":
    main()

```

## Charabia Latin

```python
#charabia_latin.py
import random

def charabia_latin_encoder(word: str) -> str:
    reversed_word = word[::-1]
    ending = random.choice(['us', 'um', 'it'])
    return reversed_word + ending

def charabia_latin_decoder(encoded: str) -> str:
    for ending in ('us', 'um', 'it'):
        if encoded.endswith(ending):
            core = encoded[:-len(ending)]
            return core[::-1]
    return encoded[::-1]

def main():
    print("=== Charabia Latin Converter ===")
    mode = ''
    while mode not in ('e','d'):
        mode = input("(e)ncode / (d)ecode: ").strip().lower()

    word = input("Nhập từ: ").strip()

    if mode == 'e':
        out = charabia_latin_encoder(word)
        print("\n→ Encoded:", out)
    else:
        out = charabia_latin_decoder(word)
        print("\n→ Decoded:", out)

if __name__ == "__main__":
    main()

```

## chiffre_tritheme

```PYTHON
#chiffre_tritheme.py
def chiffre_de_tritheme(texte: str, decalage: int) -> str:
    resultat = []
    for i, char in enumerate(texte):
        if char.isalpha():
            decalage_actuel = (decalage + i) % 26
            base = 'a' if char.islower() else 'A'
            nouveau_char = chr((ord(char) - ord(base) + decalage_actuel) % 26 + ord(base))
            resultat.append(nouveau_char)
        else:
            resultat.append(char)
    return ''.join(resultat)

def dechiffre_de_tritheme(texte: str, decalage: int) -> str:
    resultat = []
    for i, char in enumerate(texte):
        if char.isalpha():
            decalage_actuel = (decalage + i) % 26
            base = 'a' if char.islower() else 'A'
            ancien_char = chr((ord(char) - ord(base) - decalage_actuel) % 26 + ord(base))
            resultat.append(ancien_char)
        else:
            resultat.append(char)
    return ''.join(resultat)

def main():
    print("=== Chiffre de Trithème ===")
    mode = ''
    while mode not in ('e','d'):
        mode = input("(e)ncode / (d)ecrypt: ").strip().lower()

    texte = input("Entrez le texte:\n")
    try:
        decalage = int(input("Entrez le décalage initial (entier ≥0): ").strip())
    except ValueError:
        print("Décalage non valide, doit être un entier.")
        return

    if mode == 'e':
        res = chiffre_de_tritheme(texte, decalage)
        print("\n→ Texte chiffré:")
    else:
        res = dechiffre_de_tritheme(texte, decalage)
        print("\n→ Texte déchiffré:")
    print(res)

if __name__ == '__main__':
    main()

```

## GS8 Braille Code
```python
# GS8_Braille.py
GS8_MAP = {
    # lowercase
    'a':'⠁','b':'⠃','c':'⠉','d':'⠙','e':'⠑','f':'⠋','g':'⠛','h':'⠓','i':'⠊','j':'⠚',
    'k':'⠅','l':'⠇','m':'⠍','n':'⠝','o':'⠕','p':'⠏','q':'⠟','r':'⠗','s':'⠎','t':'⠞',
    'u':'⠥','v':'⠧','w':'⠺','x':'⠭','y':'⠽','z':'⠵',
    # uppercase
    'A':'⡁','B':'⡃','C':'⡉','D':'⡙','E':'⡑','F':'⡋','G':'⡛','H':'⡓','I':'⡊','J':'⡚',
    'K':'⡅','L':'⡇','M':'⡍','N':'⡝','O':'⡕','P':'⡏','Q':'⡟','R':'⡗','S':'⡎','T':'⡞',
    'U':'⡥','V':'⡧','W':'⡺','X':'⡭','Y':'⡽','Z':'⡵',
}

INV_GS8_MAP = {v:k for k,v in GS8_MAP.items()}

def gs8_encode(text: str) -> str:
    out = []
    for ch in text:
        out.append(GS8_MAP.get(ch, ch))
    return ''.join(out)

def gs8_decode(braille: str) -> str:
    out = []
    for ch in braille:
        out.append(INV_GS8_MAP.get(ch, ch))
    return ''.join(out)

def main():
    print("=== Gardner–Salinas 8 (GS8) Braille Converter ===")
    mode = ''
    while mode not in ('e','d'):
        mode = input("(e)ncode ASCII→GS8 / (d)ecode GS8→ASCII: ").strip().lower()

    s = input("Nhập chuỗi:\n")
    if mode == 'e':
        print("\n→ GS8 Braille:")
        print(gs8_encode(s))
    else:
        print("\n→ ASCII:")
        print(gs8_decode(s))

if __name__ == '__main__':
    main()

```


## NATO
```python
# otan.py

import re

# Bảng NATO phonetic
phonetic_alphabet = {
    'A': 'Alfa',     'B': 'Bravo',    'C': 'Charlie', 'D': 'Delta',
    'E': 'Echo',     'F': 'Foxtrot',  'G': 'Golf',    'H': 'Hotel',
    'I': 'India',    'J': 'Juliett',  'K': 'Kilo',    'L': 'Lima',
    'M': 'Mike',     'N': 'November', 'O': 'Oscar',   'P': 'Papa',
    'Q': 'Quebec',   'R': 'Romeo',    'S': 'Sierra',  'T': 'Tango',
    'U': 'Uniform',  'V': 'Victor',   'W': 'Whiskey', 'X': 'X-ray',
    'Y': 'Yankee',   'Z': 'Zulu',
    '0': 'Zero',     '1': 'One',      '2': 'Two',     '3': 'Three',
    '4': 'Four',     '5': 'Five',     '6': 'Six',     '7': 'Seven',
    '8': 'Eight',    '9': 'Nine'
}

inv_phonetic = {v.upper(): k for k, v in phonetic_alphabet.items()}

def encode_to_phonetic(text: str) -> str:
    out = []
    for ch in text.upper():
        out.append(phonetic_alphabet.get(ch, ch))
    return ' '.join(out)

def decode_from_phonetic(code: str) -> str:

    word_chunks = re.split(r'\s{2,}', code.strip())

    decoded_words = []
    for chunk in word_chunks:
        tokens = chunk.strip().split()
        letters = [inv_phonetic.get(tok.upper(), tok) for tok in tokens]
        decoded_words.append(''.join(letters))

    return ' '.join(decoded_words).title()

def main():
    print("=== NATO Phonetic Converter ===")
    mode = ''
    while mode not in ('e', 'd'):
        mode = input("(e)ncode → phonetic / (d)ecode → text: ").strip().lower()

    data = input("Entrez votre chaîne:\n")
    if mode == 'e':
        result = encode_to_phonetic(data)
        print("\n→ Encoded phonetic:\n" + result)
    else:
        result = decode_from_phonetic(data)
        print("\n→ Decoded text:\n" + result)

if __name__ == '__main__':
    main()

```

## PRIME
```python
# prime.py
import re

PRIMES = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101]
LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
ENC_MAP = {LETTERS[i]: str(PRIMES[i]) for i in range(26)}
DEC_MAP = {str(PRIMES[i]): LETTERS[i] for i in range(26)}

def prime_encode(text: str) -> str:
    out = []
    for ch in text.upper():
        out.append(ENC_MAP.get(ch, ch))
    return " ".join(out)

def prime_decode(code_str: str) -> str:
    parts = re.split(r'( +)', code_str.strip())
    out = []
    for part in parts:
        if part.isspace():
            if len(part) > 1:
                out.append(' ')
        else:
            out.append(DEC_MAP.get(part, ''))
    return ''.join(out).title()

def main():
    print("=== Prime-Number Substitution Cipher ===")
    mode = ""
    while mode not in ("e","d"):
        mode = input("(e)ncode / (d)ecode: ").strip().lower()

    s = input("Nhập chuỗi: ").rstrip()
    if mode == "e":
        print("\n→ Encoded:")
        print(prime_encode(s))
    else:
        print("\n→ Decoded:")
        print(prime_decode(s))

if __name__ == "__main__":
    main()

```

## Shankar Cipher
```python
# shankar.py
# Bảng hoán vị
original_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
shankar_alphabet = "XWYAZBCDQEFGHIKLMNOPJRSTUV"

# Tạo dict mã hóa và giải mã
encrypt_dict = {original_alphabet[i]: shankar_alphabet[i] for i in range(26)}
decrypt_dict = {shankar_alphabet[i]: original_alphabet[i] for i in range(26)}

def shankar_encrypt(text: str) -> str:
    out = []
    for ch in text.upper():
        out.append(encrypt_dict.get(ch, ch))
    return ''.join(out)

def shankar_decrypt(text: str) -> str:
    out = []
    for ch in text.upper():
        out.append(decrypt_dict.get(ch, ch))
    return ''.join(out)

def main():
    print("=== Shankar Substitution Cipher ===")
    mode = ''
    while mode not in ('e','d'):
        mode = input("(e)ncrypt / (d)ecrypt: ").strip().lower()

    s = input("Nhập chuỗi: ")
    if mode == 'e':
        res = shankar_encrypt(s)
        print("\n→ Encrypted:")
    else:
        res = shankar_decrypt(s)
        print("\n→ Decrypted:")
    print(res)

if __name__ == '__main__':
    main()

```

## spoon
```python
# spoon.py
import sys

# Mapping Brainfuck → Spoon (binary strings)
BF_TO_SPOON = {
    '+': '1',        # increment
    '-': '000',      # decrement
    '>': '010',      # move right
    '<': '011',      # move left
    '[': '00100',    # start loop
    ']': '0011',     # end loop
    '.': '001010',   # output
    ',': '0010110',  # input (rarely used)
}

SPOON_TO_BF = {v: k for k, v in BF_TO_SPOON.items()}
TOKENS = sorted(SPOON_TO_BF.keys(), key=len, reverse=True)


def bf_generate_print(s: str) -> str:

    code = []
    prev = 0
    for ch in s:
        o = ord(ch)
        diff = o - prev
        if diff > 0:
            code.append('+' * diff)
        elif diff < 0:
            code.append('-' * (-diff))
        code.append('.')  # output
        prev = o
    return ''.join(code)


def spoon_encode(bf_code: str) -> str:
    """Chuyển Brainfuck → Spoon (0/1)."""
    out = []
    for c in bf_code:
        if c in BF_TO_SPOON:
            out.append(BF_TO_SPOON[c])
    return ''.join(out)


def spoon_decode(spoon: str) -> str:
    # 1) parse
    i = 0
    bf = []
    while i < len(spoon):
        for tok in TOKENS:
            if spoon.startswith(tok, i):
                bf.append(SPOON_TO_BF[tok])
                i += len(tok)
                break
        else:
            # không khớp bất kỳ token nào → lỗi
            raise ValueError(f"Invalid Spoon token at pos {i}")
    bf_code = ''.join(bf)

    # 2) interpret BF
    return bf_interpret(bf_code)


def bf_interpret(code: str, inp: str = '') -> str:
    tape = [0] * 30000
    ptr = 0
    pc = 0
    out = []
    # build bracket map
    stack = []
    jm = {}
    for idx, c in enumerate(code):
        if c == '[':
            stack.append(idx)
        elif c == ']':
            j = stack.pop()
            jm[j] = idx
            jm[idx] = j

    while pc < len(code):
        c = code[pc]
        if c == '+':
            tape[ptr] = (tape[ptr] + 1) & 0xFF
        elif c == '-':
            tape[ptr] = (tape[ptr] - 1) & 0xFF
        elif c == '>':
            ptr += 1
        elif c == '<':
            ptr -= 1
        elif c == '.':
            out.append(chr(tape[ptr]))
        elif c == ',':
            tape[ptr] = ord(inp[0]) if inp else 0
        elif c == '[' and tape[ptr] == 0:
            pc = jm[pc]
        elif c == ']' and tape[ptr] != 0:
            pc = jm[pc]
        pc += 1

    return ''.join(out)


def main():
    print("=== ASCII ⇄ Spoon Converter ===")
    mode = ''
    while mode not in ('e', 'd'):
        mode = input("(e)ncode ASCII→Spoon / (d)ecode Spoon→ASCII: ").strip().lower()

    if mode == 'e':
        s = input("Nhập chuỗi ASCII: ")
        bf = bf_generate_print(s)
        spoon = spoon_encode(bf)
        print("\n[1] Brainfuck code:")
        print(bf)
        print("\n[2] Spoon encoding (0/1):")
        print(spoon)
    else:
        s = input("Nhập Spoon code (chuỗi 0 và 1):\n")
        try:
            decoded = spoon_decode(s.strip())
        except ValueError as err:
            print("Lỗi decode:", err)
            return
        print("\nKết quả ASCII:")
        print(decoded)


if __name__ == "__main__":
    main()

```

## Wabun
```python
# wabun.py
import re
alphabet = "a, i, u, e, o, ka, ki, ku, ke, ko, sa, shi, su, se, so, ta, chi, tsu, te, to, na, ni, nu, ne, no, ha, hi, fu, he, ho, ma, mi, mu, me, mo, ya, yu, yo, ra, ri, ru, re, ro, wa, wi, n, we, wo, kya, kyu, kyo, sha, shu, sho, cha, chu, cho, nya, nyu, nyo, hya, hyu, hyo, mya, myu, myo, rya, ryu, ryo, ga, gi, gu, ge, go, gya, gyu, gyo, za, ji, zu, ze, zo, ja, ju, jo, da, ji, zu, de, do, ja, ju, jo, ba, bi, bu, be, bo, bya, byu, byo, pa, pi, pu, pe, po, pya, pyu, pyo"
alphabet_wabun = alphabet.split(", ")

code = "--.--   .-   ..-   -.---   .-...   .-..   -.-..   ...-   -.--   ----   -.-.-   --.-.   ---.-   .---.   ---.   -.   ..-.   .--.   .-.--   ..-..   .-.   -.-.   ....   --.-   ..--   -...   --..-   --..   .   -..   -..-   ..-.-   -   -...-   -..-.   .--   -..--   --   ...   --.   -.--.   ---   .-.-   -.-   .-..-   .-.-.   .--..   .---   -.-.. .--   -.-.. -..--   -.-.. --   --.-. .--   --.-. -..--   --.-. --   ..-. .--   ..-. -..--   ..-. --   -.-. .--   -.-. -..--   -.-. --   --..- .--   --..- -..--   --..- --   ..-.- .--   ..-.- -..--   ..-.- --   --. .--   --. -..--   --. --   .-.. ..   -.-.. ..   ...- ..   -.-- ..   ---- ..   -.-.. .. .--   -.-.. .. -..--   -.-.. .. --   -.-.- ..   ..-. ..   .--. ..   .---. ..   ---. ..   ..-. .. .--   ..-. .. -..--   ..-. .. --   -. ..   ..-. ..   .--. ..   .-.-- ..   ..-.. ..   ..-. .. .--   ..-. .. -..--   ..-. .. --   -... ..   --..- ..   --.. ..   . ..   -.. ..   --..- .. .--   --..- .. -..--   --..- .. --   -... ..--.   --..- ..--.   --.. ..--.   . ..--.   -.. ..--.   --..- ..--. .--   --..- ..--. -..--   P --"
code_wabun = code.split("   ")

wabun_code = dict(zip(alphabet_wabun, code_wabun))

def encode_wabun(text):
    encoded_text = []
    i = 0
    while i < len(text):
        if i + 3 <= len(text) and text[i:i+3] in wabun_code:
            encoded_text.append(wabun_code[text[i:i+3]])
            i += 3
        elif i + 2 <= len(text) and text[i:i+2] in wabun_code:
            encoded_text.append(wabun_code[text[i:i+2]])
            i += 2
        elif i + 1 <= len(text) and text[i:i+1] in wabun_code:
            encoded_text.append(wabun_code[text[i:i+1]])
            i += 1
        else:
            encoded_text.append(text[i])  
            i += 1
    return ' '.join(encoded_text)

def decode_wabun(code_str: str) -> str:
    tokens = code_str.split()
    i = 0
    decoded = []
    while i < len(tokens):
        for k in (3, 2, 1):
            if i + k <= len(tokens):
                chunk = " ".join(tokens[i:i+k])
                if chunk in inv_wabun_code:
                    decoded.append(inv_wabun_code[chunk])
                    i += k
                    break
        else:
            decoded.append(tokens[i])
            i += 1

    out = "".join(decoded)
    out = re.sub(r'([a-z])([A-Z])', r'\1 \2', out)
    return out
def main():
    print("=== Wabun (Morse Nhật Bản) Converter ===")
    mode = ""
    while mode not in ("e", "d"):
        mode = input("(e)ncode Latin→Wabun / (d)ecode Wabun→Latin: ").strip().lower()

    data = input("Nhập nội dung:\n").strip()
    if mode == "e":
        print("\n→ Mã Wabun:")
        print(encode_wabun(data))
    else:
        print("\n→ Giải mã Latin:")
        print(decode_wabun(data))

if __name__ == "__main__":
    main()

```

## Solve
```python


from pwn import remote, context, log
import re

import bibi, GS8_Braille, charabia_latin, chiffre_tritheme
import otan, shankar, prime, spoon, wabun

context.log_level = 'info'
HOST, PORT = '103.197.184.48', 12345

def norm(words: str) -> str:
    return ' '.join(w.capitalize() for w in re.split(r'\s+', words.strip()))


def solve_bibi(ct):                        
    return str(bibi.decode_bibi(ct))

def solve_charabia(ct):
    return norm(charabia_latin.charabia_latin_decoder(ct))

def solve_tritheme(ct):
    return norm(chiffre_tritheme.dechiffre_de_tritheme(ct, 3))

def solve_gs8(ct):
    return norm(GS8_Braille.gs8_decode(ct))


def solve_otan(ct):

    return norm(otan.decode_from_phonetic(ct))

def solve_shankar(ct):
    return norm(shankar.shankar_decrypt(ct))

def solve_prime(ct):
    return norm(prime.prime_decode(ct))

def solve_wabun(ct):
    return norm(wabun.decode_wabun(ct))

# ───── tiny Brain‑fuck runner for Spoon ───── #
def run_bf(code: str) -> str:
    tape, ptr, pc, out = [0]*30000, 0, 0, []
    # jump table
    jmp, st = {}, []
    for i, c in enumerate(code):
        if c == '[': st.append(i)
        elif c == ']':
            j = st.pop(); jmp[i] = j; jmp[j] = i
    while pc < len(code):
        c = code[pc]
        if   c == '>': ptr += 1
        elif c == '<': ptr -= 1
        elif c == '+': tape[ptr] = (tape[ptr]+1) & 0xff
        elif c == '-': tape[ptr] = (tape[ptr]-1) & 0xff
        elif c == '.': out.append(chr(tape[ptr]))
        elif c == '[' and tape[ptr]==0: pc = jmp[pc]
        elif c == ']' and tape[ptr]!=0: pc = jmp[pc]
        pc += 1
    return ''.join(out)

def solve_spoon(ct):
    decoded = spoon.spoon_decode(ct)
    if all(ch not in '><+-.,[]' for ch in decoded):
        return norm(decoded)
    return norm(run_bf(decoded))

# ─────────── hint → solver map ──────────── #
SOLVERS = {
    'encoded as pairs of alternating tones'               : solve_bibi,
    'mirror it, then add a touch of classical latin': solve_charabia,
    'shifting letters in a cascade of threes'                 : solve_tritheme,
    'braille encoded in 8-dot cells'             : solve_gs8,
    'spelled out in the nato phonetic alphabet'      : solve_otan,
    'where elites get numeric'          : solve_leet,
    'an eastern twist on the abcs'          : solve_shankar,
    'the very first of the indivisible' : solve_prime,
    'morse code with a japanese accent'       : solve_wabun,
    'brainfuck, but with spoons instead of forks'         : solve_spoon,
}

# ───────────────────── main ───────────────────── #
def main():
    io = remote(HOST, PORT)
    while True:
        line = io.recvline(timeout=10)
        if line and line.lower().startswith(b'hint:'):
            io.unrecv(line)   
            break
    turn = 1
    while True:
        try:
            hint = cipher = None
            while cipher is None:
                ln = io.recvline(timeout=5).decode('utf-8', 'ignore').strip()
                if not ln: continue
                if ln.startswith('hint:'):
                    hint = ln[5:].strip().lower()

                elif ln.startswith('cipher:'):
                    cipher = ln[7:].strip()
                else:
                    print(ln)
            fn = SOLVERS.get(hint)
            if fn is None:
                log.error(f'Unknown hint {hint}')
                break

            ans = fn(cipher)
            log.info(f"[#{turn}] {hint!r} → {ans!r}")
            io.sendline(ans.encode())
            turn += 1
        except EOFError:
            log.info('Connection closed – maybe flag sent.')
            break
        except Exception as e:
            log.error(f'Error at round {turn}: {e}')
            break

    try:
        rest = io.recvall(timeout=2).decode()
        if rest: print(rest)
    except: pass
    io.close()

if __name__ == '__main__':
    main()

# PTITCTF{running_on_the_server_is_so_crazy}
```
