with open("input", 'r') as f:
    data = map(int, f.read().split())

def read_node(i):
    metadata_sum = 0
    children_length = 0

    # Read header
    num_child = data[i] 
    num_metadata = data[i + 1]
    i += 2

    # Get metadata sums from children
    for j in range(num_child):
        temp = part2(i + children_length)
        children_length += temp[0]
        meta_sum += temp[1]

    while (num_child > 0):
        temp = read_node(i + children_size)
        children_size += temp[0]
        meta_sum += temp[1]
        num_child -= 1

    # Shift index by size of child nodes
    i += children_size
    for j in range(num_metadata):
        metadata_sum += data[i]
        i += 1

    return 2 + children_length + num_metadata, metadata_sum

def checksum(i):
    metadata_sum1 = 0 # part1 
    metadata_sum2 = 0 # part2
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
        metadata_sum1 += temp[1]
        child_sums.append(temp[2])

    # Read metadata
    i += children_length
    for j in range(num_metadata):
        metadata_sum1 += data[i]
        if (num_child == 0):
            metadata_sum2 += data[i]
        elif (data[i] - 1 < num_child):
            metadata_sum2 += child_sums[data[i] - 1]
        i += 1

    return 2 + children_length + num_metadata, metadata_sum1, metadata_sum2

sums = checksum(0)
print("Part 1 Answer:\n" + str(sums[1]))
print("Part 2 Answer:\n" + str(sums[2]))
