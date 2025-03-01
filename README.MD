# Project Documentation

## Table of Contents
- [Introduction](#introduction)
- [License](#license)
- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
- [Usage](#usage)

## Introduction
This project is a simple code generator for creating Java classes for models, services, and repositories based on Spring framework conventions. It reads configuration from a file and generates the necessary files in the specified directory structure.

## License
This project is licensed under the GNU General Public License v3.0. See the [LICENSE](#license) file for details.

## Getting Started

### Prerequisites
- GCC compiler
- Make utility (optional)

### Installation
To compile the project, run the following command:
```bash
cc -Wall -Wextra -std=c99 -O2 -o <name_of_executable> main.c
```
Or:
```bash
gcc main.c -o <name_of_executable>
```

### Making it a system wide command

## On windows:
```
1) compile the program
2) go to modify system variable: relative to the system or to the account
3) if relative to the system go to environment variable (if account skip this)
4) Select path -> modify
5) New -> paste the directory where the .exe is located
```

## On linux:
```
sudo cc -Wall -Wextra -std=c99 -O2 -o bin/<name_of_executable> main.c
```
Or:
```
cc -Wall -Wextra -std=c99 -O2 -o bin/<name_of_executable> main.c
sudo mv <name_of_executable> bin/
```

## On mac os
```
sudo cc -Wall -Wextra -std=c99 -O2 -o /usr/local/bin/<name_of_executable> main.c
```
Or:
```
cc -Wall -Wextra -std=c99 -O2 -o <name_of_executable> main.c
sudo mv <name_of_executable> /usr/local/bin/
```


## Usage

for help:
```bash
./<name_of_executable> -h
```

