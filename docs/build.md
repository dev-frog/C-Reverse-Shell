---

## 🛠️ `docs/build.md`

````markdown
# Cross-Compilation from macOS

Your Mac (Apple Silicon or Intel) is the development host. Binaries are
cross-compiled. **You cannot compile a single binary that runs on both
Linux and Windows** — you build two separate binaries.

## Install Toolchain

```bash
# macOS build tools
xcode-select --install

# Windows cross-compiler
brew install mingw-w64

# Linux compilation via Docker (recommended for glibc-matching binaries)
brew install --cask docker
```
````

## Build Linux Target

Recommended: inside Docker, so the produced binary matches your target VM's `glibc`.

```bash
docker run --rm -v "$PWD":/src -w /src gcc:13 bash -c \
  "apt-get update -qq && apt-get install -y -qq make >/dev/null && make TARGET=linux"
# output: build/rshell-linux

```

## Build Windows Target

```bash
make TARGET=windows
# output: build/rshell.exe


```

Under the hood, `make` invokes:

```bash
x86_64-w64-mingw32-gcc -Wall -Wextra -O2 -Iinclude \
  src/main.c src/net_win.c src/shell_win.c \
  -o build/rshell.exe -lws2_32
```

## Verifying Binaries

```bash
# Linux
file build/rshell-linux
# ELF 64-bit LSB pie executable, x86-64, ...

# Windows
file build/rshell.exe
# PE32+ executable (console) x86-64, for MS Windows

```
