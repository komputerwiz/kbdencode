# kbdencode
*A keyboard layout encoder filter: type input using a certain keyboard layout, see the output as if you were typing in another layout.*

I use the [Dvorak keyboard layout][dvorak] ( you should too :) ), and I often fumble around the <del>traditional</del> <ins>antiquated</ins> QWERTY layout if I need to quickly use someone else's computer to show him or her something. I could add the Dvorak Keyboard to his or her user preferences, but `kbdtools` presents an alternate solution: I can type what I want on a QWERTY keyboard as if it were a Dvorak keyboard, and then convert the gibberish into what I had typed.

## Installation
`kbdencode` is built with [GNU Autotools][]. The easiest way to install `kbdencode` is to download a distribution package from the [official website][kbdencode] or the Releases tab on GitHub. Alternatively, you can use Autotools to set up this repository:

```
autoreconf --install
```


At this point, the build process is identical to that of a distributed package:

```
./configure
make
make install
```

**NOTE:** `kbdencode` has a build dependency on the [Boost][] [program_options][boost-program-options] library by Vladimir Prus for parsing command-line options.

The default installation directory is `/usr/local`, and the last command might require super user permissions: `sudo make install`.

### Build Hints

To install kbdencode to a custom directory (e.g. under the `.local` directory in your home directory), use the standard `--prefix` flag:

```
./configure --prefix=$HOME/.local
```

While this is not relevant for `kbdencode` (since it has only one source file), the build process can be greatly optimized by using the `-jN` flag on the `make` command. This specifies the number of parallel build threads that can be executed simultaneously. For example, an Intel Core i7 quad-core processor can run up to 8 threads:

```
make -j8
```


## Usage
As it suits my needs, the default encoding direction is `--from=qwerty`, `--to=dvorak`. At present, the only command line options are `--from=<layout>`,   `--to=<layout>`, and `--help`; and the only named layouts are `qwerty` and `dvorak`. Instructions for specifying additional layouts are listed in the next section.

### As a file decoder
Files to decode can be specified as extra command-line arguments:

```console
user@host:~ % kbdencode --from=qwerty --to=dvorak file1.txt file2.txt
```

### As a command-line filter
`kbdencode` can handle text input through the standard input stream:

```console
user@host:~ % echo "jdppsw ,soph!" | kbdencode
hello, world!
```

This makes it possible (but somewhat infeasible) to use a shell at the command line:

```console
user@host:~ % kbdencode | zsh
p;
Destkop    Downloads  Music     Videos
Documents  Music      Pictures
ih Hs,lpsah;
r,h
/home/user/Downloads
,udk jkkrZ[[,sohrod;;esou[pakd;kekaoeu/
--2014-03-18 01:50:36--  http://wordpress.org/latest.tar.gz
Resolving wordpress.org... 66.155.40.250, 66.155.40.249
Connecting to wordpress.org|66.155.40.250|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 5869727 (5.6M) [application/x-gzip]
Saving to: 'latest.tar.gz'

100%[=======================================================================================>] 5,869,727   3.37MB/s   in 1.7s   

2014-03-18 01:50:39 (3.37 MB/s) - 'latest.tar.gz' saved [5869727/5869727]
^D
user@host:~ %
```

### As a cryptogram cipher
If you want to type a message to a friend so that no one can read it over your shoulder, you can type the message into a file using a different keyboard layout.

    -- Encoded --
    XrxS Yd. xci xrq ru e.ncjcrgo jdrjrnay. co cb yd. jaxcb.y b.qy yr yd.
    p.upci.payrpv D.nl frgpo.nuw xgy erb-y n.y >k. o.. cyv [Ancj.

    -- Decoded --
    Bob: The big box of delicious chocolate is in the cabinet next to the
    refrigerator. Help yourself, but don't let Eve see it. -Alice

**NOTE:** This cipher is not very secure. Please do not use this method to encode sensitive information.


## Adding new layouts
Layouts are specified as an initializer list in the `src/kbdencode.cc` file. Layouts can also be specified as values to the `--to` and `--from` options. The format is simple:

1. type all the keys (without holding <kbd>Shift</kbd>) starting from the top-left (the backtick <kbd>`</kbd> symbol on a QWERTY keyboard), working left-to-right, and ending at the bottom-right (the forward-slash <kbd>/</kbd> key on a QWERTY keyboard).
2. Repeat the process, but hold the <kbd>Shift</kbd> key down for all keys.
3. Be sure to escape any special characters as necessary.

For example, the QWERTY map is <code>`1234567890-=qwertyuiop[]\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:"ZXCVBNM<>?</code>

Future support may be added to support some type of configuration file for simpler entry and recognition of new keyboard maps.


## License
`kbdencode` is licensed under the GPLv2 license. Full license details are available in the LICENSE file or at https://www.gnu.org/copyleft/gpl.html.

If the GPL presents a problem for you in any way, please let me know and I will consider relicensing the software for you.

[kbdencode]: http://komputerwiz.net/kbdencode
[dvorak]: http://en.wikipedia.org/wiki/Dvorak_Simplified_Keyboard
[GNU Autotools]: http://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html
[Boost]: http://www.boost.org
[boost-program-options]: http://www.boost.org/doc/libs/1_55_0/doc/html/program_options.html
