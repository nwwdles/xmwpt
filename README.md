# xmwpt

Make a window pass clicks through (e.g. if you want to have a video open in a corner but don't want it to block clicks).

Should work with KDE and standalone WMs, doesn't seem to work with Gnome.

```txt
xmwpt [-h|-v|-s WIN|-u WIN]

OPTIONS:
    -h            show this help
    -v            show version
    -s WIN        set passthrough shape for window WIN
    -u WIN        unset shape
```

Example:

```sh
$ xmwpt -s $(xdotool getactivewindow)
hiding window 111149929
```
