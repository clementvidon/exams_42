
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

- ***Pipe Child*** dup PIP OUT in STDOUT
- ***Pipe Child*** dup fdcpy in STDIN (`cat | cat | ls`)
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

- ***Prog Child*** dup fdcpy in STDIN
- ***Prog Child*** execute

#   PROG PAREN
# ############

    close   fdcpy

*STDIN=0*
*STDOUT=1*
*fdcpy=4* X

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





# ####### "echo a | cat | grep a" #######

TODO check les close / open, not needed etc.

    dup2 (PIPEOUT, STDOUT);
> Dup2 = dup to = PIPEOUT is duplicated to STDOUT = redirect STDOUT to PIPEOUT

TODO

try fork dans le parent pour 2 enfants et changer le parsing du while pour que
ca marche comme ca 2 while pour exec un pipe (et pas de ft_prg) au lieu de 3.

et ft_prg uniquement si pas de pipe.

##  MAIN()

00. *Init prevpin with STDIN as we don't have a previous PIPEIN*
    prevpin = dup (STDIN);
> prevpin is allocated a new fd that refer to STDIN.

STDIN   = 0 (open)
STDOUT  = 1 (open)
prevpin = 3 (open, points to STDIN)

##  FT_PIPE()  "echo a | cat →"

01. *Create PIPEIN and PIPEOUT*
    pipe (p);

02. *Creates a child*
    pid = fork ();

STDIN   = 0 (open)
STDOUT  = 1 (open)
prevpin = 3 (open, points to STDIN)
PIPEIN  = 4 (open)
PIPEOUT = 5 (open)

###     CHILD (new proc)

03. *Close PIPEIN*
    close (PIPEIN);
> PIPEIN unused
TODO ferme pour bloquer le stream ?

04. *Connect PIPEOUT to STDOUT*
    dup2 (PIPEOUT, STDOUT);
    close (PIPEOUT);
> Redirect STDOUT to PIPEOUT
> PIPEOUT not needed anymore

05. *Connect prevpin to STDIN*
    dup2 (prevpin, STDIN);
    close (prevpin);
> Redirect STDIN to prevpin
> Useless for the first command because prevpin is STDIN.
> prevpin not needed anymore

06. *EXEC*
    execve (cmd[0], cmd, env);
> STDIN   → cmd → STDOUT
> prevpin → cmd → PIPEOUT
> STDIN   → cmd → PIPEOUT

STDIN   = 0 (open)
STDOUT  = 1 (open, redirected to PIPEOUT)
prevpin = 3 (closed)
PIPEIN  = 4 (closed)
PIPEOUT = 5 (closed)

###     PARENT (main proc)

03. *Close PIPEOUT*
    close (PIPEOUT);
> PIPEOUT unused
TODO ferme pour bloquer le stream ?
TODO Pour ne pas recevoir l'output du child?

04. *Update prevpin*
    close (prevpin);
    *prevpin = PIPEIN;
    prevpin = PIPEIN (on sauvegarde PIPEIN)
> prevpin hold a copy the current PIPEIN.
TODO close prevpin not to received the Child output?

TODO exec happened? is it waiting that in/out are connected before to stream?

STDIN   = 0 (open)
STDOUT  = 1 (open)
prevpin = 4 (open, same as PIPEIN)
PIPEIN  = 4 (open, same as prevpin)
PIPEOUT = 5 (closed)

##  FT_PIPE()  "→ cat | grep a →"

11. *Create PIPEIN and PIPEOUT*
    pipe (p);

12. *Creates a child*
    pid = fork ();

STDIN   = 0 (open)
STDOUT  = 1 (open)
prevpin = 4 (open)
PIPEIN  = 3 (open)
PIPEOUT = 5 (open)

> PIPEIN and PIPEOUT are assigned fd 3 and 5 because it was the closest
> available since fd 4 has not been closed yet.

###     CHILD (new proc)

13. *Close PIPEIN*
    close (PIPEIN);
> PIPEIN unused
TODO fermé pour bloquer le stream ?

14. *Connect PIPEOUT to STDOUT*
    dup2 (PIPEOUT, STDOUT);
    close (PIPEOUT);
> Redirect STDOUT to PIPEOUT
> PIPEOUT not needed anymore

15. *Connect prevpin to STDIN*
    dup2 (prevpin, STDIN);
    close (prevpin);
> Redirect STDIN to prevpin
> Useful now to redirect STDIN to PREV_PIPEIN.
> prevpin not needed anymore

16. *EXEC*
    execve (cmd[1], cmd, env);
> STDIN       → cmd → STDOUT
> prevpin     → cmd → PIPEOUT
> PREV_PIPEIN → cmd → PIPEOUT

STDIN   = 0 (open, redirected to PREV_PIPEIN)
STDOUT  = 1 (open, redirected to PIPEOUT)
prevpin = 4 (closed)
PIPEIN  = 3 (closed)
PIPEOUT = 5 (closed)

###     PARENT (main proc)

13. *Close PIPEOUT*
    close (PIPEOUT);
> PIPEOUT unused
TODO fermé pour bloquer le stream ?
TODO Pour ne pas recevoir l'output du child?

14. *Update prevpin*
    close (prevpin);
    *prevpin = PIPEIN;
    prevpin = PIPEIN (on sauvegarde PIPEIN)
> prevpin hold a copy the current PIPEIN.
TODO close prevpin not to received the Child output?

TODO exec happened? is it waiting that in/out are connected before to stream?

STDIN   = 0 (open)
STDOUT  = 1 (open)
prevpin = 3 (open, same as PIPEIN)
PIPEIN  = 3 (open, same as prevpin)
PIPEOUT = 5 (closed)

##  FT_PROGRAM()

###     CHILD (new proc)

21. *Connect prevpin to STDIN (where prevpin is equal to PREV_PIPEIN)*
    dup2 (prevpin, STDIN);
    close (prevpin);
> Redirect STDIN to prevpin
> prevpin not needed anymore

22. *EXEC*
    execve (cmd[2], cmd, env);
> STDIN       → exec → STDOUT
> prevpin     → exec → STDOUT
> PREV_PIPEIN → exec → STDOUT

STDIN   = 0 (open, redirected to PREV_PIPEIN
STDOUT  = 1 (closed)
prevpin = 3 (closed)

###     PARENT (main proc)

21. *Close prepvin*
    close (prevpin);
> P

22. *Wait for children*
> while (wait (NULL) != -1);

STDIN   = 0 (closed)
STDOUT  = 1 (closed)
prevpin = 3 (closed)






GPT
    int main() {
    // Create an array to store the pipes
    int pipes[MAX_PIPES][2];
    int num_pipes = 0;

    while (1) {
        // Create a new pipe
        pipe(pipes[num_pipes]);

        // Fork the first program and redirect its output to the new pipe
        pid_t pid = fork();
        if (pid == 0) {
        // This is the child process
        dup2(pipes[num_pipes][1], 1); // redirect stdout to the new pipe
        close(pipes[num_pipes][0]);   // close unused end of the new pipe
        execlp("program1", "program1", NULL);
        } else {
        // This is the parent process
        // Fork the second program and redirect its input to the new pipe
        pid_t pid2 = fork();
        if (pid2 == 0) {
            // This is the child process
            dup2(pipes[num_pipes][0], 0); // redirect stdin to the new pipe
            close(pipes[num_pipes][1]);   // close unused end of the new pipe
            execlp("program2", "program2", NULL);
        }
        }

        // Increment the number of pipes
        num_pipes++;
    }
    }


