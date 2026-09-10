---
name: 42 Project Evaluation Checklist
about: Preparation checklist before peer defense and Moulinette submission
title: "[Evaluation] <Project Name> - Defense Prep"
labels: ["evaluation", "quality-assurance"]
assignees: sklaokli
---

## 📋 Project Details

- **Project Name**:
- **Rank**: (e.g. `r02`, `r03`)
- **Folder**: (e.g. `r02/so_long`)
- **Target Score**: `100` / `125` (with bonus)

---

## 🛠️ Pre-Evaluation Quality Checklist

### 1. The Norm (Norminette)

- [ ] Ran `norminette` on all `.c` and `.h` files
- [ ] 0 Norm Errors, 0 Norm Warnings
- [ ] Max 25 lines per function verified
- [ ] Max 4 parameters and 5 variables per function
- [ ] Header comments and prototypes match

### 2. Compilation & Make Rules

- [ ] Compiles with flags: `-Wall -Wextra -Werror`
- [ ] Zero compiler warnings treated as errors
- [ ] `make all` builds target executable
- [ ] `make clean` removes object files
- [ ] `make fclean` removes executables and archives
- [ ] `make re` performs clean rebuild without relinking unnecessarily
- [ ] No relink rule violation (typing `make` twice does not recompile)

### 3. Memory Safety & Leaks (Valgrind / AddressSanitizer)

- [ ] Tested basic execution under `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes`
- [ ] Zero definitely lost bytes
- [ ] Zero indirectly lost bytes
- [ ] Zero open file descriptors left unclosed
- [ ] Double-free protection verified
- [ ] NULL pointer dereference guards verified

### 4. Edge Cases & Resilience

- [ ] Invalid/empty command-line arguments handled cleanly
- [ ] Non-existent files, permission denied errors tested
- [ ] Signal interruptions (`Ctrl+C`, `Ctrl+\`, `Ctrl+D`) tested
- [ ] Extreme boundary values tested (INT_MIN, INT_MAX, overflow, long strings)

---

## 👥 Peer Defense Notes

- **Evaluator 1**:
  - Notes:
- **Evaluator 2**:
  - Notes:
- **Evaluator 3**:
  - Notes:

## 🎯 Final Grade: `___ / 125`
