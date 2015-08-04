utf8-to-unicode
======

介绍
------
本程序可以打印出所给字符的 Unicode 编码（以 \uXXXX 的形式），用法：

> `utf8-to-unicode <一些字符> [更多的字符] ...`

编译
------
使用 make 工具进行编译。默认编译器为 gcc，如想更换，请在 make 的命令行指定。

> `make # 或者 make CC=clang，以此类推`

帮助除错
------
本程序仍然有 bug 以至于无法使用，如果你有任何想法，欢迎PR。