#!/usr/bin/env python3

import argparse
import colorama
import os
import random
import signal
import string
import subprocess
import sys
import tempfile
import threading
import time
import token
import tokenize

from colorama import Fore, Style
from difflib import SequenceMatcher
from pathlib import Path

location = Path(sys.argv[0]).parent
content = location / ".." / "content"

default_patterns = {
    "cpp": ["*.cc", "*.C", "*.cpp", "*.cxx", "*.c++"],
    "py": ["*.py", "*.py2", "*.py3", "*.cpy"],
    "java": ["*.java"],
}

colorama.init()
clear = "\033[K"

def interrupt_handler(sig, frame):
    print(f"\n{clear}{Fore.RED}aborted{Style.RESET_ALL}")
    os._exit(1)

signal.signal(signal.SIGINT, interrupt_handler)

parser = argparse.ArgumentParser(description="TCR-Racer is a game to train your TCR typing ability.")
parser.add_argument("-p", dest="penalty", default="60", type=int, help='The penalty for "submitting" wrong code (in seconds)')
parser.add_argument("--patterns", default=None, nargs="+", help=f"Patterns to check which files in '{content}' should be considered")
for name, pattern in default_patterns.items():
    pattern_text = ",".join(pattern)
    parser.add_argument(f"--{name}", action="store_true", help=f"add {name} pattern ({pattern_text})")
parser.add_argument("--debug", action="store_true", help="Show debug information")
args = parser.parse_args()

selected_default_patterns = []
for name, pattern in default_patterns.items():
    if getattr(args, name):
        selected_default_patterns += pattern
if selected_default_patterns:
    args.patterns = (args.patterns or []) + selected_default_patterns

def matches_pattern(f):
    if args.patterns is None:
        return True
    return any(f.match(p) for p in args.patterns)

files = [f for f in content.rglob("*") if f.is_file() and f.suffix not in [".tex", ".sty"]]
filtered = [f for f in files if matches_pattern(f)]
print(f"Found {len(filtered)} matching files.")
if not filtered:
    sys.exit(1)
selected = random.choice(filtered)

language = "unknown"
for name, pattern in default_patterns.items():
    if any(selected.match(p) for p in pattern):
        language = name
if language in ["cpp", "py", "java"]:
    print(f"Language is: {language}, comments are ignored")
else:
    print(f"{Fore.YELLOW}WARNING:{Style.RESET_ALL} Language is unknown, you must type comments")

def normalize(file):
    if language in ["cpp", "java"]:
        # call c preprocessor to remove macros, comments and stuff
        with open(file) as f:
            text = subprocess.check_output(["cpp", "-dD", "-P", "-fpreprocessed"], stdin=f, encoding="utf-8")
        # remove whitespaces
        for whitespace in string.whitespace:
            text = text.replace(whitespace, "")
        return text
    elif language == "py":
        previous = token.INDENT
        cleaned = []
        with open(file) as f:
            for type, value, _, _, _ in tokenize.generate_tokens(f.readline):
                # remove comment and multiline comment
                if type == token.COMMENT:
                    continue
                elif type == token.STRING and previous == token.INDENT:
                    continue
                # remove whitespaces
                cleaned.append(value.strip())
                previous = type
        return "".join(cleaned)
    else:
        text = file.read_text()
        # remove whitespaces
        for whitespace in string.whitespace:
            text = text.replace(whitespace, "")
        return text
    
expected = normalize(selected)

tmpfile = (Path(tempfile.gettempdir()) / "tcrracer").with_suffix(selected.suffix)
tmpfile.write_text("")

print("You have to type to: ", Fore.YELLOW, tmpfile, Style.RESET_ALL, sep="")
#print("Press Enter to start",end="")
input("Press Enter to start")
print()
print("You have to type: ", Fore.YELLOW, selected.relative_to(content), Style.RESET_ALL, sep="")
if args.debug:
    print("Expected:", f"{Fore.YELLOW}{expected}{Style.RESET_ALL}")
print('Press enter to "submit" (or ctrl+c to abort)')
print()

accepted = False
tries = 0
start = time.perf_counter()

def edit_distance(a, b):
    n, m = len(a), len(b)
    dp = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(n + 1):
        dp[i][0] = i
    for j in range(m + 1):
        dp[0][j] = j
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if a[i - 1] == b[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])
    return dp[n][m]

def submit():
    global accepted
    global tries
    while not accepted:
        debug = input()
        got = normalize(tmpfile)
        equal = got == expected
        verdict = f"{Fore.GREEN}AC{Style.RESET_ALL}" if equal else f"{Fore.RED}WA{Style.RESET_ALL}"
        message = [f"{clear}submitted:", verdict]
        if args.debug:
            message.append(f"(distance: {edit_distance(got, expected)})")
            if debug == "ac": equal = True
            if debug == "wa": equal = False
        print(*message)
        if equal:
            accepted = True
        else:
            tries += 1

threading.Thread(target=submit, daemon=True).start()

elapsed = 0
penalty = 0
while not accepted:
    elapsed = time.perf_counter() - start
    penalty = args.penalty * tries
    print(f"time: {elapsed + penalty:.2f}s (try: {tries+1})", end="\r", flush=True)
    time.sleep(0.075)
print()
print(f"time: {elapsed + penalty:.2f}s (tries: {tries+1})")
print(f"speed: ~{len(expected) / elapsed:.2f} chars per second", end="")
if penalty:
    print(f", ~{len(expected) / (elapsed + penalty):.2f} with penalty", end="")
print()
