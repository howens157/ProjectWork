
while [ $# -gt 0 ]; do
	case $1 in
		-n) shift; echo "$1" ;;
		-f) shift; echo "$1" ;;
		*) echo "other" ;;
	esac

	shift
done

