cat shakespeare.txt | sed -nE 's/^\s+([A-Z]{3,16})\..*/\1/p' | sort | uniq -c | sort -r -h | head -n 30

