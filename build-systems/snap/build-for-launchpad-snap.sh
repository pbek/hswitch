#!/usr/bin/env bash
#
# This is the build/deploy script for the Launchpad Snap image
# https://launchpad.net/hswitch-snap
#
# We need a ssh key to push to the git repository
# git+ssh://pbek@git.launchpad.net/~pbek/hswitch-snap
#


# uncomment this if you want to force a version
#HSWITCH_VERSION=16.07.6

BRANCH=develop
#BRANCH=master

PROJECT_PATH="/tmp/hswitch-launchpad-snap-$$"


echo "Started the Launchpad Snap packaging process, using latest '$BRANCH' git tree"

if [ -d $PROJECT_PATH ]; then
    rm -rf $PROJECT_PATH
fi

mkdir $PROJECT_PATH
cd $PROJECT_PATH || exit

echo "Project path: $PROJECT_PATH"

# checkout Launchpad Snap repository
git clone --depth=1 git+ssh://pbek@git.launchpad.net/hswitch-snap snap || exit
#git clone -c core.sshCommand="/usr/bin/ssh -vvv" --depth=1 git+ssh://pbek@git.launchpad.net/hswitch-snap snap || exit

# checkout the source code
git clone --depth=1 git@github.com:pbek/hswitch.git hswitch -b $BRANCH
cd hswitch || exit

if [ -z $HSWITCH_VERSION ]; then
    # get version from version.h
    HSWITCH_VERSION=`cat src/version.h | sed "s/[^0-9,.]//g"`
fi

cd ../snap || exit
cp ../hswitch/build-systems/snap/snapcraft/* . -R

# replace the version in the snapcraft.yaml file
sed -i "s/VERSION-STRING/$HSWITCH_VERSION/g" snapcraft.yaml


echo "Committing changes..."
#git add -A
git commit -m "releasing version $HSWITCH_VERSION" -a
git push

# remove everything after we are done
if [ -d $PROJECT_PATH ]; then
    rm -rf $PROJECT_PATH
fi
