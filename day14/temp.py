# This thing is slow and unoptimized probably 

n_recipes = 890691
target = [int(d) for d in str(n_recipes)]
target_len = len(target)

def add_recipe(elf_1, elf_2, recipes):
    s = recipes[elf_1] + recipes[elf_2]
    if (s > 9):
        recipes.append(1)
    recipes.append(s % 10)
    elf_1 = (elf_1 + 1 + recipes[elf_1]) % len(recipes)
    elf_2 = (elf_2 + 1 + recipes[elf_2]) % len(recipes)
    return elf_1, elf_2, recipes
    
recipes = [3, 7]
elf_1 = 0
elf_2 = 1
for i in range(2, n_recipes + 10):
    elf_1, elf_2, recipes = add_recipe(elf_1, elf_2, recipes)

answer = ''.join(map(str, recipes[n_recipes:n_recipes+10]))
print("Part 1 Answer:\n" + answer)

i = 0
while (True):
    i += 1
    elf_1, elf_2, recipes = add_recipe(elf_1, elf_2, recipes)
    if recipes[i - target_len:i] == target:
        print("Part 2 Answer:\n" + str(i - target_len))
        break;

