#!/bin/bash

cd autoconf
autoconf -o ../configure configure.ac

touch configure

### autoreconf -f -i -Wall

