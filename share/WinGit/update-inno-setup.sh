#!/bin/sh

# Find a suitable download tool.
if [ -f "$(type -p curl)" ]; then
    download="curl"
    download_args_rss="-s"
    download_args="-# -L -o"
elif [ -f "$(type -p wget)" ]; then
    download="wget"
    download_args_rss="-q -O -"
    download_args="-N -O"
else
    echo "ERROR: No suitable download tool found."
    exit 1
fi

SCRIPTDIR="$(cd "$(dirname "$0")" && pwd)"
MSYSGITROOT="$(cd $SCRIPTDIR/../../ && pwd | sed 's/\/$//')/."
cd $MSYSGITROOT

# Download the most recent Inno Setup version.
file="is-unicode.exe"
url="http://www.jrsoftware.org/download.php/$file"

if [ "$download" == "curl" ]; then
    download_args="$download_args $file -R -z"
fi
$download $download_args $file $url

if [ -f $file ]; then
    # Remove any previous installation.
    rm -fr share/InnoSetup/

    # Silently install Inno Setup.
    wine=$(type -p wine)
    if [ $? -eq 0 ]; then
        $wine $file /verysilent /dir="share\InnoSetup" /noicons /tasks="" /portable=1
    else
        # See http://www.mingw.org/wiki/Posix_path_conversion.
        $file //verysilent //dir="share\InnoSetup" //noicons //tasks="" //portable=1
    fi

    # Remove unneeded files from the installation.
    ( cd share/InnoSetup/ && rm -fr Examples/ Compil32.exe isscint.dll )

    # Clean up.
    rm $file
fi
