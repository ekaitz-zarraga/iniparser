# INI file parser

Simple and direct INI parser in C.

- It allows key-value pairs separated by column (`:`) or equals (`=`).

- It allows hashtag (`#`) or semicolon (`;`) for comments.

- Does not allow inline comments.

## Compilation

``` Bash
.../iniparser$ make
```

Will create `libiniparser.a` file in the root directory. Link it and include
header files as usual.

> make install is a TODO, but if you want to install, copy `libiniparser.a`
> file to `/usr/lib` or similar and `include/iniparser.h` to `/usr/include`.
> Use it by including the header file and linking the library in your project.


## How to

This library reads the INI file line by line from top to bottom. When a
key-value pair is read, callback function is called. Data is only available
during the callback. Custom callback function must provide the way to store the
data in order to maintain it. It gets a custom data structure pointer as a
parameter for this purpose.

Check the example file in the `examples` directory.
