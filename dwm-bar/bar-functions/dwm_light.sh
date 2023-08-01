#!/bin/sh

# A dwm_bar function to read the brightness using light
# Oscar Flores <oscarlflores@protonmail.com
# Dependencies: light

dwm_light () {
    BRIGHTNESS=$(light -G)

    printf "%s" "$SEP1"
    if [ "$IDENTIFIER" = "unicode" ]; then
        printf " %s%%" "$BRIGHTNESS"
    else
        printf "BAT %s%% %s" "$BRIGHTNESS" 
    fi
    printf "%s\n" "$SEP2"
}

dwm_light

