
## NOTE: 
**caesar cipher here can encrypt only latin letters from A to Z (all capital), comma, dot and whitespace**

PIPE EXAMPLE:

echo "TEST STRING TO ENCRYPT" > data.txt
cat data.txt | ./caesar e 1 5 | ./scytale e 9 > secret.txt
cat secret.txt
cat secret.txt | ./scytale d 9 | ./caesar d 1 5

