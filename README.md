# ft_ls

`ft_ls` is clone project of `ls` command which show file and directory list.
Implementing `ls`, you can learn how to read directory and file's meta data with file system call `readdir`, `lstat` and `readlink`.

<br/><br/>

## Requirements

`ft_ls` use [libft](https://github.com/jebae/libft), [ft_printf](https://github.com/jebae/ft_printf.git)

```
# download libft
git clone https://github.com/jebae/libft.git

# download ft_printf
git clone https://github.com/jebae/ft_printf.git

# directory structure
root/
 libs/
  libft
  ft_print
```

<br/><br/>

## Install

```
make
```

<br/><br/>

## Usage

```
./ft_ls [-lRart] [file...]
```

<br/><br/>

## Features

### multi arguments

`ft_ls` could list files and directories not only one target but multiple.

```
./ft_ls foo bar a/b
```

### flags

- `l`: List files and directories in detail.
e.g. `-rw-r--r--   1 jebae  staff     1547 Jan 28 11:08 Makefile`

- `R`: Recursively read subdirectories.
- `a`: List all files include hidden files
- `r`: List in reverse order. Default order method is ascending lexicographical.
- `t`: List in order of most recent updated.
