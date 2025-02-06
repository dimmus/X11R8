# xgetres

xgetres is a simple utility which prints the value of an X resource.

## Example

    $ cat ~/.Xresources
    simple: 1
    *wildcard: 2
    $ xgetres simple
    1
    $ xgetres foo.wildcard
    2
