./newrun.sh $1 $2
sudo 2>"$3pass.txt" perf stat -d ./run_this_code
python3 runtime.py ./run_this_code

echo "nopass"
./newrun.sh nopass $2
sudo 2>"$3nopass.txt" perf stat -d ./run_this_code 
python3 runtime.py ./run_this_code
