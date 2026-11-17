import math

PHRASE = "Не клади всі яйця в один кошик, щоб не втратити все одразу"
ALPHABET = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя"
POS = {ch: i + 1 for i, ch in enumerate(ALPHABET)}
A = (math.sqrt(5) - 1) / 2

# Ключі: слова у нижньому регістрі, дублікати ("Не"/"не") пропускаємо
WORDS = []
for w in PHRASE.replace(",", "").lower().split():
    if w not in WORDS:
        WORDS.append(w)

def key_sum(w):
    return sum(POS[c] for c in w)

def h_div(w, m=13):
    return key_sum(w) % m

def h_mul(w, m=16):
    return int(m * ((key_sum(w) * A) % 1))

# ---------- Відкрите хешування (ланцюжки) ----------
def build_chain(words, h, m):
    t = [[] for _ in range(m)]
    for w in words:
        t[h(w)].append(w)
    return t

def chain_cmp(t, w, h):
    return t[h(w)].index(w) + 1          # порівнянь при успішному пошуку

# ---------- Закрите хешування (лінійне дослідження) ----------
def build_open_addr(words, h, m):
    t = [None] * m
    for w in words:
        for i in range(m):
            j = (h(w) + i) % m
            if t[j] is None:
                t[j] = w
                break
        else:
            print("Переповнення:", w)
    return t

def probe_cmp(t, w, h, m):
    for i in range(m):
        j = (h(w) + i) % m
        if t[j] == w:
            return i + 1
    return None

if __name__ == "__main__":
    print("Ключі:", WORDS, len(WORDS))
    print(f"{'слово':10}{'Σ':>4}{'k mod 13':>10}{'⌊16·{kA}⌋':>12}")
    for w in WORDS:
        print(f"{w:10}{key_sum(w):>4}{h_div(w):>10}{h_mul(w):>12}")

    for name, h, m in (("ДІЛЕННЯ m=13", h_div, 13), ("МНОЖЕННЯ m=16", h_mul, 16)):
        print("\n=====", name, "=====")
        ch = build_chain(WORDS, h, m)
        print("-- Ланцюжки --")
        for i, c in enumerate(ch):
            print(f"{i:02d}: {c}")
        cs = {w: chain_cmp(ch, w, h) for w in WORDS}
        print(cs, "max:", max(cs, key=cs.get), max(cs.values()),
              "avg: %.3f" % (sum(cs.values()) / len(cs)))

        oa = build_open_addr(WORDS, h, m)
        print("-- Відкрита адресація --")
        for i, c in enumerate(oa):
            print(f"{i:02d}: {c}")
        ps = {w: probe_cmp(oa, w, h, m) for w in WORDS}
        print(ps, "max:", max(ps, key=ps.get), max(ps.values()),
              "avg: %.3f" % (sum(ps.values()) / len(ps)))
