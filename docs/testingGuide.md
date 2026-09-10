# 42 School Monorepo — Testing & CI Guide

This guide explains how to write, execute, and automate tests across projects in this repository, both **locally** and in the **GitHub Actions CI pipeline**.

---

## 1. 🎯 Testing Philosophy

- **Safety**: Tests live inside `tests/` folders and never interfere with official 42 compilation rules (`all`, `clean`, `fclean`, `re`).
- **Norm Exemption**: Test files are deliberately exempt from Norminette rules so you can use standard assertion libraries, `printf`, and comprehensive testing logic.
- **Selectivity**: You can choose to run tests for only the specific project you are actively modifying, avoiding slow, bloated test cycles.

---

## 2. 💻 Running Tests Locally

### Run Tests for a Specific Project

From the repository root:

```bash
make test PROJECT=libft
# or
make test-libft
```

Inside the project directory directly:

```bash
cd r00/libft
make test
```

### Clean Up Test Artifacts

```bash
make fclean-all
```

---

## 3. 🤖 Automated Testing in GitHub Actions CI

Whenever you push code or open a Pull Request, GitHub Actions checks which files changed:

- If you modified files in `r00/libft/**`, it triggers the **Libft Test Job**.
- If you modified files in `r03/minishell/**`, it triggers the **Minishell Test Job**.
- Projects you didn't touch are **automatically skipped** to keep CI fast and efficient.

### Manual Test Execution via GitHub UI

You can manually run tests for any project from the GitHub Actions dashboard:

1. Go to your repository on GitHub.
2. Click **Actions** > **Project Tester**.
3. Click **Run workflow** and select the project you want to test from the dropdown menu (`libft`, `minishell`, `push_swap`, or `all`).

---

## 4. 📝 How to Add Tests to a New Project

To add automated tests to any project (e.g. `r02/push_swap` or `r03/minishell`):

1. **Create the `tests/` directory**:
   ```bash
   mkdir -p rXX/<project>/tests
   ```
2. **Add your test script or runner**:
   - For C unit tests: `rXX/<project>/tests/testMain.c`
   - For integration/shell tests: `rXX/<project>/tests/testRunner.sh`
3. **Add a `test` target in that project's Makefile**:
   ```makefile
   test: all
   	@bash tests/testRunner.sh
   ```
4. **Ensure `fclean` removes test outputs**:
   ```makefile
   fclean: clean
   	$(RM) $(NAME) testRunner
   ```

---

## 5. 🛡️ Local Git Pre-Commit Hook

Install the automated pre-commit hook with a single command:

```bash
make setup-hooks
```

### What It Does:

- **Auto-Norminette**: Whenever you run `git commit`, the hook automatically runs `norminette` on all staged `.c` and `.h` files (ignoring `tests/`). If there are any Norm errors, Git blocks the commit and highlights the line numbers.
- **Artifact Blocker**: Blocks accidental staging of `*.o`, `*.a`, `.DS_Store`, or compiled binary executables.
- **Bypass (if needed)**: Use `git commit --no-verify` in emergency situations to bypass local checks.

---

## 6. 📦 42 Intra / Vogsphere Submission Pipeline

When ready to submit a project for peer defense and Moulinette evaluation:

```bash
make submit PROJECT=libft REMOTE=git@vogsphere.42bangkok.com:vogsphere/intra-...
```

### Automated 4-Step Pipeline:

1. **[Step 1/4] Norminette Quality Gate**: Runs `make norm DIR=rXX/<project>`. If any Norm error exists, **aborts immediately**.
2. **[Step 2/4] Automated Tests**: Executes `make test PROJECT=<project>` to ensure all unit tests pass before submission.
3. **[Step 3/4] Build Object Cleanup**: Runs `make fclean` in the project folder to guarantee no compiled objects are sent.
4. **[Step 4/4] Subtree Push**: Uses `git subtree push` to push only the clean project directory directly to the root of the 42 Intra remote.

_Note: Once you provide a git URL for a project, it is saved under remote `vogsphere-<project>`. For subsequent submissions of the same project, you can simply run:_

```bash
make submit PROJECT=libft
```
