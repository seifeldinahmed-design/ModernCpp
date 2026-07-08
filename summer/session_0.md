# Session 0 — Getting Started with C++

---

## Learning Objectives

By the end of this session a student should be able to:

1. Explain what C++ is, where it came from, and why it is still used.
2. Describe how source code becomes a running program (preprocess → compile → assemble → link → load).
3. Install `g++` and compile/run a program from the terminal.
4. Read and write a basic C++ program and explain every line of it.
5. Identify the **tokens** of C++: keywords, identifiers, literals, operators, punctuation.
6. Declare and use **variables**, understand their **scope**, and pick correct **data types**.



---

# 1. What is C++?

**C++** is a general-purpose, compiled programming language created by **Bjarne Stroustrup**
at Bell Labs starting in **1979** (originally called "C with Classes"). It runs on virtually
every platform — Windows, macOS, Linux, embedded devices, and more.

C++ began as an extension of the **C** language that added **object-oriented programming
(OOP)**. A useful one-liner:

> *C++ is (almost) a superset of C, with object-oriented and generic-programming features
> added on top.*

That "superset" relationship matters: most valid C programs are also valid C++ programs, so
knowledge transfers both ways.

### Where C++ sits among languages

| | Interpreted (e.g. Python, JS) | C++ | Assembly |
|---|---|---|---|
| Speed | Slower | **Fast** | Fastest |
| Control over memory/hardware | Little | **A lot** | Total |
| Ease of writing | Easiest | Medium | Hardest |

C++ is often called a **middle-level** language: high-level enough to write large applications
comfortably, low-level enough to control memory and hardware directly.

## 1.1 Why Learn C++?

- **Close to the hardware.** You control memory layout and management directly, which gives
  high performance and deep understanding of how computers actually work.
- **Teaches the fundamentals.** Writing C++ forces you to understand the difference between the
  *compiler*, *linker*, and *loader*; between *declaration* and *definition*; between *stack*
  and *heap*; and how data types map to memory. Those concepts carry over to every other
  language.
- **Real OOP from the ground up.** You learn objects, classes, inheritance, and polymorphism —
  and later, *how* they work under the hood (virtual tables, dynamic dispatch).
- **Evergreen and in demand.** Decades old and still one of the most widely used languages in
  systems and application programming. Strong, well-paid job market.

> "To learn any programming language — not just C++ — you need to code, and code, and code
> again until it becomes second nature."

## 1.2 Where C++ Is Used

| Domain | Examples |
|--------|----------|
| Operating systems | Core parts of Windows, macOS, Linux |
| Browsers | Chrome and Firefox engines |
| Databases | MySQL, MongoDB |
| Games & engines | Unreal Engine, most AAA game engines |
| Other languages' runtimes | The reference interpreters for languages like Python and Java are written in C/C++ |
| Scientific / high-performance computing | Simulations, financial modeling |
| Embedded & real-time | MRI machines, cars, IoT devices, CAD/CAM |

## 1.3 Careers That Use C++

Software Engineer · Game Developer · Systems Programmer · Embedded Systems Developer ·
Robotics Engineer · Graphics Programmer · Database Engineer · High-Frequency Trading Developer

## 1.4 Strengths and Trade-offs

**Strengths**

- **Performance** — compiled to native machine code; among the fastest languages.
- **Rich Standard Library (STL)** — ready-made containers (`vector`, `map`, …), algorithms,
  and iterators.
- **Full OOP support** — classes, encapsulation, inheritance, polymorphism, abstraction.
- **Portability** — the same source compiles on any platform with a standard-compliant compiler.
- **Huge community** — decades of libraries, books, and Q&A (Stack Overflow, GitHub, …).

**Trade-offs (be honest with students)**

- **Easy to make subtle mistakes** — direct memory access means bugs like dangling pointers and
  buffer overflows are possible; the compiler won't always save you.
- **Verbose** — more boilerplate than Python or Go.
- **Steep learning curve** — many features and rules; the payoff is deep understanding.

---

# 2. How C++ Code Becomes a Program

This is the section the rest of the course quietly depends on. Spend real time here — almost
every confusing error message a beginner sees maps to one of these stages.

C++ is a **compiled** language. Your human-readable source is translated **ahead of time** into
**machine code** (raw CPU instructions) and saved as an executable file. Running the program
just runs that machine code — the compiler is no longer involved. (Contrast with Python, where
an interpreter reads and executes your source every time you run it.)

## 2.1 The Build Pipeline

```
  hello.cpp
     │
     ▼
┌──────────────┐   Handles all #directives: pastes in #include files,
│ Preprocessor │   expands #define macros, strips comments.
└──────────────┘   Output: pure C++ with no # lines (a "translation unit").
     │
     ▼
┌──────────────┐   Translates C++ into assembly for your CPU.
│  Compiler    │   Type checking happens here. Most errors are caught here.
└──────────────┘   Output: assembly (.s)
     │
     ▼
┌──────────────┐   Turns assembly into machine code.
│  Assembler   │   Output: an object file (.o) — machine code, but NOT yet runnable.
└──────────────┘   (Calls like std::cout are still unresolved references.)
     │
     ▼
┌──────────────┐   Combines your .o file(s) with the C++ standard library and
│  Linker      │   resolves every referenced symbol into one executable.
└──────────────┘   Output: an executable (a.out)
     │
     ▼
┌──────────────┐   The OS loads the executable into memory, sets up the
│  Loader (OS) │   stack/heap, and jumps to main(). Your program now runs.
└──────────────┘
```

### Seeing each stage yourself

`g++` normally runs all stages at once, but you can stop after any one of them. Run these live —
they make the abstract pipeline tangible:

```bash
g++ -E hello.cpp -o hello.ii   # 1. Preprocess only  → open it; note <iostream> got pasted in
g++ -S hello.cpp -o hello.s    # 2. Compile to assembly → human-readable CPU instructions
g++ -c hello.cpp -o hello.o    # 3. Assemble to object file → binary, not runnable
g++ hello.cpp -o hello         # 4. Everything: preprocess + compile + assemble + link
```

## 2.2 Which Stage Produced My Error?

This single table saves students hours of confusion all semester:

| Stage | Typical error message | Cause |
|-------|-----------------------|-------|
| **Preprocessor** | `fatal error: xyz.h: No such file or directory` | Bad `#include` / missing header |
| **Compiler** | `expected ';' before ...`, `'x' was not declared in this scope`, type mismatches | Syntax or type error in your code |
| **Linker** | `undefined reference to 'foo'`, `multiple definition of 'bar'` | A function was *declared* but never *defined*, or defined twice |
| **Loader / Runtime** | `Segmentation fault`, wrong output, crash | Logic/memory bug — code compiled fine but behaves wrong |

---

# 3. Setting Up the Toolchain

On most Linux distributions the C++ compiler is **`g++`**, part of the **GNU Compiler
Collection (GCC)**.

## 3.1 Install on Ubuntu / Debian

Install just the C++ compiler:

```bash
sudo apt update
sudo apt install g++
```

