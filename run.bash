count=0
echo "Rate analysis" > result.txt
for i in build/*.root
do 
    path=${i}
    root -l -q 'analysis.cpp('${count}', "'${path}'")' >> result.txt
    count=$((count+1))
done