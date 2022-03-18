cat shakespeare.txt | sed -nE 's/^\s+([A-Z]{3,16})\..*/\1/p' | sort | uniq -c

