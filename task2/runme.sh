> tmp.txt;
for _ in $(seq 1 10); do
  ./program myfile >> tmp.txt &
done;

sleep $((5 * 60));

kill -2 $(jobs -p);

cat tmp.txt | sort | uniq -c > result.txt;