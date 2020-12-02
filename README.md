# Codesim

## 前言
很久没有使用C++进行开发了，或者说之前也没有使用过C++去写一些大型项目。在软件工程这门课上，要求开发一个代码相似度检测工具。大体思路都是需要用Clang来解析AST的，尽管在Python和Go等语言中都可以通过Cython或者Cgo来使用libclang，但是还是原生的C++更加稳定。因此我使用C++来进行开发。

## 项目依赖
``` shell
$ llvm-config  --version
10.0.0
$ clang --version
clang version 10.0.0-4ubuntu1 
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
$ g++ --version
g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
使用其他版本的llvm和clang应该也可以。

## 编译运行
``` shell
# 编译生成codesim可执行文件
make
# codesim的使用方法
$ ./codesim -h
SYNOPSIS
        ./codesim <input file1> <input file2> [-v] [-h]

OPTIONS
        -v, --verbose
                    verbose(show more details)

        -h, --help  help(guide how to use codesim)
```

## 依赖安装
``` shell
sudo apt-get insatll llvm-dev clang libclang-dev
```

