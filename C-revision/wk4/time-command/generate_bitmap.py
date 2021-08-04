import subprocess as sp
import shlex

from pathlib import Path

def save_file(path: str, pattern: str, rep: int, nrows: int):
    with open(path, "w") as f:
        for i in range(nrows):
            if i == nrows - 1:
                f.write(f"{pattern * rep}")
            else:
                f.write(f"{pattern * rep}\n")


if __name__ == "__main__":
    rep = 4
    pattern = "00111100"
    nrows = 8

    f = open("times-unrolling.txt", "w")
    for i in range(1, 12):
        rep *= 2
        nrows *= 2
        print(f"rep: {rep} || nrows: {nrows}")
        path = Path(f"./bitmap-rep-{rep}-nrows-{nrows}.txt")
        save_file(
            path=path,
            pattern=pattern,
            rep=rep,
            nrows=nrows
        )

        i = 1
        j = 2
        s = "        "
        while i < rep and j < nrows:
            command_args = shlex.split(f"time ./test_time.out {path} {rep} {nrows} {i} {j} ")
            process = sp.run(
                args=command_args,
                stdout=sp.PIPE,
                stderr=sp.PIPE,
                universal_newlines=True
            )
            i *= 2
            j *= 2
            f.write(f"{rep*nrows}{s}{i}-{j}{process.stderr}")
            print(f"stdout: {process.stdout}")
            print(f"stderr: {process.stderr}")
            # print(f"check_returncode():\n{process.check_returncode()}")

    f.close()
