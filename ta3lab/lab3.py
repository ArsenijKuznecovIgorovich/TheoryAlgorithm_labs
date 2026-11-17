comp = 0      # для підрахунку порівнянь
assign = 0    # для підрахунку присвоювань

def swap(arr, i, j):
    """Міняє місцями два елементи в масиві."""
    global assign
    arr[i], arr[j] = arr[j], arr[i]
    assign += 3

def sink(arr, i, n):
    """
    Процедура 'занурення' елемента вниз по купі.
    """
    global comp, assign
    k = i
    while True:
        j = 2 * k + 1
        if j >= n:
            break
        comp += 1
        if j + 1 < n and arr[j + 1] > arr[j]:
            j += 1
        comp += 1
        if arr[k] >= arr[j]:
            break
        swap(arr, k, j)
        k = j

def heapsort(arr):
    """Алгоритм пірамідального сортування."""
    n = len(arr)
    print(f"Початковий масив: {arr}\n")

    # Побудова максимальної купи
    print("Побудова максимальної купи")
    for i in range(n // 2 - 1, -1, -1):
        print(f"Занурюємо елемент з індексу {i}: {arr[i]}")
        sink(arr, i, n)
    print(f"\nМасив після побудови купи: {arr}\n")

    # Сортування
    print("Сортування")
    for i in range(n - 1, 0, -1):
        print(f"Міняємо місцями корінь ({arr[0]}) та останній елемент ({arr[i]})")
        swap(arr, 0, i)
        n -= 1
        print(f"Розмір купи зменшився до {n}. Відновлюємо властивості купи.")
        sink(arr, 0, n)
        print(f"Масив на поточному кроці: {arr}\n")
    return arr

A = [10, 90, 95, 30, 45, 60, 57, 28, 5]
sorted_A = heapsort(A)
print(f"Відсортований масив: {sorted_A}")
print(f"Кількість порівнянь: {comp}")
print(f"Кількість присвоювань: {assign}")
