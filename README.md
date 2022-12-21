# hswitch

[Changelog](https://github.com/pbek/hswitch/blob/develop/CHANGELOG.md) | 
[Issues](https://github.com/pbek/hswitch/issues)

[![Build Status Linux / OS X](https://travis-ci.org/pbek/hswitch.svg?branch=develop)](https://travis-ci.org/pbek/hswitch)

**hswitch** is a hosts file content switcher to modify your static ip addresses 
quickly for development.

It currently only works under Linux.

## Screenshot

![Screenhot](screenshots/screenshot.png)

## Todo

- Windows adaptions
    - icons
    - `sudo` and copy process replacement
    - different hosts file
    - packaging
- translation?

## Installation

- `snap install hswitch`
- install the Qt base libraries on your system 
- run `/snap/hswitch/current/usr/bin/hswitch`
    - since Qt snaps still seem to look atrocious under KDE you might want to
      run the binary directly
    - disclaimer: you definitely have to run the binary directly, writing to 
      the hosts file doesn't seem to work in the Snap confinement

## Building

To get the most current features you can build the application from the 
source code. Download the latest source here:
[Sources on GitHub as ZIP](https://github.com/pbek/hswitch/archive/develop.zip)

Alternatively you can also checkout the code directly from the git repository:


```shell
git clone https://github.com/pbek/hswitch.git -b master
cd hswitch
```

Then download [Qt Creator](http://www.qt.io/download-open-source), open the 
project file `src/hswitch.pro` and click on *Build / Run*.

Or you can build it directly in your terminal:

```shell
cd src
qmake
make
make install
```

Please feel free to contribute source code to this project, make suggestions or
report troubles on the [issues page](https://github.com/pbek/hswitch/issues).

You can also visit [hswitch on GitHub](https://github.com/pbek/hswitch).

## Minimum software requirements

- A desktop operating system, that supports [Qt](http://www.qt.io/)
- Qt 5
- gcc 4.8+

## Disclaimer

This SOFTWARE PRODUCT is provided by THE PROVIDER "as is" and "with all faults."
THE PROVIDER makes no representations or warranties of any kind concerning the
safety, suitability, lack of viruses, inaccuracies, typographical errors, or
other harmful components of this SOFTWARE PRODUCT. 

There are inherent dangers in the use of any software, and you are solely
responsible for determining whether this SOFTWARE PRODUCT is compatible with
your equipment and other software installed on your equipment.
You are also solely responsible for the protection of your equipment and 
backup of your data, and THE PROVIDER will not be liable for any damages you may
suffer in connection with using, modifying, or distributing this SOFTWARE PRODUCT.
