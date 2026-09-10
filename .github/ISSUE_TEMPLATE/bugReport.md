---
name: Bug Report
about: Track a bug, segmentation fault, or memory leak in a project
title: "[Bug] <Short summary>"
labels: ["bug"]
assignees: sklaokli
---

## 🐛 Bug Summary

A clear and concise description of the bug.

## 📁 Affected Project & File

- **Project**: (e.g. `r03/minishell`)
- **File / Function**: (e.g. `parser.c:parse_pipe()`)

## 🔁 Reproduction Steps

1. Run `./minishell`
2. Enter command: `cat << EOF | cat -e`
3. Observe crash / leak / unexpected output

## 💥 Expected vs Actual Behavior

- **Expected**: Command executes or displays error cleanly without crashing.
- **Actual**: Segmentation fault (core dumped) / Memory leak reported by Valgrind.

## 🔍 Debugger / Valgrind Output

```text
(Paste relevant valgrind or gdb backtrace here)
```
