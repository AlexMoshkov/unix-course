#!/bin/bash

dd if=/dev/zero of=fileA bs=1 count=$((4 * 1024 * 1024 + 1))
printf '\x01' | dd of=fileA bs=1 seek=0 conv=notrunc
printf '\x01' | dd of=fileA bs=1 seek=10000 conv=notrunc
printf '\x01' | dd of=fileA bs=1 seek=$((4 * 1024 * 1024)) conv=notrunc
