# sh run.sh test.cpp
sudo perf c2c record --all-user ./run_this_code > vars.txt
sudo perf c2c report -c tid,iaddr --stdio > perf.txt
python3 parse.py perf.txt vars.txt