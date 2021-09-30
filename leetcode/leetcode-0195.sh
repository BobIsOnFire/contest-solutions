# Read from the file file.txt and output the tenth line to stdout.
i=0

while read line; do
    i=$(( $i + 1 ))
    if [ "$i" = "10" ]; then
        echo "$line"
        exit
    fi
done <file.txt

echo
exit 1
