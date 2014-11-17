#!/bin/sh
trifs-tools/mkfs.trifs disk 2880 36 512
trifs-tools/ibc boot/trifs disk
trifs-tools/put init/init disk init
trifs-tools/put core/core disk core
trifs-tools/put root/root disk root
trifs-tools/put test/test disk test
trifs-tools/put ping/ping disk ping
trifs-tools/put pong/pong disk pong
