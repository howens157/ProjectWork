
VAR="hello world"

for i in $(seq 0 ${#VAR}); do
	case ${VAR:i:1} in
		h) .... ;;
		e) .... ;;
	esac
done

