# Lab 1
Разработать программу на языке С, которая осуществляет следующие действия

 * Создает область памяти размером 221 мегабайт, начинающихся с адреса 0xF8555978 при помощи mmap заполненную случайными числами /dev/urandom в 92 потоков. Используя системные средства мониторинга определите адрес начала в адресном пространстве процесса и характеристики выделенных участков памяти. Замеры виртуальной/физической памяти необходимо снять:
   1. До аллокации
   2. После аллокации
   3. После заполнения участка данными
   4. После деаллокации
 * Записывает область памяти в файлы одинакового размера 133 мегабайт с использованием блочного обращения к диску. Размер блока ввода-вывода G байт. Преподаватель выдает в качестве задания последовательность записи/чтения блоков последовательный
 * Генерацию данных и запись осуществлять в бесконечном цикле.
 * В отдельных 65 потоках осуществлять чтение данных из файлов и подсчитывать агрегированные характеристики данных - максимальное.
 * Чтение и запись данных в/из файла должна быть защищена примитивами синхронизации flock.
 * По заданию преподавателя изменить приоритеты потоков и описать изменения в характеристиках программы. 

Для запуска программы возможно использовать операционную систему Windows 10 или  Debian/Ubuntu в виртуальном окружении. 

Измерить значения затраченного процессорного времени на выполнение программы и на операции ввода-вывода используя системные утилиты.

Отследить трассу системных вызовов. 

Используя stap построить графики системных характеристик. 