Or install the full set of development tools (recommended):

```bash
sudo apt update
sudo apt install build-essential
```

`build-essential` installs:

- `gcc` — the C compiler
- `g++` — the C++ compiler
- `make` — build automation tool
- standard development libraries and headers

## 3.2 Verify the Installation

```bash
g++ --version
```

You should see the compiler version printed. If you get "command not found," the install
didn't complete.

## 3.3 Common `g++` Flags (Reference)

Students won't need all of these on day one, but keep this table handy — you'll reach for it all
semester. The four in **bold** are the ones to teach today.

| Flag | Purpose |
|------|---------|
| **`-o <name>`** | Name the output file (default is `a.out`) |
| **`-std=c++20`** | Select the C++ standard (e.g. `c++11`, `c++17`, `c++20`) |
| **`-Wall`** | Enable common warnings (use this always) |
| **`-Wextra`** | Enable extra warnings |
| `-Werror` | Treat warnings as errors |
| `-O0`–`-O3`, `-Os`, `-Ofast` | Optimization level (`-O0` = none, `-O2` = typical release) |
| `-g` | Generate debug symbols (for `gdb`) |
| `-I <dir>` | Add a header search path |
| `-L <dir>` | Add a library search path |
| `-l <name>` | Link against a library |
| `-D <macro>` | Define a preprocessor macro from the command line |
| `-U <macro>` | Undefine a macro |
| `-E` | Preprocess only |
| `-S` | Compile to assembly only |
| `-c` | Compile & assemble to an object file only (no linking) |
| `-shared` | Build a shared library |
| `-fPIC` | Generate position-independent code (for shared libs) |
| `-static` | Statically link libraries |
| `-pthread` | Enable POSIX thread support |
| `-fsanitize=address` | Detect memory errors at runtime |
| `-fsanitize=undefined` | Detect undefined behavior at runtime |
| `-v` | Show detailed compilation steps |

```bash
g++ -std=c++20 -Wall -Wextra hello.cpp -o hello
```
Most beginner bugs (uninitialized variables, unused results, comparison mistakes) show up as
warnings. `-Wall` is not "all warnings" despite the name, but it's the right default.

> **No Linux box?** An online compiler (e.g. an online C++ IDE / GDB online) is fine for
> quick experiments and works in any browser. But get students onto a local `g++` early — the
> terminal workflow is part of learning C++.

---

# 4. Your First Program: "Hello, World!"

```cpp
// hello.cpp — our first C++ program
#include <iostream>
using namespace std;

// main() is where program execution begins.
int main() {
    cout << "Hello, World!" << endl;   // print text, then a newline
    return 0;
}
```

**Output**

```
Hello, World!
```

## 4.1 Compile and Run It

```bash
$ g++ hello.cpp -o hello
$ ./hello
Hello, World!
```

Step by step:

1. Save the code in a file named `hello.cpp`.
2. Open a terminal in the directory containing that file.
3. Compile: `g++ hello.cpp -o hello` — if there are no errors, you get an executable named
   `hello`. (Omit `-o hello` and you get the default name `a.out`.)
4. Run it: `./hello` (the `./` tells the shell "run the file in *this* directory").

## 4.2 Line-by-Line Breakdown

Walk through each line — this tiny program contains most of the structural ideas of C++.

### `#include <iostream>` — a preprocessor directive

`#include` is handled by the **preprocessor** (stage 1 from §2). It pastes the contents of a
**header file** into your program. `<iostream>` ("input/output stream") declares the tools for
console I/O — including `cout` and `cin`. Without it, the compiler wouldn't know what `cout` is.

### `using namespace std;` — a namespace directive

Everything in the C++ standard library lives inside the **`std`** namespace. Its full name is
`std::cout`, `std::endl`, etc. This line lets you drop the `std::` prefix and just write `cout`.

> More on namespaces — and why professionals often *avoid* this line — in §5.4.

### `int main() { ... }` — the entry point

Every C++ program **must** have exactly one `main()` function. Execution starts here, no matter
where in the file `main` is written. The `int` means `main` returns an integer to the operating
system.

### `cout << "Hello, World!" << endl;` — output

- `cout` is the **standard output stream** (the console).
- `<<` is the **stream insertion operator** — read it as "send this into the stream."
- `"Hello, World!"` is a **string literal**.
- `endl` inserts a newline and flushes the output buffer. (`"\n"` also inserts a newline; more
  in §6.3.)
- You can chain insertions: `cout << a << b << c;`.

### `return 0;` — exit status

`main` returns `0` to signal **success** to the operating system. A non-zero value conventionally
signals an error. This is how other programs and shell scripts know whether your program
succeeded.

## 4.3 Reading Input with `cin`

Output alone gets boring fast. `cin` (the **standard input stream**) reads what the user types,
using the **extraction operator** `>>`:

```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    cout << "Enter your age: ";
    cin >> age;                        // read a number from the keyboard into `age`
    cout << "Next year you will be " << age + 1 << endl;
    return 0;
}
```

**Sample run**

```
Enter your age: 20
Next year you will be 21
```

---

# 5. Program Structure & Basic Syntax

## 5.1 The Three Parts of a Simple Program

```cpp
#include <iostream>     // 1. Header inclusion — bring in library declarations
using namespace std;    // 2. Namespace     — so we can drop the std:: prefix

int main() {            // 3. main()        — the entry point; program logic goes here
    // ... your code ...
    return 0;
}
```

## 5.2 Statements, Semicolons, and Blocks

A **statement** is a single instruction. In C++ every statement ends with a **semicolon `;`** —
the statement terminator.

```cpp
x = y;
y = y + 1;
add(x, y);
```

C++ **ignores line breaks** — the semicolon, not the newline, ends a statement. So these are
identical to the compiler:

```cpp
x = y; y = y + 1; add(x, y);          // all on one line — same meaning
```

(Write one statement per line anyway — for humans, not the compiler.)

A **block** is a group of statements wrapped in braces `{ }`. Blocks define where variables live
(their *scope*, §7.2) and form the bodies of functions, loops, and `if` statements.

```cpp
{
    cout << "Inside a block" << endl;
    return 0;
}
```

## 5.3 Whitespace

**Whitespace** = spaces, tabs, newlines, and comments. C++ uses it only to separate tokens;
beyond that it's ignored. A blank line does nothing.

```cpp
int age;                              // the space between `int` and `age` is REQUIRED
fruit = apples + oranges;             // spaces around `=` and `+` are OPTIONAL (readability)
```

Whitespace is *required* where two words would otherwise merge (`int`+`age` → `intage`), and
*optional* around operators and punctuation. Use it generously to keep code readable.

## 5.4 Namespaces: `using namespace std;` vs `std::`

A **namespace** groups related names to prevent collisions. If two libraries both define a
`sort` function, namespaces (`libA::sort`, `libB::sort`) keep them apart.

The standard library lives in the `std` namespace. You have two styles:

**Style A — `using namespace std;` (convenient for learning):**

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello" << endl;
    return 0;
}
```

**Style B — explicit `std::` prefix (preferred in real projects):**

```cpp
#include <iostream>
#include <string>

