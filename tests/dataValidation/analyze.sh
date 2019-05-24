xxd -r -p data/$1.hex data/$1.bin
ent data/$1.bin
echo "--------------------------------------------------"
ent -b data/$1.bin

