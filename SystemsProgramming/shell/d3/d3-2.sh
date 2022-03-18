cat shakespeare.txt | sed -nE 's/.*(\b[A-Z]{3,16}\b)\..*/\1/p'

