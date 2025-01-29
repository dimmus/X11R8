#!/bin/sh

set -e

NORMAL='\e[0m'
RED='\e[31;1m'
YELLOW='\e[33;1m'
BLUE='\e[35;1m'

msg() {
	[ -n "$quiet" ] && return 0
	local prompt="$YELLOW---${NORMAL}"
	local name="${BLUE}${OS} ${VER}${NORMAL}"
    printf "${prompt} ${name}: %s\n" "$1" >&2
}

get_os() {
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        OS=$NAME
        VER=$VERSION_ID
    elif type lsb_release >/dev/null 2>&1; then
        OS=$(lsb_release -si)
        VER=$(lsb_release -sr)
    else
        OS=$(uname -s)
        VER=$(uname -r)
    fi                                          
}

install_deps()
{   
    msg "Installing dependencies"

    case $OS in
        "Ubuntu"|"Kali GNU/Linux")
            sudo apt-get install -y \
                build-essential meson ninja-build \
                mesa-common-dev libgl1-mesa-dri
            ;;
        "Archlinux")
            sudo pacman -S meson libdrm libunwind libinput
            sudo pacman -Sdd mesa libglvnd # avoid autoinstall x11 stuff
            ;;
        "Alpine Linux")
            doas apk add meson flex bison clang ccache \
                freetype-dev fontconfig-dev pixman-dev xkbcomp-dev dbus-dev \
                libdrm-dev mesa-dev libunwind-dev libinput-dev libevdev-dev \
                cairo-dev openssl-dev
            ;;
        *) 
            echo "Have not list of dependencies for $OS"
            ;;
    esac
}

get_os
install_deps