#!/usr/bin/env python3
"""
Comprehensive Push Swap Test Suite
Validates sorting correctness, operation benchmarks, error handling,
format compliance, and memory leak freedom.
"""

import itertools
import os
import random
import shutil
import subprocess
import sys
import time

# Colors
GREEN = "\033[32m"
RED = "\033[31m"
YELLOW = "\033[33m"
CYAN = "\033[36m"
BOLD = "\033[1m"
RESET = "\033[0m"

TESTS_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(TESTS_DIR)
PUSH_SWAP_BIN = os.path.join(PROJECT_DIR, "push_swap")


class VirtualChecker:
    VALID_OPS = {
        "sa", "sb", "ss",
        "pa", "pb",
        "ra", "rb", "rr",
        "rra", "rrb", "rrr"
    }

    @staticmethod
    def simulate(initial_numbers, operations):
        a = list(initial_numbers)
        b = []
        for i, op in enumerate(operations):
            op = op.strip()
            if not op:
                continue
            if op not in VirtualChecker.VALID_OPS:
                return False, f"Line {i + 1}: Unknown instruction '{op}'"
            if op == "sa":
                if len(a) >= 2:
                    a[0], a[1] = a[1], a[0]
            elif op == "sb":
                if len(b) >= 2:
                    b[0], b[1] = b[1], b[0]
            elif op == "ss":
                if len(a) >= 2:
                    a[0], a[1] = a[1], a[0]
                if len(b) >= 2:
                    b[0], b[1] = b[1], b[0]
            elif op == "pa":
                if b:
                    a.insert(0, b.pop(0))
            elif op == "pb":
                if a:
                    b.insert(0, a.pop(0))
            elif op == "ra":
                if a:
                    a.append(a.pop(0))
            elif op == "rb":
                if b:
                    b.append(b.pop(0))
            elif op == "rr":
                if a:
                    a.append(a.pop(0))
                if b:
                    b.append(b.pop(0))
            elif op == "rra":
                if a:
                    a.insert(0, a.pop())
            elif op == "rrb":
                if b:
                    b.insert(0, b.pop())
            elif op == "rrr":
                if a:
                    a.insert(0, a.pop())
                if b:
                    b.insert(0, b.pop())

        if b:
            return False, f"Stack B not empty ({len(b)} elements remain)"
        if a != sorted(initial_numbers):
            return False, f"Stack A not sorted: expected {sorted(initial_numbers)[:10]}, got {a[:10]}"
        return True, "OK"


