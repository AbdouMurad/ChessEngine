import random

pieces = {"wp", "wk", "wb", "wr", "wq", "wK",
            "bp", "bk", "bb", "br","bq", "bK"}

with open("zorbrist_hash.txt", "w") as f:
    for piece in pieces:
        for i in range(64):
            key = random.getrandbits(64)
            f.write(f"{key}\n")
