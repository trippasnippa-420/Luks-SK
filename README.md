# Luks-SK
A dead simple program to extract a challenge-response (HMAC-SHA1) from a security key supporting the Yubikey API.

## How it works
The program will first try to open a file called "challenge" in its current directory and read 64 (hopefully) random bytes from it. To create this file you can just use regular old Disk Destroyer:
```zsh
dd if=/dev/urandom of=challenge bs=1 count=64
```
It will then try to open a key on VID ```0x1d50``` and PID ```0x60fc``` (my OnlyKey). If it fails it will return 1 and print the error to stdout (yes I know). If it succeeds it will attempt a challenge response and print it to stdout in standard lowercase hex (```0xdeadbeef```). This can be added to a LUKS keyslot and then be used to open the container (see LUKS bit).

## LUKS bit...
I confess this program will not unlock a LUKS encrypted drive on its own. That's because it's intended to be a part of a custom initramfs setup like [mine](https://github.com/trippasnippa-420/Custom-Initramfs).

Because all it does is spit out the response from the Yubikey on stdout it can be included in a script to unlock the LUKS disk like this (provided the response has already been added to a LUKS key slot):
```zsh
$ ok-luks | (sudo/doas) cryptsetup open <device> <mapped name> -d -
```

## Why?
While there are other programs to accomplish this task like [fido2luks](https://github.com/shimunn/fido2luks), [yubikey-luks](https://github.com/cornelinux/yubikey-luks), or even systemd's magic, I find they are all relatively complex, requiring their own init scripts and a mainstream initramfs like dracut. While many users will find this completely acceptable, I prefer an initramfs that I entirely understand and does exactly what I need it to, and this requires an equally simple program for getting a challenge-response from a Yubikey.

## Hacking
This program will require slight modification to work with mainstream Yubikeys, as it is currently configured to open a key using the VID and PID of my OnlyKey instead. Just find these two lines
```c++
const int pid[1] = { 0x60fc };
onlykey = yk_open_key_vid_pid(0x1d50, pid, sizeof(pid), 0);
```
in main.cpp and replace them with whatever you would like.
