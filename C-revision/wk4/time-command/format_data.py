

if __name__ == "__main__":
    reps = 4
    nrows = 8
    dim = []
    for i in range(1, 12):
        reps *= 2
        nrows *= 2
        dim.append(str(reps*nrows))
    print(f"dim: {dim}")
    resize_dim = "16-32"
    s = "        "

    arr = []
    with open("times-unrolling.txt", "r") as f:
        data = f.readlines()
        for line in data:
            # print(f"line: {line}")
            elements = line.split(s)
            # print(f"elements: {elements}")
            if elements[1] == resize_dim:
                print(f"elements: {elements}")
                e2 = elements[2].split(" ")[0]
                # There are 9 spaces between the outputs of "time"
                e3 = elements[3].split(" ")[1]
                e4 = elements[4].split(" ")[1]
                total_time = float(e2) + float(e3) + float(e4)
                arr.append([
                    elements[0],
                    elements[1],
                    e2, e3, e4,
                    str(round(total_time, 2))
                ])

    print(arr)
    with open(f"times-{resize_dim}.txt", "w") as f:
        f.write("# dimensions row-col real user sys total\n")
        for e in arr:
            f.write(" ".join(e) + "\n")

