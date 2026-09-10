# Agent Operating Rules & SSOT Router

This file defines the non-negotiable operational boundaries for any agentic AI or automated coding assistant operating in this repository. All coding, testing, and workflow standards reside in `docs/` as the **Single Source of Truth (SSOT)**.

---

## 1. Operational Invariants

- **NEVER Work Directly on `main`**:
  - Never edit, create, or delete files on `main`.
  - Always verify the active branch first: `git branch --show-current`.
  - If on `main`, switch to or create a dedicated task branch first (`feat/...`, `fix/...`, `test/...`, `docs/...`).
- **Branch Continuity**:
  - Keep iterations, debugging, and follow-ups on the existing active branch.
  - Do not create new branches for small revisions to the same task.
- **Human-in-the-Loop Git Control**:
  - **The AI MUST NEVER run `git add` or `git commit`.**
  - Staging and committing are strictly human developer actions.
  - The AI prepares file modifications and provides clear terminal commands for the developer to review and execute.
- **PR Description Auto-Fill Protocol (`PR_INFO.md`)**:
  - When preparing a PR, generate `PR_INFO.md` at the repository root.
  - **Line 1 (Title)**: Must be $\le 60$ characters (prevents GitHub subject truncation and spillover into description).
  - **Line 2**: Strictly blank.
  - **Line 3+ (Body)**: Complete Markdown formatted to match `.github/PULL_REQUEST_TEMPLATE/`.
  - Provide commit command: `git commit -F PR_INFO.md`.
  - Provide GitHub compare link: `https://github.com/sklaokli/42-School/compare/<branch>?expand=1`.
- **Scope Isolation (Monorepo Protection)**:
  - Never edit, reformat, or delete files outside the specific project directory target of the active task.
  - Projects from previous ranks are strictly read-only unless explicitly requested by the developer.

---

## 2. Canonical Single Source of Truth (`docs/`)

All project specifications, coding rules, and testing standards are maintained exclusively in `docs/`.

> [!IMPORTANT]
> **Progressive Disclosure**:
> Do **NOT** read all documentation files upfront.
> **ONLY** read the specific document using your file-reading tool when the active task requires it:

| Task Domain                 | SSOT Document                                    | When to Read                                                                                                |
| :-------------------------- | :----------------------------------------------- | :---------------------------------------------------------------------------------------------------------- |
| **Code Style & Norminette** | [`docs/styleGuide.md`](docs/styleGuide.md)       | When authoring or reviewing C source (25-line limits, 4 params, 5 vars, forbidden syntax) or C++98 classes. |
| **Testing Standards & CI**  | [`docs/testingGuide.md`](docs/testingGuide.md)   | When adding test suites, structuring `tests/` directories (Norm-exempt), or running local harnesses.        |
| **Git & PR Workflows**      | [`docs/workflowGuide.md`](docs/workflowGuide.md) | When creating branches, preparing PR metadata, or reviewing commit conventions.                             |