class PushSwapTester:
    def __init__(self):
        self.results = {}
        self.total_passed = 0
        self.total_failed = 0
        self.start_time = time.time()

    def run_cmd(self, args, timeout=10):
        cmd = [PUSH_SWAP_BIN] + args
        try:
            res = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)
            return res.returncode, res.stdout, res.stderr, None
        except subprocess.TimeoutExpired:
            return None, "", "", f"Timeout ({timeout}s expired)"
        except Exception as e:
            return None, "", "", str(e)

    def record(self, suite, name, success, details=""):
        if suite not in self.results:
            self.results[suite] = {"passed": 0, "failed": 0, "tests": []}
        if success:
            self.results[suite]["passed"] += 1
            self.total_passed += 1
        else:
            self.results[suite]["failed"] += 1
            self.total_failed += 1
            print(f"  {RED}[FAIL]{RESET} {name}: {details}")
        self.results[suite]["tests"].append((name, success, details))

    def test_identity_and_sorted(self):
        suite = "Identity & Zero-Op Edge Cases"
        cases = [
            ("0 arguments", []),
            ("1 argument (positive)", ["42"]),
            ("1 argument (negative)", ["-42"]),
            ("1 argument (zero)", ["0"]),
            ("1 argument (INT_MAX)", ["2147483647"]),
            ("1 argument (INT_MIN)", ["-2147483648"]),
            ("1 argument (quoted)", ["42"]),
            ("Already sorted (2 numbers)", ["1", "2"]),
            ("Already sorted (3 numbers)", ["1", "2", "3"]),
            ("Already sorted (5 numbers)", ["-10", "0", "5", "20", "99"]),
            ("Already sorted (10 numbers)", ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]),
        ]
        for name, args in cases:
            code, stdout, stderr, err = self.run_cmd(args)
            if err:
                self.record(suite, name, False, err)
            elif code != 0:
                self.record(suite, name, False, f"Expected exit code 0, got {code}")
            elif stdout != "":
                self.record(suite, name, False, f"Expected empty stdout, got {repr(stdout)}")
            elif stderr != "":
                self.record(suite, name, False, f"Expected empty stderr, got {repr(stderr)}")
            else:
                self.record(suite, name, True)

    def test_error_handling(self):
        suite = "Error Handling & Input Validation"
        cases = [
            ("Empty argument string", [""]),
            ("Whitespace only argument", ["   "]),
            ("Mixed valid with empty string", ["1", "", "2"]),
            ("Non-numeric alphabetic string", ["hello"]),
            ("Non-numeric token embedded", ["1", "a", "3"]),
            ("Non-numeric with suffix", ["123a"]),
            ("Non-numeric with prefix", ["a123"]),
            ("Special characters", ["1", "!", "2"]),
            ("Sign without digit (+)", ["+"]),
            ("Sign without digit (-)", ["-"]),
            ("Double sign (++)", ["++1"]),
            ("Double sign (--)", ["--1"]),
            ("Double sign (+-)", ["+-1"]),
            ("Double sign (-+)", ["-+1"]),
            ("Sign in middle of number", ["1-1"]),
            ("Duplicate numbers (adjacent)", ["1", "2", "2", "3"]),
            ("Duplicate numbers (spaced)", ["1", "2", "3", "1"]),
            ("Duplicate zeros", ["0", "-0"]),
            ("Duplicate negative numbers", ["-42", "10", "-42"]),
            ("INT_MAX overflow (+2147483648)", ["2147483648"]),
            ("INT_MAX large overflow", ["99999999999999999999"]),
            ("INT_MIN underflow (-2147483649)", ["-2147483649"]),
            ("INT_MIN large underflow", ["-99999999999999999999"]),
            ("Quoted invalid token", ["1 2 a 3"]),
            ("Quoted overflow token", ["1 2147483648 3"]),
            ("Quoted duplicate token", ["1 2 2 3"]),
        ]
        for name, args in cases:
            code, stdout, stderr, err = self.run_cmd(args)
            if err:
                self.record(suite, name, False, err)
            elif code == 0:
                self.record(suite, name, False, "Expected non-zero exit code on error")
            elif stderr != "Error\n":
                self.record(suite, name, False, f"Expected stderr 'Error\\n', got {repr(stderr)}")
            elif stdout != "":
                self.record(suite, name, False, f"Expected empty stdout on error, got {repr(stdout)}")
            else:
                self.record(suite, name, True)

    def test_argument_formatting(self):
        suite = "Argument Formatting & Quoting"
        cases = [
            ("Standard separate args", ["3", "2", "1"]),
            ("Single quoted string", ["3 2 1"]),
            ("Mixed quoted and unquoted args", ["3 2", "1"]),
            ("Multiple quoted strings", ["4 3", "2 1"]),
            ("Extra internal whitespace", ["  3   2   1  "]),
            ("Tab separated args", ["3\t2\t1"]),
            ("Negative numbers and zero", ["-1", "-5", "0", "2", "-10"]),
            ("Extreme bounds (INT_MIN & INT_MAX)", ["2147483647", "-2147483648", "0"]),
        ]
        for name, args in cases:
            initial = [int(tok) for arg in args for tok in arg.split()]
            code, stdout, stderr, err = self.run_cmd(args)
            if err:
                self.record(suite, name, False, err)
                continue
            if code != 0:
                self.record(suite, name, False, f"Failed with exit code {code}: stderr={stderr}")
                continue
            ops = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
            ok, msg = VirtualChecker.simulate(initial, ops)
            if not ok:
                self.record(suite, name, False, msg)
            else:
                self.record(suite, name, True, f"{len(ops)} ops")

    def test_size_two(self):
        suite = "Size 2 Benchmark (Target: <= 1 op)"
        perms = [[1, 2], [2, 1]]
        for p in perms:
            args = [str(x) for x in p]
            name = f"Permutation {p}"
            code, stdout, stderr, err = self.run_cmd(args)
            if err:
                self.record(suite, name, False, err)
                continue
            ops = [l.strip() for l in stdout.strip().split("\n") if l.strip()]
            ok, msg = VirtualChecker.simulate(p, ops)
            if not ok:
                self.record(suite, name, False, msg)
            elif len(ops) > 1:
                self.record(suite, name, False, f"Exceeded max 1 op: got {len(ops)} ops")
            else:
                self.record(suite, name, True, f"{len(ops)} op(s)")

    def test_size_three(self):
        suite = "Size 3 Benchmark (Target: <= 3 ops)"
        perms = list(itertools.permutations([1, 2, 3]))
        for p in perms:
            initial = list(p)
            args = [str(x) for x in initial]
            name = f"Permutation {initial}"
            code, stdout, stderr, err = self.run_cmd(args)
            if err:
                self.record(suite, name, False, err)
                continue
            ops = [l.strip() for l in stdout.strip().split("\n") if l.strip()]
            ok, msg = VirtualChecker.simulate(initial, ops)
            if not ok:
                self.record(suite, name, False, msg)
            elif len(ops) > 3:
                self.record(suite, name, False, f"Exceeded max 3 ops: got {len(ops)} ops")
            else:
                self.record(suite, name, True, f"{len(ops)} op(s)")

    def test_size_five(self):
        suite = "Size 5 Benchmark (Target: <= 12 ops)"
        perms = list(itertools.permutations([1, 2, 3, 4, 5]))
        max_ops = 0
        total_ops = 0
        failed = False
        for p in perms:
            initial = list(p)
            args = [str(x) for x in initial]
            code, stdout, stderr, err = self.run_cmd(args)
            if err:
                self.record(suite, f"Perm {initial}", False, err)
                failed = True
                break
            ops = [l.strip() for l in stdout.strip().split("\n") if l.strip()]
            ok, msg = VirtualChecker.simulate(initial, ops)
            if not ok:
                self.record(suite, f"Perm {initial}", False, msg)
                failed = True
                break
            count = len(ops)
            max_ops = max(max_ops, count)
            total_ops += count
            if count > 12:
                self.record(suite, f"Perm {initial}", False, f"Exceeded 12 ops limit: got {count} ops")
                failed = True
                break

        if not failed:
            avg_ops = total_ops / len(perms)
            self.record(
                suite,
                f"All 120 permutations verified (max={max_ops}, avg={avg_ops:.1f})",
                True,
                f"Max: {max_ops}/12 ops"
            )

    def test_size_100(self):
        suite = "Size 100 Benchmark (Target: < 700 for 5/5, < 1500 to pass)"
        runs = 10
        op_counts = []
        for r in range(runs):
            nums = random.sample(range(-10000, 10000), 100)
            args = [str(x) for x in nums]
            code, stdout, stderr, err = self.run_cmd(args, timeout=15)
            if err:
                self.record(suite, f"Run {r + 1}", False, err)
                return
            ops = [l.strip() for l in stdout.strip().split("\n") if l.strip()]
            ok, msg = VirtualChecker.simulate(nums, ops)
            if not ok:
                self.record(suite, f"Run {r + 1}", False, msg)
                return
            op_counts.append(len(ops))

        min_ops = min(op_counts)
        max_ops = max(op_counts)
        avg_ops = sum(op_counts) / len(op_counts)
        score = "5/5" if avg_ops < 700 else ("4/5" if avg_ops < 900 else ("3/5" if avg_ops < 1100 else ("2/5" if avg_ops < 1300 else "1/5")))
        self.record(
            suite,
            f"{runs} randomized runs (min={min_ops}, max={max_ops}, avg={avg_ops:.1f}, score={score})",
            True,
            f"avg={avg_ops:.1f} ops"
        )

    def test_size_500(self):
        suite = "Size 500 Benchmark (Target: < 5500 for 5/5, < 11500 to pass)"
        runs = 5
        op_counts = []
        for r in range(runs):
            nums = random.sample(range(-50000, 50000), 500)
            args = [str(x) for x in nums]
            code, stdout, stderr, err = self.run_cmd(args, timeout=30)
            if err:
                self.record(suite, f"Run {r + 1}", False, err)
                return
            ops = [l.strip() for l in stdout.strip().split("\n") if l.strip()]
            ok, msg = VirtualChecker.simulate(nums, ops)
            if not ok:
                self.record(suite, f"Run {r + 1}", False, msg)
                return
            op_counts.append(len(ops))

        min_ops = min(op_counts)
        max_ops = max(op_counts)
        avg_ops = sum(op_counts) / len(op_counts)
        score = "5/5" if avg_ops < 5500 else ("4/5" if avg_ops < 7000 else ("3/5" if avg_ops < 8500 else ("2/5" if avg_ops < 10000 else "1/5")))
        self.record(
            suite,
            f"{runs} randomized runs (min={min_ops}, max={max_ops}, avg={avg_ops:.1f}, score={score})",
            True,
            f"avg={avg_ops:.1f} ops"
        )

    def test_valgrind_leaks(self):
        suite = "Memory Leaks & Valgrind Verification"
        if not shutil.which("valgrind"):
            print(f"  {YELLOW}[SKIP]{RESET} Valgrind not found in PATH")
            return

        cases = [
            ("Sorted 5 elements", ["1", "2", "3", "4", "5"]),
            ("Unsorted 5 elements", ["5", "2", "3", "1", "4"]),
            ("Single element", ["42"]),
            ("Error case (non-numeric)", ["1", "a", "3"]),
            ("Error case (duplicate)", ["1", "2", "2", "3"]),
            ("Error case (overflow)", ["2147483648"]),
            ("Error case (empty string)", [""]),
        ]

        for name, args in cases:
            cmd = [
                "valgrind",
                "--leak-check=full",
                "--show-leak-kinds=all",
                "--errors-for-leak-kinds=all",
                "--error-exitcode=99",
                PUSH_SWAP_BIN
            ] + args
            try:
                res = subprocess.run(cmd, capture_output=True, text=True, timeout=15)
                output = res.stderr
                has_leak_free = "All heap blocks were freed -- no leaks are possible" in output
                has_zero_errors = "ERROR SUMMARY: 0 errors from 0 contexts" in output
                if has_leak_free and has_zero_errors:
                    self.record(suite, name, True)
                else:
                    self.record(suite, name, False, "Valgrind detected leaks or memory errors")
            except subprocess.TimeoutExpired:
                self.record(suite, name, False, "Valgrind execution timed out")
            except Exception as e:
                self.record(suite, name, False, str(e))

    def print_summary(self):
        duration = time.time() - self.start_time
        print("\n" + "=" * 70)
        print(f"{BOLD}{CYAN}                 PUSH_SWAP TEST RESULTS SUMMARY{RESET}")
        print("=" * 70)
        print(f"{'Test Suite':<42} | {'Passed':<8} | {'Failed':<8} | {'Status'}")
        print("-" * 70)

        for suite_name, data in self.results.items():
            p = data["passed"]
            f = data["failed"]
            status = f"{GREEN}PASS{RESET}" if f == 0 else f"{RED}FAIL{RESET}"
            print(f"{suite_name:<42} | {p:<8} | {f:<8} | {status}")

        print("-" * 70)
        total = self.total_passed + self.total_failed
        overall_status = f"{GREEN}{BOLD}ALL TESTS PASSED{RESET}" if self.total_failed == 0 else f"{RED}{BOLD}TESTS FAILED{RESET}"
        print(f"Total Tests: {total} | Passed: {self.total_passed} | Failed: {self.total_failed} | Time: {duration:.2f}s")
        print(f"Overall Result: {overall_status}")
        print("=" * 70 + "\n")

    def run_all(self):
        if not os.path.isfile(PUSH_SWAP_BIN):
            print(f"{RED}Error: Binary not found: {PUSH_SWAP_BIN}{RESET}")
            print(f"Please build the project first: make -C {PROJECT_DIR}")
            sys.exit(1)

        print(f"{BOLD}{CYAN}Running Push Swap Comprehensive Test Suite...{RESET}\n")
        self.test_identity_and_sorted()
        self.test_error_handling()
        self.test_argument_formatting()
        self.test_size_two()
        self.test_size_three()
        self.test_size_five()
        self.test_size_100()
        self.test_size_500()
        self.test_valgrind_leaks()
        self.print_summary()
        sys.exit(0 if self.total_failed == 0 else 1)


if __name__ == "__main__":
    tester = PushSwapTester()
    tester.run_all()
