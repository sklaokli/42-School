# Git & PR Workflow Guide

This guide establishes the Git branching rules, commit standards, and Pull Request workflow for this repository. It serves as the Single Source of Truth for both manual development and AI-assisted workflows.

---

## 1. Quick Reference

| Action / Element      | Rule                                                    | Rationale                                                                |
| :-------------------- | :------------------------------------------------------ | :----------------------------------------------------------------------- |
| **`main` Branch**     | **PROTECTED**. Never commit directly to `main`.         | Keeps `main` stable, tested, and deployable.                             |
| **Task Branches**     | Create `<type>/<description>` off `main`.               | Isolates all feature work, bug fixes, and tests.                         |
| **Branch Continuity** | Stay on the active branch for all iterations of a task. | Prevents branch proliferation and fragmented PR history.                 |
| **Commit Control**    | Developer executes `git add` and `git commit`.          | Human-in-the-loop oversight over all Git history.                        |
| **Commit Style**      | Conventional Commits (`type(scope): summary`).          | Standardized changelogs and clean history.                               |
| **PR Subject Limit**  | **Line 1 must be $\le 60$ characters**.                 | Prevents GitHub truncating title and spilling words into PR description. |
| **PR Auto-Fill**      | Use `git commit -F PR_INFO.md`.                         | Populates 100% of the PR title and description automatically.            |

---

## 2. Branching Strategy

### Rule 1: Never Touch `main` Directly

- MUST verify the active branch before modifying files: `git branch --show-current`.
- MUST branch off latest `main` before starting any work:
  ```bash
  git checkout main
  git pull origin main
  git checkout -b <type>/<description>
  ```

### Rule 2: Dedicated Branch Naming

- `feat/<project>-<description>` (e.g. `feat/minishell-heredoc`)
- `fix/<project>-<description>` (e.g. `fix/so_long-floodfill`)
- `test/<project>-<description>` (e.g. `test/push-swap-benchmarks`)
- `docs/<description>` (e.g. `docs/workflow-guide`)
- `refactor/<project>-<description>` (e.g. `refactor/norm-cleanup`)

### Rule 3: Branch Continuity for Iterations

- MUST keep iterations, debugging, code reviews, and follow-up edits on the same active branch.
- MUST NOT create a new branch for minor revisions to the same ongoing task.

### Rule 4: Clean Branch Lifecycle

- Once a branch is merged into `main` (or abandoned), delete both local and remote branches:
  ```bash
  git checkout main
  git pull origin main
  git branch -d <branch-name>
  git push origin --delete <branch-name>
  ```

### Rule 5: Scope Isolation (Monorepo Protection)

- MUST NOT modify, reformat, or delete files outside the target project directory of the active task.
- Projects from previous ranks are strictly read-only unless the task explicitly calls for updates.

---

## 3. Commit Standards & Authority

### Human-in-the-Loop Authority

- Any AI agent or coding assistant MUST NEVER execute `git add` or `git commit`.
- Staging and committing are strictly executed by the developer.
- The AI prepares file edits and provides exact terminal commands for the developer to review and run.

### Conventional Commit Format

```text
<type>(<scope>): <summary in imperative mood>
```

| Type       | Purpose                                    | Example                                                      |
| :--------- | :----------------------------------------- | :----------------------------------------------------------- |
| `feat`     | New feature or project implementation      | `feat(minishell): add pipe redirection handling`             |
| `fix`      | Bug fix or memory leak resolution          | `fix(push_swap): resolve duplicate number parsing bug`       |
| `test`     | Adding or updating test suites             | `test(libft): add unit tests for ft_split`                   |
| `refactor` | Code restructuring without behavior change | `refactor(so_long): split render loop to meet 25-line limit` |
| `docs`     | Documentation updates                      | `docs: document PR auto-fill workflow`                       |
| `ci`       | GitHub Actions workflow updates            | `ci: add automated push_swap test job`                       |

---

## 4. The `PR_INFO.md` Auto-Fill Pattern

When creating a Pull Request on GitHub, manually copy-pasting titles and markdown templates is error-prone. We use the `PR_INFO.md` file pattern to populate 100% of the PR title and description from the Git commit.

### How GitHub Extracts PR Metadata

When a feature branch has **one commit** ahead of `main`:

1. GitHub uses the **commit subject (Line 1)** as the **PR Title**.
2. GitHub uses the **commit body (Line 3+)** as the **PR Description**.

### The 60-Character Rule

> [!IMPORTANT]
> **Line 1 must be $\le 60$ characters.**
> Git and GitHub follow the 50/72 convention. If Line 1 exceeds ~65–72 characters, GitHub chops the PR title with an ellipsis (`...`) and **spills the trailing words into the top of the description box**. Keeping Line 1 at or below 60 characters guarantees a clean title and prevents description pollution.

### File Structure (`PR_INFO.md`)

```markdown
<type>(<scope>): <concise title <= 60 characters>

### 📌 Area & Scope

- **Target Area**: `...`
- **Project**: `...`

---

### 📝 Summary of Updates

- Key bullet points explaining what changed and why.

---

### 🧪 Verification Checklist

- [x] Local tests executed and passing
- [x] Norminette compliance verified
- [x] Memory safety verified (valgrind / ASan)
```

1. **Line 1**: Conventional Commit subject ($\le 60$ chars).
2. **Line 2**: Strictly blank.
3. **Line 3+**: Full Markdown body conforming to `.github/PULL_REQUEST_TEMPLATE/`.

### Developer Workflow for PRs

```bash
# 1. Review status and diff
git status
git diff

# 2. Stage modified files (PR_INFO.md is temporary and gitignored)
git add <modified-files>

# 3. Commit using PR_INFO.md as the commit message source
git commit -F PR_INFO.md

# 4. Remove the temporary PR_INFO.md file
rm PR_INFO.md

# 5. Push branch
git push -u origin <branch-name>
```

After pushing, open the compare link printed in the terminal:
`https://github.com/sklaokli/42-School/compare/<branch-name>?expand=1`

The title and description are completely filled out automatically.