int main() {
    std::string greeting = "Hello, learner!";
    std::cout << greeting << std::endl;
    return 0;
}
```

**When to prefer explicit `std::`:**

- **Large projects / multiple libraries** — avoids ambiguous name clashes.
- **Library / header code** — never dump `std` into a header; it pollutes the global namespace
  of everyone who includes it.
- **Readability** — `std::` makes it obvious where a name comes from.

## 5.5 Comments

Comments are notes for humans; the compiler ignores them completely.

**Single-line** — starts with `//`, runs to the end of the line:

```cpp
// This whole line is a comment
cout << "Hi";   // ...and so is everything after the // here
```

**Multi-line (block)** — everything between `/*` and `*/`:

```cpp
/* This is a comment
   that spans
   several lines. */
```

**Commenting mid-statement** — a block comment can sit inside a line:

```cpp
cout << "This line" /* injected note */ << " has a comment" << endl;
// Output: This line has a comment
```

### Good uses of comments

- Explain **why**, not **what** (the code already says *what*).
- Temporarily **disable code** while debugging.
- Leave short hints about tricky logic.
- Generate documentation (e.g. Doxygen).

```cpp
/* outer  /* inner */  this text is now OUTSIDE the comment → compiler error */
```

To comment out a region that already contains block comments, use `//` on each line (or, later,
`#if 0 ... #endif`).

---

# 6. Tokens — The Building Blocks of C++

**Tokens** are the smallest meaningful units the compiler recognizes — like words in a sentence.
Every C++ program is just a stream of tokens. There are five kinds:

1. **Keywords** — reserved words with fixed meaning
2. **Identifiers** — names you invent
3. **Literals / Constants** — fixed values written directly in code
4. **Operators** — symbols that perform operations
5. **Punctuation** — structural symbols (`;`, `{}`, `()`, …)

## 6.1 Keywords

**Keywords** are reserved words with a built-in meaning; you **cannot** use them as names for
your own variables, functions, or classes. Grouped by role:

| Category | Keywords |
|----------|----------|
| **Basic data types** | `int`, `char`, `float`, `double`, `bool`, `void`, `wchar_t` |
| **Type modifiers** | `signed`, `unsigned`, `short`, `long`, `const`, `volatile` |
| **Control flow** | `if`, `else`, `switch`, `case`, `default`, `for`, `while`, `do`, `break`, `continue`, `return`, `goto` |
| **Storage classes** | `auto`, `static`, `extern`, `register`*, `mutable` |
| **OOP** | `class`, `struct`, `union`, `enum`, `public`, `private`, `protected`, `virtual`, `this`, `friend`, `explicit`, `operator` |
| **Memory** | `new`, `delete`, `sizeof` |
| **Namespaces** | `namespace`, `using` |
| **Type casts** | `static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast`, `typeid` |
| **Exceptions** | `try`, `catch`, `throw` |
| **Other** | `typedef`, `template`, `inline`, `true`, `false` |

\* `register` still exists but has been **deprecated since C++17** — don't teach it as current
practice.

> C++ has more keywords than C; the extra ones support OOP and other C++-only features.

### Keywords vs. Identifiers

| Keywords (reserved by the language) | Identifiers (names *you* choose) |
|---|---|
| `int`, `float`, `while`, `class`, `return`, `public` | `myVariable`, `calculateSum`, `Person`, `_temp` |

## 6.2 Identifiers

An **identifier** is a name you give to a variable, function, class, array, etc.

### Rules (enforced by the compiler)

- Must **start with a letter** (`A–Z`, `a–z`) **or an underscore `_`** — **never a digit**.
- After the first character: letters, digits (`0–9`), and underscores only.
- **Case-sensitive**: `myVar` and `myvar` are two different names.
- **Cannot** be a keyword (`int`, `return`, `while`, …).
- No spaces, and no punctuation like `@`, `$`, `%`, `-`.

### Conventions (style, not enforced — but expected)

- Use **meaningful names**: `totalCount`, `calculateArea` — not `x1`, `tmp2`.
- Pick a style and stay consistent: `camelCase` or `snake_case`.
- Keep names reasonably short but descriptive.

```cpp
// Valid identifiers
int age;
double salary;
char initial_alpha;
const int MAX_SIZE = 100;    // constants often ALL_CAPS
int studentAge;              // camelCase
int student_age;             // snake_case

// INVALID identifiers — each breaks a rule
int 2ndValue;      // starts with a digit
int first-name;    // contains a hyphen
int @username;     // starts with a special character
int my variable;   // contains a space
int float;         // uses a reserved keyword
```

## 6.3 Literals (Constants)

A **literal** is a fixed value written directly in the source code. Its value can't change.
C++ has integer, floating-point, character, string, and boolean literals.

### Integer literals

Can be written in different bases using a prefix:

```cpp
85        // decimal (no prefix)
0213      // octal        (leading 0)
0x4b      // hexadecimal  (leading 0x or 0X)
0b1010    // binary       (leading 0b, since C++14)
```

And suffixed with `U` (unsigned) and/or `L` (long):

```cpp
30        // int
30u       // unsigned int
30L       // long
30uL      // unsigned long
```

```cpp
212       // Legal
215u      // Legal
0xFeeL    // Legal (hex, long)
078       // ILLEGAL: 8 is not a valid octal digit
032UU     // ILLEGAL: a suffix cannot be repeated
```

### Floating-point literals

Written in decimal or scientific/exponential form (`e`/`E` introduces the exponent):

```cpp
3.14159        // Legal
314159E-5L     // Legal (scientific, long double)
510E           // ILLEGAL: incomplete exponent
210f           // ILLEGAL: no decimal point or exponent
.e55           // ILLEGAL: no integer or fraction part
```

### Boolean literals

Just two: `true` and `false` (both are keywords).

```cpp
bool isReady = true;
bool isDone  = false;
```

### Character literals

A single character in **single quotes**: `'A'`, `'7'`, `'$'`. A leading `L` makes it a wide
character: `L'x'` (stored in `wchar_t`).

### Escape sequences

