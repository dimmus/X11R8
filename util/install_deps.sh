#!/bin/sh

set -e

NORMAL='\e[0m'
RED='\e[31;1m'
YELLOW='\e[33;1m'
BLUE='\e[35;1m'

OS=
VER=

msg() {
	[ -n "$quiet" ] && return 0
	local prompt="$YELLOW---${NORMAL}"
	local name="${BLUE}${OS} ${VER}${NORMAL}"
    printf "${prompt} ${name}: %s\n" "$1" >&2
}

get_os() {
    if [ -f /etc/os-release ]; then
        # freedesktop.org and systemd
        . /etc/os-release
        OS=$NAME
        VER=$VERSION_ID
    elif type lsb_release >/dev/null 2>&1; then
        # linuxbase.org
        OS=$(lsb_release -si)
        VER=$(lsb_release -sr)
    elif [ -f /etc/lsb-release ]; then
        # For some versions of Debian/Ubuntu without lsb_release command
        . /etc/lsb-release
        OS=$DISTRIB_ID
        VER=$DISTRIB_RELEASE
    elif [ -f /etc/debian_version ]; then
        # Older Debian/Ubuntu/etc.
        OS=Debian
        VER=$(cat /etc/debian_version)
    elif [ -f /etc/SuSe-release ]; then
        # Older SuSE/etc.
        OS=SuSe
        ...
    elif [ -f /etc/redhat-release ]; then
        # Older Red Hat, CentOS, etc.
        OS=RedHat
        ...
    else
        # Fall back to uname, e.g. "Linux <version>", also works for BSD, etc.
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