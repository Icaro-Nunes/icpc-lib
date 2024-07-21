import random
import subprocess

MAX_NUM_PEOPLE = 9


def gen_case() -> str:
    n = random.randint(1, MAX_NUM_PEOPLE)
    max_m = n*n - n
    m = random.randint(0, max_m)

    ai = []
    for i in range(n):
        ai.append(random.randint(1, 100))

    restr = []
    for _ in range(m):
        x = random.randint(1, n)
        y = random.randint(1, n)

        while(x == y):
            x = random.randint(1, n)
            y = random.randint(1, n)

        restr.append((x, y))

    res = f"{n} {m}\n{' '.join(str(x) for x in ai)}\n"
    for (x, y) in restr:
        res += f"{x} {y}\n"

    return res

random.seed((1 << 9) | 31)

for i in range(100):
    print()
    print()
    case = gen_case()
    print(f"Test #{i+1}: ")
    print(case)
    # test bruteforce
    bf = subprocess.run(['out/b'], input=case, encoding='ascii', capture_output=True)
    # test solution
    sol = subprocess.run(['out/m'], input=case, encoding='ascii', capture_output=True)

    bf_res = int(bf.stdout)
    sol_res = int(sol.stdout)

    print(f"bruteforce {bf_res}, solution {sol_res}")

    if bf_res == sol_res:
        print("accepted")
    else:
        print("WA")
        break

