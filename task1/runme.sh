gcc main.c -o program

./get_a.sh

./program fileA fileB

gzip -k fileA
gzip -k fileB

gzip -cd fileB.gz | ./program fileC

./program --block-size 100 fileA fileD

stat fileA fileA.gz fileB fileB.gz fileC fileD > result.txt