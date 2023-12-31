341. Палеты

    средняяimplementationdata structuresfirst_2023_backend

Поставки товаров прибывают в распределительный центр, хранятся там и затем отправляются на склады. Каждая поставка состоит из множества палет и коробок (возможно, пустого). Все палеты и коробки имеют deliveryiddeliveryid​ — идентификатор поставки.

Палеты и коробки имеют поле parentidparentid​ — это идентификатор палеты или коробки, в которую вложена данная. Если parentid=0parentid​=0, то это палета, иначе — коробка. Отправлять на склад можно только палеты. Чтобы палеты и коробки можно было отправить на склад, должны выполняться следующие условия:

    Коробку, не размещённую в палете или другой коробке, отправлять нельзя;
    Если существует коробка, которая ещё не пришла от поставщиков или которую нельзя отправить, то нельзя отправить на склад и коробку или палету, в которую она вложена.

Зная, что в данный момент прибыли только поставки с определенными номерами, определите, какие палеты возможно отправить на склад уже сейчас.
Формат ввода

В первой строке задано одно целое число n (1≤n≤106) — общее количество палет и коробок.

Во второй строке записано nn целых чисел deliveryid​ (1≤deliveryid​≤109) — идентификаторы поставки.

В третьей строке записано nn целых чисел parentid​ (0≤parentid​≤n) — номера коробок, в которые должна быть вложена палета или другая коробка. Коробка не может быть вложена сама в себя (в том числе через другие коробки). Если parentid​=0, то это палета и её никуда класть не нужно.

В четвертой строке задано единственное целое число k (0≤k≤n) — количество поставок, которые ещё не приехали в распределительный центр.

При k≥1 в последней строке записано k целых чисел ai​ (1≤ai​≤109) — идентификаторы поставок, палеты и коробки из которых не были доставлены в распределительный центр. Гарантируется, что хотя бы одна палета или коробка имела такой идентификатор ai​.

Формат вывода

В первой строке выведите одно целое число m — количество палет, которые можно отправить на склад.

Во второй строке выведите номера палет от меньшего к большему.

[Решение](solution.cpp)