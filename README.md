# numtoeng

## Description

This is intended to be a small command line utility to convert decimal numbers into English words.
I will probably consider adding more conversions in the future, but this is all I will be doing for now.

## Usage

The general usage for this program is as follows:

```sh
numtoeng [ FLAGS ... ] ( ARGUMENTS ... )
```

This program then takes all the numeric arguments and converts them to English words, separated by a newline.

Numeric arguments are expected to fit one of the following regexes:

```js
(-|\+)?[0-9]+                            // General Integers
(-|\+)?([0-9]+\.[0-9]*)|([0-9]*\.[0-9]+) // Floating Points
```

For example, this program will parse `-.361000`, but not `+.`. If the program encounters something that it cannot parse, then it will output `invalid number: 'NUMBER'` to `stdout`.
This program cannot handle digits over MAX_INT characters in length. If such a number is encountered, then the program will output `long num` if the `--stdin` flag is not given. In the case that the flag is, then undefined behavior occurs. This is set to be patched in the future.

## Flags

All flags start with `--` to avoid ambiguity. Flags must be passed to the program before any arguments, or else they will be interpreted as regular numeric arguments. If the program is provided with conflicting or unknown flags, then it will immediately halt. Having multiple flags of the same type is considered conflicting, unless specified.

| Flag | Description |
| ----------------- | ---------------------------------------------------------------------------------- |
| `--stdin`<br>`--` | Parses input from `stdin`, with numbers assumed to be separated by `\n`, `\r`, or `\0`. The program will ignore empty lines. Silently ignores all arguments provided directly to the command. |
| `--invalid`<br>`--!` | Prints all messages for invalid numbers (e.g. too long, improper format) to `stderr` instead of `stdout`. |
| `--labels`<br>`--#` | Labels all output with the index which with they were given, starting with 1. For example, `numtoeng --# 1 2` would output:<br><br><pre><code>1: one<br>2: two</code></pre>Mutally exclusive with `--labels-0`. |
| `--labels-0`<br>`--#0` | Like `--labels`, but indexing starts from 0 instead of 1. For example, `numtoeng --#0 1 2` would output:<br><br><pre><code>0: one<br>1: two</code></pre>Mutally exclusive with `--labels`. |
