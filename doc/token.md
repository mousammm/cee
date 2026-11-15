# C89 Lexical Tokens Specification

A reference guide to the five lexical token categories defined by the ANSI C (C89) standard.

---

## 1. Keywords (32 Fixed Words)

Keywords are reserved words with predefined meanings in C89 and cannot be used as user-defined identifiers.

### Data Types & Qualifiers (12)
```c
char      int       float     double    void
signed    unsigned  short     long
struct    enum      union
```

### Storage Classes & Type Modifiers (6)
```c
auto      const     extern    register  static    volatile
```

### Control Flow (12)
```c
break     case      continue  default   do        else
for       goto      if        return    switch    while
```

### Operators (1)
```c
sizeof
```

### Type Definitions (1)
```c
typedef
```

---

## 2. Identifiers (User-Defined Names)

Identifiers are custom names created by the programmer for variables, functions, structs, unions, enums, or labels (e.g., `main`, `counter`, `_buffer`).

* **Naming Rules:** Must start with a letter (`a–z`, `A–Z`) or an underscore (`_`), followed by any combination of letters (`a–z`, `A–Z`), digits (`0–9`), or underscores (`_`).
* **Lexer Behavior:** The lexer scans the entire alphanumeric word as a candidate identifier first, then performs a lookup against the 32 reserved keywords. For example, if the word matches `while`, it emits `TOK_WHILE`; otherwise, it emits `TOK_IDENT`.

---

## 3. Literals / Constants (Hardcoded Values)

Literals represent raw, fixed values written directly into the source code. C89 defines four distinct types:

| Literal Type | Description | Examples |
| :--- | :--- | :--- |
| **Integer Constants** | Whole numbers written in decimal, octal (leading `0`), or hexadecimal (`0x`/`0X`), optionally suffixed with `U` (unsigned) or `L` (long). | `42`, `052`, `0x2A`, `100UL` |
| **Floating-Point Constants** | Decimal numbers containing a decimal point, an exponent (`e`/`E`), or both, optionally suffixed with `f`/`F` or `l`/`L`. | `3.14`, `1e-5`, `2.5f` |
| **Character Constants** | A single character or escape sequence enclosed in single quotes. | `'A'`, `'\n'`, `'\0'` |
| **String Literals** | A sequence of characters enclosed in double quotes (implicitly null-terminated). | `"Hello, world!\n"` |

---

## 4. Operators (Math, Logic, and Memory)

Operators perform operations on variables and values. Because several operators share leading characters (such as `<`, `<=`, `<<`, and `<<=`), the lexer uses **1-to-2 characters of lookahead** to consume the longest valid token—a rule known as **Maximal Munch**.

* **Arithmetic & Bitwise:**
  `+`, `-`, `*`, `/`, `%`, `++`, `--`, `&`, `|`, `^`, `~`, `<<`, `>>`
* **Comparison & Logical:**
  `==`, `!=`, `<`, `>`, `<=`, `>=`, `&&`, `||`, `!`
* **Assignment:**
  `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=`, `^=`, `<<=`, `>>=`
* **Memory, Member Access & Misc:**
  `&` (address-of), `*` (dereference), `.` (direct member), `->` (pointer member), `? :` (ternary conditional), `,` (comma operator)

---

## 5. Punctuators / Delimiters (Structural Glue)

Punctuators organize code into blocks, parameter lists, and statements so the parser can determine where expressions begin and end.

* **Brackets & Braces:**
  `(` `)` (parentheses), `{` `}` (curly braces), `[` `]` (square brackets)
* **Statement & List Separators:**
  * `;` — Statement terminator
  * `,` — Argument and declaration list separator
  * `:` — Label and `switch`/`case` delimiter
  * `...` — Ellipsis for variadic functions (e.g., `int printf(const char *fmt, ...)`)
