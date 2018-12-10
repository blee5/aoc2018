lights = []

with open("input", 'r') as f:
    for line in f:
        # I don't know how to use regex :c
        line = line[line.find("<") + 1:]
        x, y = map(int, line[:line.find(">")].split(","))
        line = line[line.find("<") + 1:]
        dx, dy = map(int, line[:line.find(">")].split(","))
        lights.append({"x": x, "y": y, "dx": dx, "dy": dy})

bounds = []
for i in range(25000):
    minx = min(d["x"] + i * d["dx"] for d in lights)
    maxx = max(d["x"] + i * d["dx"] for d in lights)
    miny = min(d["y"] + i * d["dy"] for d in lights)
    maxy = max(d["y"] + i * d["dy"] for d in lights)
    bounds.append((maxx, minx, maxy, miny, i))

bounds.sort(key=lambda t: (t[0] - t[1]) * t[2] - t[3])
bounds = bounds[:5]

print("Trying 5 likely candidates")
for bound in bounds:
    sky = [[' '] * (bound[0] - bound[1] + 1) for j in range(bound[2] - bound[3] + 1)]
    for light in lights:
        sky[light["y"] + bound[4] * light["dy"] - bound[3]][light["x"] + bound[4] * light["dx"] - bound[1]] = "#"
    for s in sky:
        if "#" in s:
            print(''.join(s))  
    print("Elapsed Time: {} seconds".format(bound[4]))
    input()
