#!/bin/bash
clear && ctags -R * && cd build && cmake .. && make && ./test
