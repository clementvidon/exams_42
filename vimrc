"+Import 42 conf here-+
se nocp
filetype plugin indent on
se sw=4 ts=4 ci
"+--------------------+
se ru sc udf hi=999 ttm=0 tw=80
sy on
nn <space>w <c-w>
nn se :e *
nn ss :b#<CR>
nn ; :
nn : ;

no <space>n :w<CR>:!clear; norminette %<CR>
no <space>= mmgo=G:sil! %s/\s\+$//e<CR>`mzz
no <space>8 :wa\|lc %:h<CR>
            \
            \:sil !clang -Werror -Wall -Wextra -fsanitize=address *.c 2>err<CR>
            \:cfile err<CR>:cw5<CR>
            \:!clear;./a.out\|cat -e<CR>
