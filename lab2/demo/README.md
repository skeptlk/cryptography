```
./keygen 33 > alph.txt
./crypt -a alph.txt < input.txt > secret.txt
cat secret.txt
./decrypt -a < secret.txt
rm secret.txt
```