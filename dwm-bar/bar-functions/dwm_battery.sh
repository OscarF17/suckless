#!/bin/sh

# A dwm_bar function to read the battery level and status
# Joe Standring <git@joestandring.com>
# GNU GPLv3

dwm_battery () {
    # Change BAT1 to whatever your battery is identified as. Typically BAT0 or BAT1
    CHARGE=$(cat /sys/class/power_supply/BAT0/capacity)
    TIME=$(acpi | awk '{print $5}' | awk -F ':' '{print $1":"$2}')
    STATUS=$(acpi | awk '{print $3}')

    printf "%s" "$SEP1"
    if [ "$IDENTIFIER" = "unicode" ]; then
        if [ "$STATUS" = "Charging," ]; then
            printf " %s%% %s" "$CHARGE" "$TIME"
        else
            printf " %s%% %s" "$CHARGE" "$TIME"
        fi
    else
        printf "BAT %s%% %s" "$CHARGE" "$TIME"
    fi
    printf "%s\n" "$SEP2"
}

dwm_battery