Some characters are written with a backslash `\`:

| Escape | Meaning |
|:------:|---------|
| `\n` | Newline |
| `\t` | Horizontal tab |
| `\\` | Backslash |
| `\'` | Single quote |
| `\"` | Double quote |
| `\0` | Null character |
| `\r` | Carriage return |
| `\a` | Alert (bell) |
| `\b` | Backspace |
| `\v` | Vertical tab |
| `\f` | Form feed |

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello\tWorld\n";          // tab between the words, then newline
    cout << "She said \"hi\"\n";       // embedded double quotes
    return 0;
}
```

**Output**

```
Hello	World
She said "hi"
```

### String literals

Text in **double quotes**: `"hello"`. A long string can be split across lines by writing
adjacent string literals, which the compiler joins:

```cpp
"hello, "  "d"  "ear"                  // becomes "hello, dear"
```

## 6.4 Operators

An **operator** is a symbol that performs an operation on one or more values (operands).

### Arithmetic

| Op | Meaning | Example (`a=10, b=3`) |
|:--:|---------|-----------------------|
| `+` | Addition | `a + b` → 13 |
| `-` | Subtraction | `a - b` → 7 |
| `*` | Multiplication | `a * b` → 30 |
| `/` | Division | `a / b` → 3 (integer division!) |
| `%` | Modulus (remainder) | `a % b` → 1 |

### Increment / Decrement

| Op | Meaning |
|:--:|---------|
| `++` | Increase by 1 |
| `--` | Decrease by 1 |

`++x` (pre) increments then yields the new value; `x++` (post) yields the old value then
increments.

### Relational (comparison) — result is a `bool`

| Op | Meaning |
|:--:|---------|
| `==` | Equal to |
| `!=` | Not equal to |
| `>` | Greater than |
| `<` | Less than |
| `>=` | Greater than or equal |
| `<=` | Less than or equal |

### Logical — combine boolean expressions

| Op | Meaning |
|:--:|---------|
| `&&` | AND — true only if **both** sides are true |
| `\|\|` | OR — true if **either** side is true |
| `!` | NOT — flips true/false |

### Assignment

| Op | Meaning | `x += 5` is short for |
|:--:|---------|-----------------------|
| `=` | Assign | — |
| `+=` `-=` `*=` `/=` `%=` | Compound arithmetic assign | `x = x + 5` |
| `<<=` `>>=` `&=` `^=` `\|=` | Compound bitwise assign | `x = x & 5` etc. |

### Bitwise — operate on individual bits

| Op | Meaning |
|:--:|---------|
| `&` | AND |
| `\|` | OR |
| `^` | XOR |
| `~` | NOT (one's complement) |
| `<<` | Left shift |
| `>>` | Right shift |

### Miscellaneous

| Op | Meaning |
|:--:|---------|
| `sizeof(x)` | Size of a type/variable in bytes |
| `&x` | Address of a variable |
| `*p` | Dereference a pointer (value it points to) |
| `? :` | Ternary conditional: `cond ? a : b` |
| `,` | Comma operator |

### Operators in action

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 3;

    cout << "a + b  = " << a + b  << endl;   // 13
    cout << "a / b  = " << a / b  << endl;   // 3  (integer division)
    cout << "a % b  = " << a % b  << endl;   // 1  (remainder)
    cout << "a > b  = " << (a > b) << endl;  // 1  (true)
    cout << "a==b   = " << (a == b) << endl; // 0  (false)

    int max = (a > b) ? a : b;               // ternary
    cout << "max    = " << max << endl;      // 10
    return 0;
}
```

## 6.5 Punctuation

Punctuation tokens give the code its structure:

| Symbol | Purpose |
|--------|---------|
| `;` | End a statement |
| `,` | Separate items (variables, arguments) |
| `.` | Access a member of an object |
| `->` | Access a member through a pointer |
| `()` | Group expressions / call functions |
| `{}` | Define a block of code |
| `[]` | Array subscript |

## 6.6 Trigraphs (historical — skip unless asked)

Old C++ had three-character sequences like `??=` for `#`, meant for keyboards missing certain
symbols. **Trigraphs were removed in C++17** and should never be used. Mention only so students
recognize them if they see them in ancient code.

---

# 7. Variables

A **variable** is a named storage location in memory. Each variable has:

- a **name** (identifier),
- a **type** (which sets its size, layout, valid values, and allowed operations),
- a **value** stored at some memory address.

## 7.1 Declaration, Definition, and Initialization

These three words are used loosely in conversation but mean specific things — worth getting right
early.

```cpp
int x;              // DEFINITION: reserves memory for x (value is garbage until set)
int y = 5;          // DEFINITION + INITIALIZATION: reserve memory AND give it a value
x = 10;             // ASSIGNMENT: store a value into already-existing storage
extern int z;       // DECLARATION only: "z exists somewhere else" — no memory reserved here
```

- **Declaration** tells the compiler a name and its type exist (used across multiple files with
  `extern`). A variable can be declared many times.
- **Definition** actually allocates the storage. A variable must be defined **exactly once**.
- **Initialization** gives it a value *at the moment of definition*.

Modern C++ also supports brace initialization: `int y{5};` (safer — it rejects narrowing
conversions).

⚠️ **Common pitfall — uninitialized variables.** A local variable that you *define but don't
initialize* holds **garbage** (whatever was in that memory). Reading it is undefined behavior.

```cpp
int count;                 // garbage value!
cout << count;             // undefined — could print anything

int count2 = 0;            // ✅ always initialize
```

`-Wall` catches many of these. Teach "**declare and initialize together**" as a habit.

### Multiple declarations in one statement

You may declare several variables of the **same type** at once:

```cpp
int    i, j, k;                       // three ints
int    x = 10, y = 20, z = 30;        // declare + initialize each
int    a = b = c = 0;                 // chain-assign the same value to all three
char   grade = 'A';
double pi = 3.14159;
```

## 7.2 Variable Scope

**Scope** is the region of the program where a name is valid. There are two main kinds:

![C++ Variable Scopes](session_0.assets/cpp_variable_scope.jpg)

### Local variables

Declared **inside a function or block**. They exist only within that block, and are **not
initialized automatically** — you must set them.

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;   // local to main()
    int c = a + b;
    cout << c << endl;    // 30
    return 0;
}
```

### Global variables

Declared **outside all functions**, usually at the top of the file. Accessible from anywhere
after their declaration, and (unlike locals) **zero-initialized by default**.

```cpp
#include <iostream>
using namespace std;

int g;                    // global, automatically 0

int main() {
    int a = 10, b = 20;   // local
    g = a + b;
    cout << g << endl;    // 30
    return 0;
}
```

Default initialization for globals:

| Type | Default value |
|:----:|:-------------:|
| `int` | `0` |
| `char` | `'\0'` |
| `float` / `double` | `0` |
| pointer | `nullptr` |

### Shadowing and the scope resolution operator `::`

If a local and a global share a name, the **local wins** inside the function (it *shadows* the
global). Use the **scope resolution operator `::`** to reach the global:

```cpp
#include <iostream>
using namespace std;

int g = 20;               // global

