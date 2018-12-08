with open("input", 'r') as f:
    data = map(int, f.read().split())

def checksum(i):
    total = 0 # part1 
    value = 0 # part2
    children_length = 0

    # Read header
    num_child = data[i] 
    num_metadata = data[i + 1]
    i += 2

    child_sums = []
    # Get metadata sums from children
    for j in range(num_child):
        temp = checksum(i + children_length)
        children_length += temp[0]
        total += temp[1]
        child_sums.append(temp[2])

    # Read metadata
    i += children_length
    for j in range(num_metadata):
        total += data[i]
        if (num_child == 0):
            value += data[i]
        elif (data[i] - 1 < num_child):
            value += child_sums[data[i] - 1]
        i += 1

    return 2 + children_length + num_metadata, total, value

sums = checksum(0)
print("Part 1 Answer:\n" + str(sums[1]))
print("Part 2 Answer:\n" + str(sums[2]))
