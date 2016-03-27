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

``` Bash
.../iniparser$ make install
```

Will install `libiniparser.a` in `/usr/lib/iniparser/` and `include/iniparse.h`
in `/usr/include/iniparser/`. Default installation prefix can be changed
exporting `INSTALL_PREFIX` before running `make install`.

## How to

This library reads the INI file line by line from top to bottom. When a
key-value pair is read, callback function is called. Data is only available
during the callback. Custom callback function must provide the way to store the
data in order to maintain it. It gets a custom data structure pointer as a
parameter for this purpose.

Check the example file in the `examples` directory.
