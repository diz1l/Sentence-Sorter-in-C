# Sentence Sorter in C

This program reads an input text file, splits it into sentences, and prints them in alphabetical order.

## Features
- Splits sentences by `.`, `?`, and `!`
- Trims leading and trailing spaces
- Converts all text to lowercase (for consistent sorting)
- Uses dynamic memory allocation for storing sentences
- Sorts sentences alphabetically with `qsort`
- Frees all allocated memory

## How it Works
1. The file `abc.txt` is opened and read line by line.
2. Each line is split into tokens (sentences) using `strtok` with delimiters `.?!`.
3. Each token:
   - Is converted to lowercase (`toLower`)
   - Is trimmed of leading and trailing spaces (`trim`)
   - Is copied into a dynamic array of strings (`append_sentence`)
4. After all sentences are collected, `qsort` sorts them alphabetically.
5. The sorted sentences are printed to the console.

## Example

### Input file (`abc.txt`)
```
C is a powerful language.  
Programming is fun!  
How are you?  
Age is just a number.  
```

### Program output
```
[age is just a number]
[c is a powerful language]
[how are you]
[programming is fun]
```

## Program Flow (ASCII Diagram)

```
        ┌──────────────────────────┐
        │  Start Program (main)    │
        └─────────────┬────────────┘
                      │
                      ▼
        ┌──────────────────────────┐
        │ Open file "abc.txt"      │
        └─────────────┬────────────┘
                      │
             [File not found?]
                      │Yes
                      ▼
             ┌─────────────────┐
             │ Print ERROR msg │
             │ Exit program    │
             └─────────────────┘
                      │No
                      ▼
        ┌──────────────────────────┐
        │ Read file line by line   │
        └─────────────┬────────────┘
                      │
                      ▼
        ┌──────────────────────────┐
        │ Split line into tokens   │
        │ (delimiters . ? !)       │
        └─────────────┬────────────┘
                      │
                      ▼
        ┌──────────────────────────┐
        │ For each token:          │
        │  • toLower(token)        │
        │  • trim(token)           │
        │  • save in array         │
        └─────────────┬────────────┘
                      │
                      ▼
        ┌──────────────────────────┐
        │ All sentences collected  │
        └─────────────┬────────────┘
                      │
                      ▼
        ┌──────────────────────────┐
        │ Sort array with qsort    │
        └─────────────┬────────────┘
                      │
                      ▼
        ┌──────────────────────────┐
        │ Print sorted sentences   │
        └─────────────┬────────────┘
                      │
                      ▼
        ┌──────────────────────────┐
        │ Free memory, close file  │
        └─────────────┬────────────┘
                      │
                      ▼
        ┌──────────────────────────┐
        │        End Program       │
        └──────────────────────────┘
```

## Build & Run

### Compile
```bash
gcc -std=c17 -Wall -Wextra -O2 main.c -o sorter
```

### Run
```bash
./sorter
```

⚠️ Make sure that the input file is named `abc.txt` and is located in the same directory as the compiled program.

## Possible Improvements

- **Preserve original case**  
  Currently, all text is converted to lowercase for consistent sorting.  
  An alternative is to keep the original case and implement a custom
  case-insensitive comparison function for sorting.

- **Handle multi-character punctuation**  
  For example: ellipsis (`...`), question marks with exclamations (`?!`),
  or abbreviations like `U.S.A.`.  
  The current code simply splits at every `.`, `?`, or `!`.

- **Support larger files**  
  The program reads the file line by line using a buffer of 2024 bytes.
  For very large files or very long sentences, it may be better to read
  the entire file into memory or use dynamic growing buffers.

- **Configurable delimiters**  
  Instead of hardcoding `.?!`, make delimiters configurable through
  program arguments or a configuration file.

- **Output formatting**  
  Add line numbers or restore original punctuation marks at the end of
  each sentence for clearer output.

- **Error handling**  
  The code currently skips memory allocation errors silently.  
  A robust version would handle these cases and notify the user.

- **Unit tests**  
  Add automated tests for `trim`, `toLower`, and the sorting logic
  to ensure correctness on edge cases.

- **Unicode support**  
  At the moment, only basic ASCII characters are handled.  
  Adding UTF-8 support would allow sorting of multilingual text.
