# BitStreamInterpreter

A simple command-line Bit Stream interpreter in C++ that takes a custom program and an input stream, then outputs the interpreted result in transformed format.

## 🛠️ Build Instructions

Make sure you have a C++ compiler installed (e.g., `g++`).

### Compile

```bash
g++ verimatrix.cpp -o BitStreamConvertor
```
Run the Bit stream convertor

```bash
BitStreamConvertor --program ">,>,>,>,>,>,>,>,>+<<<<<<<<+[>+]<[<]>>>>>>>>>[+<<<<<<<<[>]+<[+<]>>>>>>>>>>,>,>,>,>,>,>,>,>+<<<<<<<<+[>+]<[<]>>>>>>>>>]<[+<]+<<<<<<<<+[>+]<[<]>>>>>>>>>[+<<<<<<<<[>]+<[+<]>;>;>;>;>;>;>;>;<<<<<<<<+<<<<<<<<+[>+]<[<]>>>>>>>>>]<[+<]" --stream "hello world"
```