int main() {
    int g = 10;           // local shadows the global
    cout << "Local  g: " << g   << endl;   // 10
    cout << "Global g: " << ::g << endl;   // 20  (::g reaches the global)
    return 0;
}
```

## 7.3 Lvalues and Rvalues

- An **lvalue** refers to a **memory location** — it can appear on the **left** side of `=`.
- An **rvalue** is a **temporary value** — it can only appear on the **right** side.

```cpp
int g = 20;               // OK: g is an lvalue, 20 is an rvalue
10 = 20;                  // ERROR: 10 is an rvalue — you can't assign to a literal
```

Rule of thumb: *variables* are lvalues; *literals and computed results* are rvalues.

---

# 8. Data Types

A variable's **type** tells the compiler how much memory to reserve and how to interpret the
bits stored there.

## 8.1 The Fundamental (Primitive) Types

| Type | Keyword | Stores |
|------|:-------:|--------|
| Boolean | `bool` | `true` / `false` |
| Character | `char` | a single character (1 byte) |
| Integer | `int` | whole numbers |
| Floating point | `float` | real numbers, single precision |
| Double floating point | `double` | real numbers, double precision |
| Wide character | `wchar_t` | a wide character |
| Valueless | `void` | "no type" (e.g. a function returning nothing) |

### Type modifiers

Several types can be adjusted with: `signed`, `unsigned`, `short`, `long`.

- `signed` / `unsigned` — allow negatives, or non-negatives only (doubles the positive range).
- `short` / `long` — use less / more memory.

### Sizes and ranges

Sizes are the typical values on a **64-bit Linux** system (the environment for this course).
**They are platform-dependent** — always confirm with `sizeof`.

| Type | Typical size | Typical range |
|------|:------------:|---------------|
| `char` | 1 byte | −128 to 127 (or 0 to 255 if unsigned) |
| `unsigned char` | 1 byte | 0 to 255 |
| `int` | 4 bytes | −2,147,483,648 to 2,147,483,647 |
| `unsigned int` | 4 bytes | 0 to 4,294,967,295 |
| `short int` | 2 bytes | −32,768 to 32,767 |
| `unsigned short int` | 2 bytes | 0 to 65,535 |
| `long int` | 8 bytes | ≈ −9.2×10¹⁸ to 9.2×10¹⁸ |
| `unsigned long int` | 8 bytes | 0 to ≈ 1.8×10¹⁹ |
| `long long int` | 8 bytes | −(2⁶³) to (2⁶³−1) |
| `float` | 4 bytes | ~7 significant digits |
| `double` | 8 bytes | ~15 significant digits |
| `long double` | 16 bytes | extended precision |
| `wchar_t` | 4 bytes (Linux) | one wide character |

⚠️ **Platform caveat:** On 64-bit **Windows**, `long int` is 4 bytes, not 8. This is exactly why
you use `sizeof` instead of memorizing numbers.

### Check sizes on *your* machine

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "char        : " << sizeof(char)        << " byte(s)"  << endl;
    cout << "int         : " << sizeof(int)         << " byte(s)"  << endl;
    cout << "short int   : " << sizeof(short int)   << " byte(s)"  << endl;
    cout << "long int    : " << sizeof(long int)    << " byte(s)"  << endl;
    cout << "float       : " << sizeof(float)       << " byte(s)"  << endl;
    cout << "double      : " << sizeof(double)      << " byte(s)"  << endl;
    cout << "wchar_t     : " << sizeof(wchar_t)     << " byte(s)"  << endl;
    return 0;
}
```

**Output (64-bit Linux)**

```
char        : 1 byte(s)
int         : 4 byte(s)
short int   : 2 byte(s)
long int    : 8 byte(s)
float       : 4 byte(s)
double      : 8 byte(s)
wchar_t     : 4 byte(s)
```

### Find exact limits with `<limits>`

Better than hard-coding ranges: ask the standard library.

```cpp
#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "int  min = " << numeric_limits<int>::min() << endl;
    cout << "int  max = " << numeric_limits<int>::max() << endl;
    cout << "uint max = " << numeric_limits<unsigned int>::max() << endl;
    cout << "long max = " << numeric_limits<long int>::max() << endl;
    return 0;
}
```

## 8.2 Numeric Types in Detail

### The integer family

| Type | Size | Use it for |
|------|:----:|------------|
| `short int` | 2 bytes | small numbers, saving memory |
| `int` | 4 bytes | the everyday default |
| `long int` | 8 bytes* | large numbers |
| `long long int` | 8 bytes | very large numbers |
| `unsigned ...` | same as above | when the value is never negative (counts, sizes) |

\* platform-dependent; see the caveat above.

```cpp
#include <iostream>
using namespace std;

int main() {
    int                    a = 16;
    short int              b = 3;
    long int               c = -32;
    long long int          d = 555;
    unsigned short int     e = 22;
    unsigned int           f = 33;
    unsigned long int      g = 888;
    unsigned long long int h = 444444;

    cout << "int                    size=" << sizeof(a) << "  value=" << a << endl;
    cout << "short int              size=" << sizeof(b) << "  value=" << b << endl;
    cout << "long int               size=" << sizeof(c) << "  value=" << c << endl;
    cout << "long long int          size=" << sizeof(d) << "  value=" << d << endl;
    cout << "unsigned short int     size=" << sizeof(e) << "  value=" << e << endl;
    cout << "unsigned int           size=" << sizeof(f) << "  value=" << f << endl;
    cout << "unsigned long int      size=" << sizeof(g) << "  value=" << g << endl;
    cout << "unsigned long long int size=" << sizeof(h) << "  value=" << h << endl;
    return 0;
}
```

**Output (64-bit Linux)**

```
int                    size=4  value=16
short int              size=2  value=3
long int               size=8  value=-32
long long int          size=8  value=555
unsigned short int     size=2  value=22
unsigned int           size=4  value=33
unsigned long int      size=8  value=888
unsigned long long int size=8  value=444444
```

> 📝 The original version of this table in many tutorials mismatches the `sizeof` argument with
> its label (printing `sizeof(unsigned int)` under the "short int" line, etc.). The version above
> is corrected — each line reports its own variable.

### Floating-point types

`float` (4 bytes, ~7 digits) and `double` (8 bytes, ~15 digits) store real numbers.
Prefer `double` unless memory is tight — it's more precise and usually just as fast.

```cpp
#include <iostream>
using namespace std;

int main() {
    float       k = 1.120123f;
    double      m = 1.34000123;
    long double n = 1.21312312421L;

    cout << "float       size=" << sizeof(k) << "  value=" << k << endl;
    cout << "double      size=" << sizeof(m) << "  value=" << m << endl;
    cout << "long double size=" << sizeof(n) << "  value=" << n << endl;
    return 0;
}
```

**Output**

```
float       size=4   value=1.12012
double      size=8   value=1.34
long double size=16  value=1.21312
```

⚠️ **Common pitfall — floats are approximate.** `0.1 + 0.2` is not exactly `0.3` in binary
floating point. Never compare floats with `==`; compare whether the difference is tiny instead.

## 8.3 The `char` Type and ASCII

`char` holds a **single character** in 1 byte. Internally it stores a **number** — the
character's **ASCII code** — so a `char` is really just a small integer.

```
'a' to 'z'  →  97–122
'A' to 'Z'  →  65–90
'0' to '9'  →  48–57
```

```cpp
#include <iostream>
using namespace std;

int main() {
    char letter = 'a';   // an alphabet
    char symbol = '&';   // a symbol
    char digit  = '1';   // the character '1' (NOT the number 1)
    cout << letter << " " << symbol << " " << digit << endl;
    return 0;
}
```

### char ↔ int conversion

Because a `char` *is* a number, you can convert freely between a character and its ASCII code:

