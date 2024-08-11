makedirectory () {
    if [ ! -d "$1" ]; then
      echo "$1 does not exist."
      echo "Creating $1"
      mkdir $1
    else 
      echo "$1 does exist."
    fi
}

makedirectoryandCmake () {
    if [ ! -d "$1" ]; then
      echo "$1 does not exist."
      echo "Creating $1"
      mkdir $1 && cd $1
      cmake ..
      make 
      cd ..
    else 
      echo "$1 does exist."
    fi

}

BUILDDIR="build/"

makedirectoryandCmake ${BUILDDIR}

echo "run the simulation..."
cd build/
./lab2run run.mac
cd ..

count=0
echo "Rate analysis" > result.txt
for i in build/*.root
do 
    path=${i}
    root -l -q 'analysis.cpp('${count}', "'${path}'")' >> result.txt
    count=$((count+1))
done