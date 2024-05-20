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
