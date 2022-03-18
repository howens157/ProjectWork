cat shakespeare.txt | sed -nE 's/\s+([A-Z]{3,16}\b)\..*/\1/p'

