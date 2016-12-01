#!/bin/sh

# Setup the environment for cases when Travis automatically can't
apt-get update
apt-get -y install cmake cmake-data check
