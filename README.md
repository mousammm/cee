# cee (bee + compiler)

On my to create my own compiler, that spits x86_64 machine code!

Though currently im learning more about intrepreters.

**Prerequisites**
- [Tutorial point](https://www.tutorialspoint.com/compiler_design/index.htm)
- DSA : [trees, graphs, hash tables, graph traversal algorithms, Abstract Syntax Trees (ASTs) Control Flow Graphs (CFGs)]
- assembly : x86-64, fasm
- [Formal Languages and Automata, Learn regular expressions, finite automata, context-free grammars]

**Resource's**
- [craftinginterpreters by Nora Sandler](https://craftinginterpreters.com/)
- [c4 intrepreter](https://github.com/lotabout/write-a-C-interpreter/)
- [Let's Build a Compiler by Jack Crenshaw](https://compilers.iecc.com/crenshaw/)
- [Kaleidoscope LLVM IR](https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/index.html)

**codebase**
- [chibicc](https://github.com/rui314/chibicc)
- [tcc](https://repo.or.cz/tinycc.git/tree)
- [qbe backend]()

**books**
- [DRAGON BOOK:compilers: Principles, Techniques, and Tools (1st edition)]()
- [the C programming language: 2nd edition ANCII C]()
- [Modern-Compiler-Implementation-in-C](https://raw.githubusercontent.com/yihui-he/Modern-Compiler-Implementation-in-C/master/Modern%20Compiler%20Implementation%20in%20C.pdf)

**Path**
- [reddit](https://www.reddit.com/r/Compilers/comments/1qhey2x/i_wish_to_study_compiler_design_and_also_wish_to/)
- [Read Crafting Interpreters](https://www.google.com/search?kgmid=%2Fg%2F11np48zhhk&q=so+i+want+to+actually+study+compiler+desing+like+actually+the+real+one+crafting+interpreters)
- [Work through Modern Compiler Implementation](https://www.google.com/search?kgmid=%2Fg%2F11cpkjjm_d&q=so+i+want+to+actually+study+compiler+desing+like+actually+the+real+one+modern+compiler+implementation) by Andrew Appel.

**Projects**
- [Craig Stuntz](https://www.craigstuntz.com/posts/2023-10-13-learning-compilers-and-programming-languages.html)
- Real Hardware. Write a backend that emits x86-64
- Build a Frontend. Write a hand-coded recursive descent parser that converts source text into an AST and performs semantic type checking.
- Generate an Intermediate Representation (IR). Lower your AST into Three-Address Code (TAC) or an SSA-based IR, then build a Control Flow Graph.
- Implement Optimizations. Write passes over your IR to perform constant folding, dead code elimination, and common subexpression elimination.
