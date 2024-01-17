import argparse

from pysat.formula import CNF
from pysat.solvers import Solver

import numpy as np

from argparse_range import range_action

MAX_VARS = 10_000
MAX_CLAUSES = 100_000
CLAUSE_SIZE = 3


def main():
    parser = argparse.ArgumentParser(
        description="Script for generating SAT systems"
    )

    parser.add_argument(
        "-c",
        "--clauses",
        type=int,
        required=True,
        action=range_action(1, MAX_CLAUSES + 1),
        help="Amount of clauses",
    )
    parser.add_argument(
        "-v",
        "--vars",
        required=True,
        type=int,
        action=range_action(2, MAX_VARS + 1),
        help="Amount of vars",
    )

    args = parser.parse_args()

    cnf_sizes: tuple[int, int] = (args.clauses, CLAUSE_SIZE)
    clauses = (
        np.random.randint(1, args.vars + 1, size=cnf_sizes)
        * np.random.choice([-1, 1], size=cnf_sizes)
    ).tolist()
    print("{")
    for clause in clauses:
        print(f'{{{", ".join(map(str, clause))}}},')
    print("}\n")

    with Solver(bootstrap_with=CNF(from_clauses=clauses)) as solver:
        print("formula is", f'{"s" if solver.solve() else "uns"}atisfiable')


if __name__ == "__main__":
    main()
