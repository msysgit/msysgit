This is the copy of [msysGit](https://github.com/msysgit/msysgit) that ships
with [GitHub for Windows](http://windows.github.com/).

# How to make changes

1. Make your changes on the `devel` branch
2. Run `msys.bat`
3. Inside the bash shell, run `ghfw-release.sh`

This will build a portable Git release and check it in to the `PortableGit`
branch. Now you can push your changes to `origin`.

# Repository structure

This repository has two important branches: `devel`, and `PortableGit`.

## `devel`

This is the main branch of the repository, and is periodically synced with
[msysgit/msysgit@devel](https://github.com/msysgit/msysgit/tree/devel). This
branch contains all of the msysGit source code, Git source code, Git
documentation, and supporting build scripts.

## `PortableGit`

This branch is generated from the `devel` branch. Changes should never be made
by hand to this branch, except to the `.gitattributes` and `.gitignore` files
at the root of the repository.
