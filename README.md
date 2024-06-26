# comp-club-task
Решение тестового задания для вакансии "Инженер по разработке ПО для базовых станций (С++)"

## Сборка и запуск
Проверка работы программы происходила на компиляторе g++ (MinGW-W64 x86_64-msvcrt-posix-seh, built by Brecht Sanders) 13.1.0

Сборка осуществляется следующим образом:
```sh
$ g++ -c main.cpp functions.cpp
$ g++ -o task.exe main.o functions.o
```

Запуск:
```sh
$ task.exe test_file.txt
```

## Тестовые примеры

### Тест 1
Вход:
```
3
09:00 19:00
10
08:48 1 client1
09:41 1 client1
09:48 1 client2
09:52 3 client1
09:54 2 client1 1
10:25 2 client2 2
10:58 1 client3
10:59 2 client3 3
11:30 1 client4
11:35 2 client4 2
11:45 3 client4
12:33 4 client1
12:43 4 client2
15:52 4 client4
```

Выход:
```
09:00
08:48 1 client1
08:48 13 NotOpenYet
09:41 1 client1
09:48 1 client2
09:52 3 client1
09:52 13 ICanWaitNoLonger!
09:54 2 client1 1
10:25 2 client2 2
10:58 1 client3
10:59 2 client3 3
11:30 1 client4
11:35 2 client4 2
11:35 13 PlaceIsBusy
11:45 3 client4
12:33 4 client1
12:33 12 client4 1
12:43 4 client2
15:52 4 client4
19:00 11 client3
19:00
1 70 05:58
2 30 02:18
3 90 08:01
```

### Тест 2
Вход:
```
3
9:00 12:00
10
11:00 1 cl1
```

Выход:
```
9:00 12:00
```

Пояснение: неправильный формат времени

### Тест 3
Вход:
```
3
10:00 19:00
10
11:00 1 cl1
12:00 2 cl1 4
```

Выход:
```
12:00 2 cl1 4
```

Пояснение: номер стола больше общего количества столов

### Тест 4
Вход:
```
3
10:00 19:00
10
12:00 1 cl1
11:00 1 cl2
```

Выход:
```
11:00 1 cl2
```

Пояснение: события идут непоследовательно по времени

### Тест 5
Вход:
```
3
19:00 10:00
10
12:00 1 cl1
```

Выход:
```
19:00 10:00
```

Пояснение: время открытия больше времени закрытия (считаю, что события происходят в один и тот же день, поэтому случай ночной смены не учитывается)

### Тест 6
Вход:
```
1
10:00 19:00
1
10:00 1 vasya
11:00 1 007
12:00 1 zina
13:00 1 -anonim__
14:00 1 anton
```

Выход:
```
10:00
10:00 1 vasya
11:00 1 007
12:00 1 zina
13:00 1 -anonim__
14:00 1 anton
19:00 11 -anonim__
19:00 11 007
19:00 11 anton
19:00 11 vasya
19:00 11 zina
19:00
1 0 00:00
```

### Тест 7
Вход:
```
2
10:00 19:00
10
10:00 1 cl1
11:00 2 cl1 1
11:05 2 cl1 2
12:05 4 cl1
```

Выход:
```
10:00
10:00 1 cl1
11:00 2 cl1 1
11:05 2 cl1 2
12:05 4 cl1
19:00
1 10 00:05
2 10 01:00
```

### Тест 8
Вход:
```
2
10:00 19:00
10
10:00 1 cl1
11:00 2 cl1 1
11:05 2 cl1 2
12:00 1 cl2
12:05 2 cl2 1
```

Выход:
```
10:00
10:00 1 cl1
11:00 2 cl1 1
11:05 2 cl1 2
12:00 1 cl2
12:05 2 cl2 1
19:00 11 cl1
19:00 11 cl2
19:00
1 80 07:00
2 80 07:55
```

### Тест 9
Вход:
```
1
10:00 19:00
10
10:00 1 cl1
11:00 2 cl1 1
12:00 1 cl2
13:00 3 cl2
14:00 1 cl3
15:00 3 cl3
```

Выход:
```
10:00
10:00 1 cl1
11:00 2 cl1 1
12:00 1 cl2
13:00 3 cl2
14:00 1 cl3
15:00 3 cl3
15:00 11 cl3
19:00 11 cl1
19:00 11 cl2
19:00
1 80 08:00
```

### Тест 10
Вход:
```
1
10:00 19:00
10
10:00 1 cl1
11:00 2 cl2 1
12:00 1 cl1
```

Выход:
```
10:00
10:00 1 cl1
11:00 2 cl2 1
11:00 13 ClientUnknown
12:00 1 cl1
12:00 13 YouShallNotPass
19:00 11 cl1
19:00
1 0 00:00
```

### Тест 11
Вход:
```
1
10:00 19:00
10
10:00 1 cl1
23:00 1 cl2
```

Выход:
```
10:00
10:00 1 cl1
19:00 11 cl1
23:00 1 cl2
23:00 13 NotOpenYet
19:00
1 0 00:00
```
