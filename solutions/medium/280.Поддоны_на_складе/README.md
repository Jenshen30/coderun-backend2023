280. Поддоны на складе


На складе Яндекс Маркета есть n разных поддонов. У каждого поддона есть длина и ширина. Поддоны можно поворачивать на 90 градусов.

Поддон p можно поставить на поддон q, только если p целиком помещается на q. Это означает, что длина и ширина поддона p должны быть строго меньше длины и ширины поддона q.

Найдите количество поддонов, которые нельзя поставить ни на один другой поддон.

Формат ввода

Первая строка содержит одно целое число n (2≤n≤300 000) — количество поддонов на складе.

Следующие n строк содержат по два целых числа wi​ и hi​ (1≤wi​,hi​≤109) — ширина и длина i-го поддона соответственно.

Формат вывода

Выведите одно целое число — количество поддонов, которые нельзя поставить ни на один другой.

Примечание

Разберём пример из условия:

    Первый поддон можно поставить на третий и четвёртый поддон, не переворачивая.
    Второй поддон можно поставить на третий поддон.
    Третий поддон нельзя поставить ни на один другой поддон, так как у всех других поддонов минимальная координата меньше 5.
    Четвёртый поддон нельзя поставить ни на один другой поддон, так как у всех других поддонов максимальная координата меньше 6.

[Решение](solution.cpp)