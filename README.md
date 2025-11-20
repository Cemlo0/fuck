# fuck
This tool make it possible to say *fuck* to your command prompt.

---

## Overview
`fuck` is a small CLI tool that reads and displays **rude** responses corresponding to a command-line argument from a configuration file.

The tool returns a witty (or simply vulgar) message based on the specified target. It aims to offer a small, **abrupt** release for your daily frustrations.

Path recommended.

<img width="236" height="111" alt="image" src="https://github.com/user-attachments/assets/66502bfe-f6a5-41e6-bc59-7b4204285d56" />

Just that.

## `fuck.txt` File Format
The response data is stored in the fucks.txt file, located in the same directory as the executable, in the format: `key:value`.
|Format|Description|
|---------|---------|
|`key:response`|Separates the command-line argument (key) and the response message (value) with a colon.|

Example:Content of `fucks.txt`
```fucks.txt
you:fuck you too
me:okay
off:no, YOU fuck off!
them:why not?
it:yep, let's fuck it all up
world:a bit ambitious, isn't it?
```

## Examples

### Specifying a Custom Target
```
# If 'you:fuck you too' is defined in fucks.txt
$ fuck you
fuck you too
```

### Undefined Target
```
# If 'apple' is not found in fucks.txt
$ fuck apple
I don't know how to fuck that.
```

### Built-in Help
```
$ fuck help
Usage: fuck <target>
(Check fucks.txt for custom targets)
```
yes, it is unhelpable. i know.

### Version Info
```
$ fuck -v
version FUCK.1.0 (The RUDE edition)
```

## Building
Use your own GCC.
Just as:
```
# Compile the C file
gcc fuck.c -o fuck.exe -lkernel32 
# -lkernel32 is required to link the GetModuleFileNameA function
```

### Compilation Note
*WINDOWS ONLY!!* cause it using Windows API.
someone help to make it compatible for others. *PLEASE*.

To suppress security warnings related to the use of fopen and strcpy when building with environments like Visual Studio, the following macro is defined at the beginning of the code:
```C
#define _CRT_SECURE_NO_WARNINGS
```

### Required Files
`fuck.c`(main source code)
`fucks.txt`(response data file)

## Contribution
You just needed to bring your own humore.
i'm noob for all in github, idk how.
`Gemini`says, 
```Building
If you wish to contribute:
1.  Fork this repository.
2.  Create your feature branch (`git checkout -b feature/new-rude-thing`).
3.  Commit your changes (`git commit -am 'Add new rude thing'`).
4.  Push to the branch (`git push origin feature/new-rude-thing`).
5.  Create a Pull Request.
```
i know that you'll do well than me. 
Branch, Commit, Push-to-the-branch, They are free. Try it.

Sorry for my noob. And please sure I'm Japanese.
Fuck you.
