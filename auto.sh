#!/bin/sh
autoconf
autoreconf --install
automake
./configure
