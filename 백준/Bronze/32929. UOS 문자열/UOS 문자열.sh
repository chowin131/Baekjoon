read x
r=$(( (x - 1) % 3 ))

if [ $r -eq 0 ]; then
    echo "U"
elif [ $r -eq 1 ]; then
    echo "O"
else
    echo "S"
fi