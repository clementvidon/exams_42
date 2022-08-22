
#           EXAM 42

## Summary 

This repository is intended to help me **learn** functions by heart for the 42 exams.
It also aims to **improve** these functions at the same time.

For this purpose I developed the following method:

At **level 1** we find the different 42 exams `rank02 rank03 rank04 ...` as well
as the `tools` folder that contains my exam `vimrc` or debugging tools to quickly test functions improvement.

At **level 2** we find the different subjects that we can meet during the exam.

At **level 3** we find the core of the method, three source files:
- `base.c` functional starting point, *must not be modified*.
- `check.c` the improvement file, with annotation and modifications allowed.
- `try.c` this file will be used and reused to code and recode the function by
  heart.
- (optionally) a `doc` and `test` folders.

## Method 

The workflow is the following:
1. recode the function into `try.c`
2. debug `try.c`
3. diff `try.c` and `check.c` (*vim users tip: `:h vimdiff` and look for `do` and `dp`*)

***LEARN***

4. update `check.c` with the mistakes found in `try.c` and document with a
  `TODO` comment

      ssize_t r; // TODO ssize_t instead of long

***IMPROVE***

4. update `check.c` with comments that keep a tracks of mistakes found in
  `try.c`, the number preceding the `XXX` (here `2`) indicate that this mistake
  has been done for twice `try.c`

      static char *temp; // 2 XXX static keyword missing

Before the exam I can **check my most common mistakes** using `check.c`.
After the exam I can **improve my function** using `check.c`.
