pots = list(".##..##..####..#.#.#.###....#...#..#.#.#..#...#....##.#.#.#.#.#..######.##....##.###....##..#.####.#")

rules_s = """.#... => #
#.... => .
#.### => .
#.##. => .
#...# => .
...#. => .
.#..# => #
.#### => #
.###. => .
###.. => #
##### => .
....# => .
.#.## => #
####. => .
##.#. => #
#.#.# => #
..#.# => .
.#.#. => #
###.# => #
##.## => .
..#.. => .
..... => .
..### => #
#..## => #
##... => #
...## => #
##..# => .
.##.. => #
#..#. => .
#.#.. => #
.##.# => .
..##. => ."""

rules = []
for rule in rules_s.split("\n"):
    temp = rule.split(" => ")
    if temp[0][2] != temp[1]:
        temp[0] = list(temp[0])
        rules.append(temp)

def sum_pots(pots, zero):
    s = 0
    for i in range(0, len(pots)):
        if pots[i] == '#':
            s += i - zero
    return s

zero, prev_zero = 0, 0
prev_pots = []
for i in range(50000000000):
    # All are inputs guaranteed to converge into an identical sequence that just shifts?
    # I doubt it, but at least it works for my case..
    if prev_pots == pots:
        break;

    prev_zero = zero
    prev_pots = pots.copy()
    zero += 5
    pots = list('.....') + pots + list('.....')
    temp_pots = pots.copy()

    for j in range(2, len(pots) - 2):
        for rule in rules:
            if pots[j - 2: j + 3] == rule[0]:
                temp_pots[j] = rule[1]
    # Trim
    for j in range(5):
        while temp_pots[0] == '.':
            zero -= 1
            temp_pots = temp_pots[1:]
    for j in range(5):
        while temp_pots[-1] == '.':
            temp_pots = temp_pots[:-1]

    pots = temp_pots

    if i == 19:
        print("Part 1 Answer:\n" + str(sum_pots(pots, zero)))

print("Part 2 Answer:\n" + str(sum_pots(pots, zero + (zero - prev_zero) * (50000000000 - i))))
