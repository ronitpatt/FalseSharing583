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
    struct_vars.sort(key=lambda x: x[1])
    return [i[0] for i in struct_vars]

false_shared_addresses = parse_perf(sys.argv[1])
address_to_var = parse_vars(sys.argv[2])

print(address_to_var)
print(false_shared_addresses)

print("False shared addresses:")
struct_map = defaultdict(list)
for i, tid in false_shared_addresses:
    if i in address_to_var:
        print(address_to_var[i], i, tid)
        if "struct." in address_to_var[i][1]:
            s = address_to_var[i][1].split(".")
            struct_map[s[1]].append((s[2], tid))
    # else:
    #     before_i = [j for j in address_to_var if int(j, 16) < int(i, 16)]
    #     if len(before_i):
    #         closest = max(before_i, key=lambda x: int(x, 16))
            
print(struct_map)
print("--- REORDERED STRUCTS ---")
for key in struct_map:
    with open("reorder.txt", "w") as outfile:
        outfile.write("struct." + key + " " + ' '.join(reorder_struct(struct_map[key])))