```cpp
#include <iostream>
using namespace std;

int main() {
    char c = '$';
    int  a = 97;

    cout << "ASCII code of '$' : " << int(c)  << endl;   // 36
    cout << "Character for 97  : " << char(a) << endl;   // a
    return 0;
}
```

**Output**

```
ASCII code of '$' : 36
Character for 97  : a
```

⚠️ **Common pitfall:** `'1'` (the character, ASCII 49) is **not** the number `1`. `'1' + 1`
gives `50` (`'2'`), not `2`. This trips students up constantly in input parsing.

## 8.4 The `bool` Type

`bool` holds one of two values: **`true`** (printed as `1`) or **`false`** (printed as `0`).
It's the natural type for conditions and flags.

```cpp
#include <iostream>
using namespace std;

int main() {
    bool flag = true;

    int count = 0;
    while (flag) {              // loops while flag is true
        count++;
        if (count >= 3) flag = false;
    }
    cout << "count = " << count << ", flag = " << flag << endl;  // 3, 0

    if (flag) cout << "flag is true"  << endl;
    else      cout << "flag is false" << endl;                    // this runs
    return 0;
}
```

### bool ↔ number conversion

Any **non-zero** number converts to `true`; **zero** converts to `false`. And `true`/`false`
convert to `1`/`0` in arithmetic:

```cpp
#include <iostream>
using namespace std;

int main() {
    int   zero = 0, twelve = 12;
    float pi   = 3.14f;

    bool a = zero;    // 0        -> false
    bool b = twelve;  // non-zero -> true
    bool c = pi;      // non-zero -> true

    cout << a << " " << b << " " << c << endl;   // 0 1 1

    int sum = twelve + true + true;              // 12 + 1 + 1
    cout << "sum = " << sum << endl;             // 14
    return 0;
}
```

**Output**

```
0 1 1
sum = 14
```

> 📝 A widely copied version of this example is missing quotes around a string and won't compile
> (`cout << After adding ... << sum;`). The corrected version is above.

## 8.5 Type Conversion

**Implicit conversion** happens automatically when types mix (e.g. `int` → `double`).
**Explicit conversion (cast)** is when *you* force it by naming the target type:

```cpp
#include <iostream>
using namespace std;

int main() {
    double a = 6.551555;

    cout << "as int    : " << (int)a         << endl;   // 6   (fraction dropped)
    cout << "as float  : " << (float)a       << endl;   // 6.55156
    cout << "as double : " << a              << endl;   // 6.55155
    cout << "as long   : " << (long)a        << endl;   // 6
    return 0;
}
```

Two ways to write a cast:

```cpp
int x = (int)3.9;              // C-style cast          → 3
int y = static_cast<int>(3.9); // C++ style (preferred) → 3
```

💡 **Teaching tip:** Prefer `static_cast<T>(value)`. It's more explicit, easier to search for,
and the compiler checks it more carefully than the terse C-style `(T)value`.

## 8.6 Derived Types (Preview)

Built from the fundamental types. Full treatment comes in later sessions; here's a first look so
the vocabulary is familiar.

### Array — a fixed-size sequence of same-type elements, stored contiguously

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {1, 2, 3, 2, 1};
    for (int x : arr)              // range-based for loop
        cout << x << " ";
    cout << endl;                  // 1 2 3 2 1
    return 0;
}
```

### Pointer — stores the memory *address* of another variable

```cpp
#include <iostream>
using namespace std;

int main() {
    int  a = 20;
    int *p = &a;                   // p holds the address of a
    cout << "address of a: " << p  << endl;   // e.g. 0x7ffc...
    cout << "value at p   : " << *p << endl;  // 20 (dereference)
    return 0;
}
```

### Reference — an alias (second name) for an existing variable

```cpp
#include <iostream>
using namespace std;

int main() {
    int  c = 11;
    int &ref = c;                  // ref is another name for c
    ref = 121;                     // changing ref changes c
    cout << c << endl;             // 121
    return 0;
}
```

### Function — a named, reusable block of code

```cpp
#include <iostream>
using namespace std;

string parity(int n) {             // returns whether n is odd or even
    return (n % 2) ? "Odd" : "Even";
}

int main() {
    int a;
    cin >> a;
    cout << a << " is " << parity(a) << endl;
    return 0;
}
```

## 8.7 User-Defined Types (Preview)

Types *you* create. Covered in depth later — a first glimpse:

### `struct` — bundle related data together

```cpp
#include <iostream>
using namespace std;

struct Student {
    string name;
    int    grade;
};

int main() {
    Student s;
    s.name  = "Ali";
    s.grade = 10;
    cout << s.name << " scored " << s.grade << endl;
    return 0;
}
```

### `class` — data + behavior together (the heart of OOP)

```cpp
#include <iostream>
using namespace std;

class Numbers {
private:
    int a, b;                          // data members (hidden from outside)

public:
    void setValues(int x, int y) {     // member functions (behavior)
        a = x;
        b = y;
    }
    int addition() { return a + b; }
    void display() { cout << "a=" << a << ", b=" << b << endl; }
};

int main() {
    Numbers num;                       // create an object
    num.setValues(10, 20);
    num.display();                     // a=10, b=20
    cout << "Sum: " << num.addition() << endl;   // 30
    return 0;
}
```

- **`private`** members are usable only inside the class; **`public`** members are the interface
  the outside world uses. (There's also `protected`, for inheritance — a later topic.)

### `enum` — give names to a set of integer constants

```cpp
#include <iostream>
using namespace std;

enum Color { RED, GREEN, BLUE };       // RED=0, GREEN=1, BLUE=2 by default

int main() {
    Color c = GREEN;
    cout << "Color code: " << c << endl;   // 1
    return 0;
}
```

You can set explicit values; each unspecified name is one more than the previous:

```cpp
enum Color { RED, GREEN = 5, BLUE };   // RED=0, GREEN=5, BLUE=6
```

### `union` — several members sharing the **same** memory

All members overlap in memory, so writing one changes the others. Used for low-level
memory-saving tricks.

```cpp
#include <iostream>
using namespace std;

union Data {
    int   i;
    float f;
};

int main() {
    Data d;
    d.i = 2;
    cout << d.i << endl;   // 2
    d.f = 4.0f;            // now overwrites the same memory
    cout << d.i << endl;   // garbage — i and f shared storage
    return 0;
}
```

### `typedef` / `using` — create an alias for an existing type

```cpp
typedef int Feet;          // classic C style
using   Meters = int;      // modern C++ style (preferred)

Feet   distance = 100;     // just an int, but reads with intent
Meters height   = 2;
```

---

# 9. Constants

A **constant** is a value that must not change after it's set. Two ways to declare one:

## `const` keyword (preferred)

```cpp
#include <iostream>
using namespace std;

int main() {
    const int  LENGTH = 10;
    const int  WIDTH  = 5;
    const char NEWLINE = '\n';

    int area = LENGTH * WIDTH;
    cout << area << NEWLINE;      // 50
    return 0;
}
```

`const` is **type-safe** — the compiler knows `LENGTH` is an `int` and checks its use.

## `#define` preprocessor macro (older style)

