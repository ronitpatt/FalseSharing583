# sh run.sh test.cpp
Prefix=""
if [ $# = 2 ]; then
    Prefix=$2
fi
sudo perf c2c record --all-user ./run_this_code > vars.txt
sudo perf c2c report -c tid,iaddr --stdio > $1
python3 parse.py $1 vars.txt