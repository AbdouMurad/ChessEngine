with open("zobrist_hash.txt") as f:
    numbers = [line.strip() for line in f.readlines()]

with open("zobrist_array.c", "w") as f:
    f.write("uint64_t zobristTable[768] = {\n")
    for i, num in enumerate(numbers):
        f.write(f"    0x{int(num):016x},")
        if (i + 1) % 4 == 0:
            f.write("\n")
        else:
            f.write(" ")
    f.write("};\n")