```cpp
#include <iostream>
using namespace std;

#define LENGTH 10
#define WIDTH  5
#define NEWLINE '\n'

int main() {
    int area = LENGTH * WIDTH;   // preprocessor replaces LENGTH→10, WIDTH→5 before compiling
    cout << area << NEWLINE;      // 50
    return 0;
}
```

💡 **Teaching tip:** Prefer `const` (and `constexpr` later) over `#define`. Macros are blind
text substitution with no type checking and no scope — a frequent source of surprising bugs.

> **Convention:** name constants in `ALL_CAPS` so they stand out from variables.

---

# 10. Wrap-Up & Exercises

## Key Takeaways

- C++ is a fast, compiled, middle-level language — a superset of C with OOP.
- Source becomes a program through **preprocess → compile → assemble → link → load**; each
  stage produces its own kind of error.
- `g++ -Wall -Wextra file.cpp -o prog` then `./prog`.
- Every program has one `main()`; statements end in `;`; blocks use `{ }`.
- Programs are streams of **tokens**: keywords, identifiers, literals, operators, punctuation.
- **Variables** have a name, type, and scope; always initialize them.
- Pick the right **data type** for the data; use `sizeof` and `<limits>` rather than memorizing.

## Exercises

1. **Warm-up.** Write, compile, and run a program that prints your name and course on two
   separate lines (use `endl` or `\n`).
2. **Input & arithmetic.** Read two integers from the user and print their sum, difference,
   product, integer quotient, and remainder.
3. **Type sizes.** Print the size of `char`, `int`, `long`, `float`, and `double` on your
   machine. Compare with a neighbor on a different OS if possible.
4. **Integer division trap.** Read two integers and print their division result as a `double`
   (so `7 / 2` prints `3.5`, not `3`). *Hint: cast one operand.*
5. **char/ASCII.** Read a single character and print its ASCII code; then read a number 65–90
   and print the corresponding uppercase letter.
6. **Scope.** Write a program with a global and a local variable of the same name; print both the
   local value and the global value (using `::`).
7. **Debug it.** Fix this program so it compiles and prints `Total: 14`:
   ```cpp
   #include <iostream>
   using namespace std
   int main() {
       int x = 12
       cout << "Total: " << x + true + true << endl
       return 0
   }
   ```

---

---

# Appendix A — Hands-On Practice Apps

Two small, complete programs for each core topic. The source files live in the
**`session_0_apps/`** folder next to this guide, so students can compile and run them directly.
Every program below was compiled with `-std=c++20 -Wall -Wextra` (zero warnings) and run to
confirm its output.

Build any one of them like this (from inside `session_0_apps/`):

```bash
g++ -std=c++20 -Wall -Wextra 04_io_greeting.cpp -o greeting
./greeting
```

> In the "Sample run" boxes, text the **user types** is shown right after the prompt on the same
> line — that's exactly how it looks in a real terminal.

## Topic 4 — Input / Output

### App 1 · `04_io_greeting.cpp` — personalized greeting

Teaches: `getline` (reading a whole line), string variables, `cout`.

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    cout << "What is your name? ";
    getline(cin, name);              // reads a whole line (spaces allowed)
    cout << "Hello, " << name << "! Welcome to C++." << endl;
    return 0;
}
```

**Sample run**

```
What is your name? Ada Lovelace
Hello, Ada Lovelace! Welcome to C++.
```

### App 2 · `04_io_add_two.cpp` — add two numbers

Teaches: `cin >>`, integer variables, arithmetic in `cout`.

```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Enter first number: ";
    cin >> a;
    cout << "Enter second number: ";
    cin >> b;
    cout << a << " + " << b << " = " << a + b << endl;
    return 0;
}
```

**Sample run**

```
Enter first number: 7
Enter second number: 5
7 + 5 = 12
```

## Topic 5 — Program Structure, Comments & Namespaces

### App 1 · `05_structure_rectangle_area.cpp` — rectangle area & perimeter

Teaches: a clean 4-step structure (declare → input → compute → output) with comments.

```cpp
#include <iostream>
using namespace std;

int main() {
    // 1. Declare variables for the dimensions
    double width, height;

    // 2. Read the input from the user
    cout << "Enter width: ";
    cin >> width;
    cout << "Enter height: ";
    cin >> height;

    // 3. Compute the results
    double area      = width * height;
    double perimeter = 2 * (width + height);

    // 4. Display the results
    cout << "Area      = " << area      << endl;
    cout << "Perimeter = " << perimeter << endl;
    return 0;
}
```

**Sample run**

```
Enter width: 4
Enter height: 3
Area      = 12
Perimeter = 14
```

### App 2 · `05_structure_rectangle_area_std.cpp` — same program, explicit `std::`

Teaches: namespaces — the identical logic written **without** `using namespace std;`. Compare it
side-by-side with App 1 to see exactly what the `using` line saves you from typing.

```cpp
#include <iostream>

int main() {
    double width, height;

    std::cout << "Enter width: ";
    std::cin >> width;
    std::cout << "Enter height: ";
    std::cin >> height;

    double area = width * height;
    std::cout << "Area = " << area << std::endl;
    return 0;
}
```

**Sample run**

```
Enter width: 4
Enter height: 3
Area = 12
```

## Topic 6 — Tokens & Operators

### App 1 · `06_operators_calculator.cpp` — arithmetic operators

Teaches: `+ - * / %`, and the cast `(double)` that fixes integer division.

```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Enter two integers: ";
    cin >> a >> b;

    cout << a << " + " << b << " = " << a + b         << endl;   // addition
    cout << a << " - " << b << " = " << a - b         << endl;   // subtraction
    cout << a << " * " << b << " = " << a * b         << endl;   // multiplication
    cout << a << " / " << b << " = " << (double)a / b << endl;   // real division
    cout << a << " % " << b << " = " << a % b         << endl;   // remainder
    return 0;
}
```

**Sample run**

```
Enter two integers: 17 5
17 + 5 = 22
17 - 5 = 12
17 * 5 = 85
17 / 5 = 3.4
17 % 5 = 2
```

### App 2 · `06_operators_number_checks.cpp` — relational & logical operators

Teaches: `==`, `>`, `<=`, `&&`, and `boolalpha` (print `true`/`false` instead of `1`/`0`).

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter a whole number: ";
    cin >> n;

    bool isEven     = (n % 2 == 0);
    bool isPositive = (n > 0);
    bool inRange    = (n >= 1 && n <= 100);   // logical AND of two comparisons

    cout << boolalpha;                        // print true/false, not 1/0
    cout << n << " is even?        " << isEven     << endl;
    cout << n << " is positive?    " << isPositive << endl;
    cout << n << " is in [1,100]?  " << inRange    << endl;
    return 0;
}
```

**Sample run**

```
Enter a whole number: 42
42 is even?        true
42 is positive?    true
42 is in [1,100]?  true
```

## Topic 7 — Variables & Scope

### App 1 · `07_variables_swap.cpp` — swap two variables

