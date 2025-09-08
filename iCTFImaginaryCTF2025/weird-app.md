<img width="796" height="305" alt="image" src="https://github.com/user-attachments/assets/bf158db4-232d-4756-b582-cfe90b96fa5d" />  

Download and open it with Jadx, we need to lookup where is the **main** fucntion locate to read the code.   
**android.xxx or kotlin.xxx** is lib folder, so no need to check here, also with **com.google**

<img width="459" height="406" alt="image" src="https://github.com/user-attachments/assets/30fe9def-35fe-4ed9-8d47-60824e5493f0" />  

I see `MainActivity` function but the `MainActivityKt` one did the thing.  

Extract the code and we can see some important thing:  
First, transform Flag funcion:  
```java
    public static final String transformFlag(String flag) {
        Intrinsics.checkNotNullParameter(flag, "flag");
        String res = "";
        int length = flag.length();
        for (int i = 0; i < length; i++) {
            int length2 = "abcdefghijklmnopqrstuvwxyz".length();
            for (int c = 0; c < length2; c++) {
                if ("abcdefghijklmnopqrstuvwxyz".charAt(c) == flag.charAt(i)) {
                    int ind = c + i;
                    res = res + "abcdefghijklmnopqrstuvwxyz".charAt(ind % "abcdefghijklmnopqrstuvwxyz".length());
                }
            }
            int length3 = "0123456789".length();
            for (int c2 = 0; c2 < length3; c2++) {
                if ("0123456789".charAt(c2) == flag.charAt(i)) {
                    int ind2 = (i * 2) + c2;
                    res = res + "0123456789".charAt(ind2 % "0123456789".length());
                }
            }
            int length4 = "!@#$%^&*()_+{}[]|".length();
            for (int c3 = 0; c3 < length4; c3++) {
                if ("!@#$%^&*()_+{}[]|".charAt(c3) == flag.charAt(i)) {
                    int ind3 = (i * i) + c3;
                    res = res + "!@#$%^&*()_+{}[]|".charAt(ind3 % "!@#$%^&*()_+{}[]|".length());
                }
            }
        }
        return res;
    }

```

Leaked output flag from `Greating` function : 
```java
TextKt.m2712Text4IGK_g("Transformed flag: idvi+1{s6e3{)arg2zv[moqa905+", modifier3, 0L, 0L, (FontStyle) null, (FontWeight) null, (FontFamily) null, 0L, (TextDecoration) null, (TextAlign) null, 0L, 0, false, 0, 0, (Function1<? super TextLayoutResult, Unit>) null, (TextStyle) null, $composer2, i3, 0, 131068);
```

Let's rev it !  

With character: 
```java
int ind = c + i;
res = res + "abcdefghijklmnopqrstuvwxyz".charAt(ind % "abcdefghijklmnopqrstuvwxyz".length());

// Rev 
in_index = (out_index - i) mod 26
```

With number:
```java
int ind2 = (i * 2) + c2;
res = res + "0123456789".charAt(ind2 % "0123456789".length());

// Rev
in_index = (out_index - i*2) mod 10
```

With special char:
```java
int ind3 = (i * i) + c3;
res = res + "!@#$%^&*()_+{}[]|".charAt(ind3 % "!@#$%^&*()_+{}[]|".length());

// Rev
in_index = (out_index - i*i) mod (symbols.length())
```

Then you have the flag: 
> Flag: ictf{1_l0v3_@ndr0id_stud103}

Peace!








