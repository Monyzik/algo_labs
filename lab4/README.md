## Лабораторная работа №4

### Сбалансированные деревья

ФИО: Кобылкевич Фёдор Максимович

Группа: М8О-102БВ-25

#### Постановка задачи:

Построить упорядоченное AVL-дерево для хранения и поиска элементов с
уникальными строковыми ключами и вещественными значениями. Ключ –
непустая последовательность латинских букв не более чем из 6 символов.

#### Описание работ:

Будем поддерживать в каждом узле высоту поддерева. При добавлении и удалении вершин может получится ситуация, когда у
нас высота сыновей будет отличаться более чем на 2 будем производить выравнивание дерева с помощью 4 операций: правого
малого поворота, левого малого поворота, правого большого поворота и левого большого поворота. После этого действия
обновим значение высот у поддерева. Поиск и вывод реализуем аналогично бинарному дереву, так как авл дерево также
поддерживает инвариант бинарного дерева. 

#### Запуск:

```commandline
cmake ./cmake-build-debug 
./cmake-build-debug/lab4
```

Для запуска тестов достаточно в корне лабораторной работы выполнить (после build-а):

```commandline
./cmake-build-debug/tests_lab4 
```

Для запуска бенчмарков:

```commandline
./cmake-build-debug/lab4_bench
```

#### Примеры работы:

```text
1 qwerty 3.14
1 asdf 5.0
3
qwerty 3.1400
  asdf 5.0000
1 dyz 4.5
1 uiop 7.7777
3
dyz 4.5000
  asdf 5.0000
  qwerty 3.1400
    uiop 7.7777
4 asdf
Значение: 5.0000
2 dyz
3
qwerty 3.1400
  asdf 5.0000
  uiop 7.7777
4 qwerty
Значение: 3.1400
-1
```

### Бенчмарки

Бенчмарки проводились на устройстве:

```text
PC Model: Mac16,8
ОС Version: Tahoe 26.4

Run on (14 X 23.9995 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB
  L1 Instruction 128 KiB
  L2 Unified 4096 KiB (x14)

CPU Model: Apple M4 Pro
RAM Memory: 24 GB
RAM Type: LPDDR5

```

```text
-----------------------------------------------------------------------
Benchmark                             Time             CPU   Iterations
-----------------------------------------------------------------------
AVLInsertBenchmark/1000             221 ns          221 ns      3107755
AVLInsertBenchmark/10000            386 ns          385 ns      1901802
AVLInsertBenchmark/100000           551 ns          550 ns      1154811
AVLInsertBenchmark_BigO           29.87 lgN       29.83 lgN  
AVLInsertBenchmark_RMS               14 %            14 %    
StdMapInsertBenchmark/1000          535 ns          534 ns      1172431
StdMapInsertBenchmark/10000         718 ns          718 ns       827560
StdMapInsertBenchmark/100000        910 ns          910 ns       801723
StdMapInsertBenchmark_BigO        54.35 lgN       54.32 lgN  
StdMapInsertBenchmark_RMS             1 %             1 %    
AVLFindBenchmark/1000               118 ns          118 ns      5831632
AVLFindBenchmark/10000              186 ns          186 ns      3730071
AVLFindBenchmark/100000             279 ns          278 ns      2536498
AVLFindBenchmark_BigO             15.01 lgN       15.01 lgN  
AVLFindBenchmark_RMS                 13 %            13 %    
StdMapFindBenchmark/1000            320 ns          320 ns      2187644
StdMapFindBenchmark/10000           427 ns          427 ns      1643474
StdMapFindBenchmark/100000          651 ns          650 ns      1193785
StdMapFindBenchmark_BigO          35.67 lgN       35.62 lgN  
StdMapFindBenchmark_RMS              10 %            10 %    
AVLEraseBenchmark/1000             21.0 ns         21.0 ns     33446894
AVLEraseBenchmark/10000            23.2 ns         23.1 ns     28902211
AVLEraseBenchmark/100000           36.1 ns         36.1 ns     16823786
AVLEraseBenchmark_BigO             2.02 lgN        2.02 lgN  
AVLEraseBenchmark_RMS                10 %            10 %    
StdMapEraseBenchmark/1000          45.0 ns         45.0 ns     15589680
StdMapEraseBenchmark/10000         46.6 ns         46.6 ns     14818018
StdMapEraseBenchmark/100000         140 ns          139 ns      3854246
StdMapEraseBenchmark_BigO          6.14 lgN        6.13 lgN  
StdMapEraseBenchmark_RMS             40 %            40 %    
```

Все бенчмарки и их результаты сохранены в файле ***report.json***

#### Выводы

Научились строить сбалансированные деревья,
а также поддерживать их инвариант при вставке и удалении.
Научились выполнять над ними элементарные операции поиска и вывода. 
