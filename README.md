# xmwpt

Make a window pass clicks through.

```txt
xmwpt [-h|-v|-s WIN|-u WIN]
example:
    xmwpt -s WIN        set passthrough shape for window WIN
    xmwpt -u WIN        unset shape
```

Example:

```sh
$ xmwpt -s $(xdotool getactivewindow | sed 's/.*://')
hiding window 111149929
```
