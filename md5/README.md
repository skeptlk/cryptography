# MD5 hashing function implementation

Ported from pseudocode found here: 
https://en.wikipedia.org/wiki/MD5#Pseudocode

The only main feature of this code is the ability to read huge files by chunks,
so that only one chunk of size 512 bits (64 bytes) processed each round.

We need the `processLast` variable (main.cpp:69 and below) to handle situation 
when after padding the original message with 1 and 0's we have to add another chunk 
to append message size into it. 