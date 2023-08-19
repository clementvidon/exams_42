
#           EXAMS 42

## Summary

This repository is intended to help me to **learn** functions by heart for the
42 exams.  It also aims to **improve** these functions at the same time.  For
this purpose I developed the following method.

At level one we find `tool` folder that contains my minimal exam `config`, the
default 42 vimrc, and debugging tools to quickly check the improvements.

Inside the `func` directory there is a folder for each function that we can
encounter during the exams.

Inside each of these folder we find the core of the method, three source files:
- `base.c` functional starting point, *must not be modified*.
- `check.c` the improvement file, with annotation and modifications allowed.
- `try.c` this file will be used and reused to code and recode the function by
  heart.
And (optionally) a `doc` and `test` folders.

## Method

The workflow is the following:
1. recode `base.c` function into `try.c`
2. debug `try.c`
3. diff `try.c` and `base.c` into `check.c`

> **HINT** Vim users will like `:h vimdiff`, the `do` and the `dp` commands.

***LEARN***

4. update `check.c` with the mistakes found in `try.c` and document with a
  `TODO` comment

        ssize_t r; // TODO ssize_t instead of long

***IMPROVE***

4. update `check.c` with comments that keep a track of mistakes found in
   `try.c`, the number preceding the `XXX` ( here `2` ) indicates indicates the
   number of times the error has been done during `try.c` attempts.

        static char *temp; // 2 XXX static keyword missing

***THUS***

Before the exam **I can check my most common mistakes** using `check.c`.
After the exam **I can improve my function** using `check.c`.
