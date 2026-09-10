# 42 School Monorepo — Style & Consistency Guide

This guide establishes the architectural, naming, and coding conventions across this repository to ensure long-term maintainability, Norm compliance, and a professional engineering standard.

---

## 1. 🗂️ Monorepo Directory Hierarchy

```
42-School/
├── r00/ – r05/                # Ranks: zero-padded lowercase (r00, r01, r02...)
│   └── <project_name>/        # Projects: lowercase or snake_case matching 42 intra
│       ├── Makefile           # Always uppercase 'M'
│       ├── src/               # Standardized source directory
│       ├── include/           # Standardized header directory
│       └── tests/             # Standardized test directory (plural)
├── docs/                      # Documentation and architecture guides
├── .github/                   # GitHub Actions, issue templates, and PR templates
└── Makefile                   # Root command center for monorepo and subtrees
```

---

## 2. 📄 Source Files: C vs. C++ Standards

### C Projects (Rank 00 – Rank 03 + miniRT)

Strict adherence to 42 **Norminette**:

- **File naming**: `snake_case.c` and `snake_case.h` (e.g. `ft_split.c`, `minishell.h`).
- **Functions**: `snake_case` (e.g. `ft_strjoin()`, `execute_pipeline()`).
- **Typedefs / Structs**: Prefix or suffix notation (`t_list`, `s_command`).
- **Constraints**: Max 25 lines/function, max 4 parameters, max 5 variables per function, no forbidden constructs (`for`, `switch`, `goto`, ternary).

### C++ Projects (Rank 04 & Rank 05)

Strict adherence to C++98 and **Object-Oriented Canonical Form**:

- **Class Files**: `PascalCase.cpp` and `PascalCase.hpp` matching the class name exactly (e.g. `Bureaucrat.cpp`, `Bureaucrat.hpp`).
- **Canonical Orthodox Form**: Default constructor, copy constructor, copy assignment operator, and destructor implemented for every class.
- **Exercises**: `ex00/`, `ex01/`, `ex02/` matching evaluation sheets.
- **Templates**: Definitions in `.hpp` or included `.tpp` files.

---

## 3. 🧪 Testing Standards

- Test directories must always be named **`tests/`** (plural).
- Test files are placed inside `tests/` (e.g. `tests/testMain.c`).
- Tests are **automatically excluded from Norminette** in CI and Makefile.
- Every project with tests must implement a `test:` target in its local Makefile.
- Test binaries and logs must be removed during `make fclean`.

---

## 4. 🌿 Git Workflow, Branches & Commits

### Branch Naming Convention

Always develop new features, bug fixes, or tests in a dedicated branch:

- `feat/<project>-<description>` (e.g. `feat/minishell-heredoc`)
- `fix/<project>-<description>` (e.g. `fix/so_long-floodfill`)
- `test/<project>-<description>` (e.g. `test/libft-memory`)
- `docs/<description>` (e.g. `docs/style-guide`)

### Conventional Commit Format

```text
<type>(<scope>): <short summary>
```

- **feat**: A new feature (`feat(minishell): add signal handling during heredoc`)
- **fix**: A bug fix (`fix(so_long): fix memory leak on map load error`)
- **test**: Adding or updating tests (`test(libft): add unit tests for ft_split`)
- **refactor**: Code change that neither fixes a bug nor adds a feature (`refactor(norm): split function to satisfy 25-line limit`)
- **docs**: Documentation only (`docs: update project roadmap`)
- **ci**: GitHub Actions or CI updates (`ci: exclude test suites from Norminette`)

For detailed Git branching rules, human-in-the-loop commit boundaries, and PR auto-fill instructions, see the [Git & PR Workflow Guide](workflowGuide.md).
