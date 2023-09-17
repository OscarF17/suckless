#!/bin/sh

# Last notification sent
LAST="NONE"

LOW=20
CRITICAL=10

while true; do
    STATUS=$(acpi | awk '{print $3}')
    CHARGE=$(cat /sys/class/power_supply/BAT0/capacity)

    # Only check if not plugged and not sent already
    if [ $STATUS = "Discharging," ]; then
        # Check if battery is critical
        if [ $CHARGE -le $CRITICAL ]; then
            # Only send if it hasn't already been sent 
            if [ $LAST != "CRIT" ]; then
                notify-send "󰂃 BATTERY CRITICAL" "Battery under 10%"
                LAST="CRIT"
            fi

        elif [ $CHARGE -le $LOW ]; then
            if [ $LAST != "LOW" ]; then
                notify-send "󰂃 BATTERY LOW" "Battery under 10%"
                LAST="LOW"
            fi
        
        fi

    # Reset notifications
    elif [ $LAST != "NONE" ]; then
        LAST="NONE"
    fi

    sleep 300 # Check every 5 minutes
done
