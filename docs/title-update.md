# Making `default_patched.xex` (slopped guide)

## What you need

| File | Size (bytes) | SHA1 | SHA256 |
|---|---|---|---|
| `default.xex` (disc) | 19,447,808 | `090CCB0E7F5C7C2F659301FAC0859CEFB1FF0E3A` | `8959C449E382661D29B8EA479C685F506CD5BD3ECA40B3D73A51CC10F281069F` |
| `default.xexp` (title update 5) | 2,504,704 | `0C9DDCACD74DC89342FCE063A91CDD608F9E942C` | `A5E49FC1FF7F6F65E6F95A7B5C4B9392BB9E38674D1237AC0E2F0149D05929D7` |
| `default_patched.xex` (result) | 19,316,736 | `EC7B163617CD725F50B0CCA665AAF943F9BC6D8A` | `89C31820DD104DF2A8A7D86E8D0AF15650DD7DDF304C9BE4F542689F1B58B0A6` |

- **`default.xex`**: at the root of your Crackdown 2 disc (title ID `4D5308BC`). Extract the disc image's files with an
  ISO extractor such as exiso.
- **`default.xexp`**: title update 5. Its `Version.txt` reads `"15.10.30.57636"`.
  The update itself is an STFS package: extract it with an STFS tool (wxPirs, Le Fluffie, Velocity), and `default.xexp` is at its
  root, beside `Version.txt`. If you installed the update into Xenia, Xenia has already extracted it, to
  `<Xenia>\content\0000000000000000\4D5308BC\000B0000\TU_16L625S_0000004000000.0000000000181\default.xexp`.
- **XexTool v6.6** by xorloser (`xextool.exe`, build of 23 September 2013). It is not part of this repository.

Check both inputs before you patch (`certutil` comes with Windows):

```
certutil -hashfile default.xex SHA1
certutil -hashfile default.xexp SHA1
```

## Apply the update

With `default.xex` and `default.xexp` in the current folder:

```
xextool -p default.xexp -o default_patched.xex default.xex
```

XexTool ends with `Successfully wrote altered xex to default_patched.xex` and `default_patched.xex is retail encrypted
uncompressed.` ("uncompressed" is its name for the basic compression the original file uses, so it is expected).

- Always give `-o`. Without it, XexTool rewrites `default.xex` in place.
- Give no other option. The ones that change the output (`-c`, `-e`, `-m`, `-r`, `-u`, `-s`) write a different file,
  and the tools refuse it even though the game code inside is the same.
- XexTool 6.6 with exactly this command is the one way known to give the expected file. Another patcher may produce the
  same game image in a file with a different hash.

## Check the result

```
certutil -hashfile default_patched.xex SHA1
```

It must print `ec7b163617cd725f50b0cca665aaf943f9bc6d8a`. Then continue with setup:

```
py -I tools\cd2.py setup <path>\default_patched.xex
```

`setup` checks the same hash and refuses any other file, the unpatched `default.xex` included.

## If a hash differs

- **`default.xex`**: not the disc build title update 5 applies to. The update's delta patch starts from version
  0.0.0.1, the disc's.
- **`default.xexp`**: a different title update. Title update 5 takes the game to version 0.0.5.1.
- **Both inputs match, the result does not**: a different XexTool version, or an extra option.
