# sudoku-c

CLI sudoku game made in C.

#### Known problems

    - When input is a letter infinite loop happens.  
    - Not very efficient sudoku creation algorithm. For 16x16 with medium difficulty (or higher) sudoku board is generating slowly.


### start command
> `gcc -o sudoku sudoku.c cli.c -lm`

![](./meme.mp4)

<video width="320" height="240" controls>
  <source src="./meme.mp4" type="video/mp4">
</video>