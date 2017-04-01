#!/usr/bin/env bash

# -----------------------------------------------------------------------------
# Info:
#   author:    Miroslav Vidovic
#   file:      bookmarks-rofi.sh
#   created:   01.04.2017.-10:42:44
#   revision:  ---
#   version:   1.0
# -----------------------------------------------------------------------------
# Requirements:
#   rofi 
# Description:
#   Search all bookmarks in rofi. 
# Usage:
# 
# -----------------------------------------------------------------------------
# Script:

# bookie outputs data with colors
# Remove ( color / special / escape / ANSI ) codes, from text, with sed
remove_color_characters(){
  sed -r "s/\x1B\[([0-9]{1,2}(;[0-9]{1,2})?)?[m|K]//g"
}

# Display a rofi menu for bookmark selection
display_in_rofi(){
  rofi -dmenu -lines 20 -width 80 -fuzzy -only-match -location 0 -p "Bookmark > "
}

main(){
  # Get the bookmark data
  bookmark=$(./bookie -l | remove_color_characters | display_in_rofi)
  # Extract the url
  url=$(echo $bookmark | awk '{print $2}')

  xdg-open "$url"
}

main

exit 0
