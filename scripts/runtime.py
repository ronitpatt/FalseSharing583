import os, sys, time

N = 50

executable = sys.argv[1]

command = "/bin/bash -c \"{ time  " + executable +"; } 2> output.txt\""
print(command)

totalelapsed = 0
for _ in range(N):
    os.system(command)
    with open("output.txt", "r") as infile:
        elapsed = infile.readlines()[1]
        elapsed = elapsed.split()[1] # 0m0.012s
        elapsed = float(elapsed[2:-1])
        totalelapsed += elapsed
    
    # elapsed = float(data[2][:-7])

print(totalelapsed/N)
