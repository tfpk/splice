# Splice

## Introduction

Splice is a tool to take a given input and a binary; and join together the
input and the output in the same way a user might see on a terminal.

In other words, splice emulates what a user would see on a cooked tty.

## Example

Take this simple C program, which scans in 3 numbers:

``` c++
#include <stdio.h>

int main(void) {

    int a, b, c;
    printf("Enter one number: ");
    scanf("%d", &a);
    printf("Enter another number: ");
    scanf("%d", &b);
    printf("Enter a last number: ");
    scanf("%d", &c);
    
    printf("%d + %d + %d = %d\n", a, b, c, a + b + c);

    return 0;
}
```

Given the input `1\n\2n3\n`, a tty might show

``` sh
$ ./my_program
Enter one number: 1
Enter another number: 2
Enter a last number: 3
1 + 2 + 3 = 6
```

However, on a terminal, it might look like:

``` sh
Enter one number: Enter another number: Enter a last number: 1 + 2 + 3 = 6
```

`splice` will print out to the terminal something similar to the tty.

## Usage

Before using splice, ensure that you have installed `unbuffer` program.
Usually this is part of the `expect` package.

You will also need to run the `make` command in the base directory of
this repository. This will create the `.so` object in `bin/`.

Then, run it as follows:

``` sh
$ echo -e "1\n2\n3\n" | ./splice my_program arg1 arg2
```

It also takes the following arguments:

 - `--start-delimiter <string>`

This is what gets printed before the input you've given.

 - `--end-delimiter <string>`

This is what gets printed after the input you've given.

 - `--delay <float in ms>`
 
This is how long we wait between inputs. I am assuming the reason this
is needed is because if you provide all the inputs at once they get
grouped together. It seems that about 10ms is enough, but you may need
to turn it up.

## Caveats

At the moment, splice is dumb. It assumes you only want to see
things read from file descriptor 0, and write to file descriptor 1.
A better program would track when `dup2` has cloned a file
descriptor, or opened `/dev/stdin`.

