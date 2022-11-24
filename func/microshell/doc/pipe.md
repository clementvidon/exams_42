
    cat | ls;

# #### #
# MAIN #
# #### #

    fdcpy   = STDIN

*STDIN=0*
*STDOUT=1*
*fdcpy=3*

# ####### #
# FT_PIPE #
# ####### #

    *fdcpy  => STDIN    3       <INHERITED FROM MAIN [PREV PIPE]>

    p[2]    = pipe      4,5

*STDIN=0*
*STDOUT=1*
*fdcpy=3*
*p[0]=4*
*p[1]=5*

#   PIPE CHILD
# ############

    close   p[0]        4X

    STDOUT  => p[1]     1⇒5     STDOUT points to p[1]
    close   p[1]        5X

    STDIN   => *fdcpy   0       STDIN  points to *fdcpy
    close   *fdcpy      3X

*STDIN=0*
*STDOUT=1* ⇒ p[1]
*fdcpy=X*
*p[0]=X*
*p[1]=X*

- ***Pipe Child*** output to PIPE OUT
- ***Pipe Child*** input from * fdcpy (`cat | cat | ls`)
- ***Pipe Child*** execute (`[fdcpy >] exec > PIPE OUT`)

#   PIPE PAREN
# ############

    close   p[1]        X5
    close   *fdcpy      X3
    *fdcpy  = p[0]      3→4     *fdcpy become p[0]

*STDIN=0*
*STDOUT=1*
*fdcpy=4*
*p[0]=4*
*p[1]=X*

- ***Pipe Parent*** saves PIPE IN into * fdcpy

# ####### #
# FT_PROG #
# ####### #

    fdcpy  = p[0]       4       <INHERITED FROM FT_PIPE>

*STDIN=0*
*STDOUT=1*
*fdcpy=4*

#   PROG CHILD
# ############

    STDIN   => fdcpy    0       STDIN  points to fdcpy
    close   fdcpy       4X

*STDIN=0*  ⇒ fdcpy
*STDOUT=1*

*fdcpy=4*  X

- ***Prog Child*** input from fdcpy
- ***Prog Child*** execute

#   PROG PAREN
# ############

    close   fdcpy

*STDIN=0*  X
*STDOUT=1*
*fdcpy=4*

---------------------------------------------------------------------

WRITE TO PIPE

   Prev commands:
     dup: Pipe ← StdOut
     cmd: … ← I/O → |

   Last command:
     dup: File1 ← StdOut
     cmd: … ← I/O → File2

READ FROM PIPE

   First command:
      dup: File0 ← StdIn
      cmd: File0 ← I/O → …

   Next commands:
      dup: Pipe ← StdIn
      cmd: | ← I/O → …


- ***Pipe Parent*** saves PIPE IN into * fdcpy

- ***Pipe Child*** output to PIPE OUT
- ***Pipe Child*** input from * fdcpy (`cat | cat | ls`)
    fdcpy = PIPE IN from prev ft_pipe parent ?
    parce que les multi pipes sont des poupées russes ?
- ***Pipe Child*** execute (`[fdcpy >] exec > PIPE OUT`)

- ***Prog Child*** input from fdcpy
- ***Prog Child*** execute


EXAMPLE TODO

  "echo a | cat | grep a"

  PIPE1:
   paren
    close PIPE1 OUT (pour pas recevoir l'output du child)
    fdcpy = PIPE1 IN

   child
    close PIPE1 IN (unused)

    STDIN = fdcpy
    (echo a)> PIPE1 OUT (STDOUT redirect to PIPE1 OUT)

  PIPE2:
   paren
    close PIPE2 OUT (pour pas recevoir l'output du child)
    fdcpy = PIPE2 IN

   child
    close PIPE2 IN (unused)

    STDIN = fdcpy (PIPE1 IN)
    PIPE2 IN >(cat)> PIPE2 OUT (STDOUT redirect to PIPE2 OUT)


  PROG:
   paren
   child
