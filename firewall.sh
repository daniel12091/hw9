#!/bin/bash

cat $1 > rules_file
cat $2 > packets.txt


cat rules_file | uniq | sed 's:#.*$::g' | sed '/^$/d' | sed 's/ //g' > temp.txt

cat temp.txt |\
while read line; do
	IFS=',' read -ra rules <<< "$line"
	(cat packets.txt | \
	./firewall.exe "${rules[0]}" 2>/dev/null |\
	./firewall.exe "${rules[1]}" 2>/dev/null |\
	./firewall.exe "${rules[2]}" 2>/dev/null |\
	./firewall.exe "${rules[3]}" 2>/dev/null)  >> tmp_results.txt
done


cat tmp_results.txt | sort | uniq | sed 's:#.*$::g' | sed '/^$/d' | sed 's/ //g'
rm tmp_results.txt rules_file  packets.txt temp.txt
