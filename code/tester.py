import random
import subprocess

MAX_N = 100


def gen_case() -> str:
    return f"1\n"

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

    bf_res = bf.stdout
    sol_res = sol.stdout

    print(f"bruteforce {bf_res}, solution {sol_res}")

    if bf_res == sol_res:
        print("accepted")
    else:
        print("WA")
        break

