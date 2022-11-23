
    cat | ls;

0. *MAIN*

    fdcpy   = STDIN

1. *FT_PIPE* (write or read & write)

    *fdcpy  = STDIN         <inherited from main>

    fd[2]   = pipe

   >> CHILD << (write)

    close   PIPEIN

    STDOUT  => PIPEOUT      STDOUT points to PIPEOUT
    close   PIPEOUT

    STDIN   => *fdcpy       STDIN  points to *fdcpy
    close   *fdcpy

> Exec:
> | (STDIN is fdcpy) STDIN->PRG->STDOUT

   >> PAREN << (read)

    close   PIPEOUT
    close   *fdcpy
    *fdcpy  = PIPEIN        *fdcpy become PIPEIN

2. *FT_PROG*  (read)

    fdcpy  = PIPEIN         <inherited from ft_pipe>

   >> CHILD <<

    STDIN   => fdcpy        STDIN  points to fdcpy
    close   fdcpy

> Exec:
> | (STDIN is fdcpy) STDIN->PRG->STDOUT

   >> PAREN <<

    close   fdcpy

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
