Teaches: variables, assignment, and why you need a temporary to swap.

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5, b = 9;
    cout << "Before: a = " << a << ", b = " << b << endl;

    int temp = a;   // 1. save a's value
    a = b;          // 2. copy b into a
    b = temp;       // 3. copy the saved value into b

    cout << "After:  a = " << a << ", b = " << b << endl;
    return 0;
}
```

**Sample run**

```
Before: a = 5, b = 9
After:  a = 9, b = 5
```

### App 2 · `07_variables_scope_demo.cpp` — local vs global & `::`

Teaches: a local variable shadows a global one; `::` reaches the global.

```cpp
#include <iostream>
using namespace std;

int counter = 100;   // GLOBAL variable

int main() {
    int counter = 5; // LOCAL variable — shadows the global inside main()

    cout << "Local  counter : " << counter   << endl;   // uses the local
    cout << "Global counter : " << ::counter << endl;   // :: reaches the global
    return 0;
}
```

**Sample run**

```
Local  counter : 5
Global counter : 100
```

## Topic 8 — Data Types

### App 1 · `08_datatypes_profile_card.cpp` — five types together

Teaches: `string`, `int`, `double`, `char`, `bool` in one program.

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name     = "Sara";   // text
    int    age      = 21;       // whole number
    double gpa      = 3.75;     // real number
    char   grade    = 'A';      // single character
    bool   enrolled = true;     // true / false

    cout << boolalpha;          // show the bool as true/false
    cout << "Name     : " << name     << endl;
    cout << "Age      : " << age      << endl;
    cout << "GPA      : " << gpa      << endl;
    cout << "Grade    : " << grade    << endl;
    cout << "Enrolled : " << enrolled << endl;
    return 0;
}
```

**Sample run**

```
Name     : Sara
Age      : 21
GPA      : 3.75
Grade    : A
Enrolled : true
```

### App 2 · `08_datatypes_ascii_explorer.cpp` — char ↔ ASCII

Teaches: a `char` is a small integer; convert both ways with `int(...)` and `char(...)`.

```cpp
#include <iostream>
using namespace std;

int main() {
    char ch;
    cout << "Enter a character: ";
    cin >> ch;
    cout << "'" << ch << "' has ASCII code " << int(ch) << endl;   // char -> int

    int code;
    cout << "Enter an ASCII code (65-90): ";
    cin >> code;
    cout << "Code " << code << " is the character '" << char(code) << "'" << endl;  // int -> char
    return 0;
}
```

**Sample run**

```
Enter a character: A
'A' has ASCII code 65
Enter an ASCII code (65-90): 66
Code 66 is the character 'B'
```

## Topic 9 — Constants

### App 1 · `09_constants_circle.cpp` — `const` value

Teaches: `const` is read-only. Uncommenting a line that reassigns `PI` produces a **compiler
error** (`assignment of read-only variable 'PI'`) — a great live demo.

```cpp
#include <iostream>
using namespace std;

int main() {
    const double PI = 3.14159;   // constant — read-only

    double radius;
    cout << "Enter the radius: ";
    cin >> radius;

    cout << "Circumference = " << 2 * PI * radius     << endl;
    cout << "Area          = " << PI * radius * radius << endl;
    return 0;
}
```

**Sample run**

```
Enter the radius: 5
Circumference = 31.4159
Area          = 78.5397
```

### App 2 · `09_constants_seconds_in_day.cpp` — `#define` constants

Teaches: `#define` — the preprocessor substitutes each name with its value before compiling.

```cpp
#include <iostream>
using namespace std;

#define HOURS_PER_DAY    24
#define MINUTES_PER_HOUR 60
#define SECONDS_PER_MIN  60

int main() {
    int secondsPerDay = HOURS_PER_DAY * MINUTES_PER_HOUR * SECONDS_PER_MIN;
    cout << "There are " << secondsPerDay << " seconds in a day." << endl;
    return 0;
}
```

**Sample run**

```
There are 86400 seconds in a day.
```

---

### Build them all at once

Drop this `Makefile` into `session_0_apps/` and run `make` to build every app; `make clean`
removes the executables.

```make
# Makefile — build every practice app in this folder
CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

SRCS = $(wildcard *.cpp)
BINS = $(SRCS:.cpp=)

all: $(BINS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(BINS)
```



>A **namespace** in C++ is a feature that helps organize code and prevents **name conflicts** between identifiers (such as functions, classes, and variables).
>
>### Why namespaces are needed
>
>Imagine two libraries both define a function named `print()`:
>
>```
>// Library A
>void print() {
>    cout << "Library A";
>}
>
>// Library B
>void print() {
>    cout << "Library B";
>}
>```
>
>Without namespaces, the compiler wouldn't know which `print()` you mean.
>
>### Defining a namespace
>
>You create a namespace using the `namespace` keyword:
>
>```
>#include <iostream>
>using namespace std;
>
>namespace A {
>    void print() {
>        cout << "Hello from A\n";
>    }
>}
>
>namespace B {
>    void print() {
>        cout << "Hello from B\n";
>    }
>}
>
>int main() {
>    A::print();
>    B::print();
>
>    return 0;
>}
>```
>
>**Output:**
>
>```
>Hello from A
>Hello from B
>```
>
>The `::` operator is called the **scope resolution operator**. It tells the compiler which namespace to look in.
>
>### Using `using namespace`
>
>Instead of writing the namespace every time, you can bring its members into scope:
>
>```
>using namespace A;
>
>int main() {
>    print();   // Calls A::print()
>}
>```
>
>Be careful with `using namespace` in large projects because it can cause name conflicts.
>
>### Using a single member
>
>Instead of importing everything, you can import only one member:
>
>```
>using A::print;
>
>int main() {
>    print();
>}
>```
>
>### The `std` namespace
>
>The C++ Standard Library places its functions and classes inside the `std` namespace.
>
>Without `using namespace std;`:
>
>```
>std::cout << "Hello";
>std::endl;
>```
>
>With it:
>
>```
>using namespace std;
>
>cout << "Hello";
>endl(cout);
>```
>
>### Nested namespaces
>
>Namespaces can be nested:
>
>```
>namespace Company {
>    namespace Project {
>        void display() {
>            std::cout << "Nested namespace";
>        }
>    }
>}
>
>int main() {
>    Company::Project::display();
>}
>```
>
>Since C++17, you can write this more concisely:
>
>```
>namespace Company::Project {
>    void display() {
>        std::cout << "Nested namespace";
>    }
>}
>```
>
>### Anonymous namespace
>
>An unnamed (anonymous) namespace limits visibility to the current source file:
>
>```
>namespace {
>    int x = 10;
>}
>```
>
>This is often used for file-local variables and functions.
>
>### Summary
>
>- A **namespace** groups related code.
>- It prevents naming conflicts between different parts of a program or libraries.
>- Access members using the **scope resolution operator (`::`)**.
>- `std` is the namespace used by the C++ Standard Library.
>- Avoid `using namespace std;` in header files and large projects to reduce the risk of name collisions.
>
>
