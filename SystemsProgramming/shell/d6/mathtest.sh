
AVAR=5.42
BVAR=6.98

RES=$(echo "$BVAR<$AVAR" | bc -l)

echo "$RES"

