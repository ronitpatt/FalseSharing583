import sys
from collections import defaultdict
def parse_perf(filename):
    with open(filename, "r") as infile:
        lines = infile.readlines()

    lines = [i.strip().replace("\n", "") for i in lines]

    index = lines.index("Shared Data Cache Line Table")
    lines = lines[index:]
    
    index = lines.index("Shared Cache Line Distribution Pareto")
    lines = [i for i in lines[index+7:] if i!=""]

    ans = []
    while len(lines):
        lines.pop(0)
        base_address = lines.pop(0).split()[-1]
        lines.pop(0)

        while(len(lines) and lines[0][0] != "-"):
            temp = lines.pop(0).split()
            
            if temp[0] != "0.00%" or temp[1] != "0.00%":
                print(temp)
                colon_index = temp[8].index(':')
                ans.append((hex(int(base_address, 16) + int(temp[5], 16)), temp[8][:colon_index]))

    return ans

def parse_vars(filename):
    with open(filename, "r") as infile:
        lines = infile.readlines()

    lines = [i.strip().replace("\n", "") for i in lines]
    lines = [i for i in lines if len(i.split()) == 3]
    mapper = {}

    for i in lines:
        temp = i.split()
        mapper[temp[2]] = (temp[0], temp[1])

    return mapper


def reorder_struct(struct_vars):
    
    sortedoffsets = [sorted(list(struct_vars[threadid])) for threadid in struct_vars]
    res = []
    newoffset = -1
    topad = []
    for region in sortedoffsets:
        res += region
        if newoffset > 0:
            topad.append(newoffset)
        newoffset += len(region)
    print(struct_vars, res)
    return res, topad

false_shared_addresses = parse_perf(sys.argv[1])
address_to_var = parse_vars(sys.argv[2])

print("Address", address_to_var)
print("false shared addresse", false_shared_addresses)

print("False shared addresses:")
struct_map = defaultdict(lambda: defaultdict(set))
for i, tid in false_shared_addresses:
    if i in address_to_var:
        print(address_to_var[i], i, tid)
        if "struct." in address_to_var[i][1]:
            s = address_to_var[i][1].split(".")
            struct_map[s[1]][tid].add(s[2])
    # else:
    #     before_i = [j for j in address_to_var if int(j, 16) < int(i, 16)]
    #     if len(before_i):
    #         closest = max(before_i, key=lambda x: int(x, 16))
            
print(struct_map)
print("--- REORDERED STRUCTS ---")
prefix = ""
if len(sys.argv) == 4:
    prefix = sys.argv[3]
neworder = defaultdict(list)
paddStruct = defaultdict(list)

for key in struct_map:
    neworder[key], paddStruct[key] = reorder_struct(struct_map[key])

if "reordering" == prefix:
    with open("reorder.txt", "w") as outfile:
        for key in neworder:
            outfile.write("struct." + key + " " + ' '.join(neworder[key]))
        with open("padding.txt", 'w') as outfile:
            outfile.write(f"struct.{key+prefix} "+ ' '.join(paddStruct[key]))
    exit()
padding = {}
print(struct_map)
print("neworder", neworder)
for key in neworder:
    topad = []
    elements = neworder[key]
    for i in range(1,len(elements)):
        if int(elements[i]) != int(elements[i-1]) + 1:
            topad.append(str(i-1))
    print(topad)
    padding[key] = topad
    with open("padding.txt", 'w') as outfile:
        outfile.write(f"struct.{key+prefix} "+ ' '.join(topad))

    