# dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


## Requirements
------------
In order to build dwm you need the Xlib header files.

On Fedora:
Dependencies:
sudo dnf install git make gcc libXft-devel libX11-devel libXinerama-devel

Additional packages:
sudo dnf install spectacle copyq light redshift playerctl
- Spectacle: Screenshots
- CopyQ: Clipboard manager
- Light: Brightness control
- Redshift: Blue light filter
- Playerctl: Enable media keys

Fonts:
FontAwesome

On Debian / Mint
sudo apt install build-essential libx11-dev libxft-dev libxinerama-dev libfreetype6-dev libfontconfig1-dev

## Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


## Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


## Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

## Personal configurations

### Fix touchpad controls
Create a file on /etc/X11/xorg.conf.d named 0X-touchpad.conf (change X with whatever is the largest file number already in the directory)
Paste the following:
Section "InputClass"
    Identifier "touchpad"
    MatchIsTouchpad "on"
    Option "Tapping" "on"
    Option "ClickMethod" "buttonareas"
    Option "DisableWhileTyping" "on"
    Option "MiddleEmulation" "on"
    Option "NaturalScrolling" "on"
EndSection

This will enable:
- Button areas (clicking on right side of touchpad works as right click"
- Natural scrollong: invert scrolling direction
