https://github.com/okovtun/PV_521.git
https://www.youtube.com/playlist?list=PLeqyOOqxeiINwoETYVNufASRa3i53K2Gb

https://stamina-online.com/ru/lessons/ru
https://www.typingstudy.com/ru-lao-1/numeric_keypad

/////////////////////////////////////////////////////////////////////////////////
/////////////////				DATA CONTAINERS						/////////////
/////////////////////////////////////////////////////////////////////////////////

Time:
	https://legacy.cplusplus.com/reference/ctime/
	https://legacy.cplusplus.com/reference/ctime/clock/
	https://legacy.cplusplus.com/reference/ctime/CLOCKS_PER_SEC/

TODO:
1. Создать список заданное число элементов следующим образом:
	ForwardList list(5);

2. Перегрузить оператор []:
	for(int i=0; i<list.get_size(); i++)
		list[i] = rand()%100;
	for(int i=0; i<list.get_size(); i++)
		cout << list[i] << tab;
	cout << endl;

3. Провести тест производительности оператора [];
4. Реализовать MoveSemantic (The Rule Of five) в классе 'ForwardList';
5. Протестировать производительность Copy-методов;
6. Оптимизировать производительность Copy-методов;

DONE:
1. Решить проблему с выходом за пределы списка в методе insert();
2. Написать метод erase();
3. Деструктор списка должен полностью очищать список;
4. ForwardList fusion = list1 + list2;
   fusion.print();

DONE:
В класс 'ForwardList' добавить следующие методы:
1. push_back();
2. pop_front();
3. pop_back();
4. insert();
5. erase();

/////////////////////////////////////////////////////////////////////////////////
/////////////////				  INHERITANCE						/////////////
/////////////////////////////////////////////////////////////////////////////////

CSV

TODO:
1. Добить иерархию треугольников;
2. Создать ветку 'Geometry_HW_3';
3. Вынести код, создающий инструменты для рисования в Базовый класс;

DONE:
0. Сделать COMMIT и создать ветку 'Geometry_HW_2';
1. Добавить инкапсуляцию для первичных размеров фигур;
2. Написать класс 'Circle':
	https://learn.microsoft.com/en-us/windows/win32/gdi/filled-shapes

Продолжить задачу в ветке 'Abstract_HW_1':
Реализовать иерархию геометрических фигур: квадрат, треугольник, круг, прямоугольник.....
Для каждой фигуры должны выводиться ее первичные ствойства, такие как: длина стороны квадрата,
радиус круга и т.д., и вторичные свойства, такие как: площадь и периметр.
Так же, должна быть возможность нарисовать каждую фигуру.

DONE:
От ветки 'master' создать векту 'LoadHW', и в ней попробовать добить функцию Load();
-----------------------------------------------
Прочитать группу из файла, в результате чего должен появиться такой же массив объектов, 
как мы создавали в main().

DONE:
1. В проект 'Academy' добавить класс 'Graduate' (Дипломник);
2. Залить репу на GitHub, и прислать ссылку;

DONE:
1. В ветке 'StringSeparation' вынести в отдельные файлы классы
   'Point' и 'Fraction';
2. От ветки 'StringSeparation' создать ветку 'LIBs', и в ней,
   собрать и проверить статические библиотеки для классов:
	'Point', 'Fraction' и 'String';

DONE:
1. Теория;

DONE:
1. Выучить теорию;
2. Написать CopyAssignment;
3. В Solution 'IntroductionToOOP' добавить проект Matrix, и в нем реализовать класс Matrix,
   описывающий Матрицу.
   В классе должны быть все необходимые методы и операции (+, -, *, /);

DONE:
В Solution 'IntroductionToOOP' добавить проект 'String' и в этом проекте реализовать 
класс 'String', который способен выполнять следующие операции:
	String str1 = "Hello";
	String str2 = "World";
	String str3 = str1 + str2;
	cout << str3 << endl;

DONE:
0. !!!!!!! Выучить теорию !!!!!!!
1. Проверочный код в секции 'STREAMS_CHECK' должен заработать:
	https://github.com/okovtun/PV_521/blob/35173b38f18dedc52c6e5b449c55a1dddc84c68e/IntroductionToOOP/Fraction/main.cpp#L345C1-L350C24
2. Проверочный код в секции 'CONVERSIONS_FROM_CLASS_TO_OTHER' должен заработать:
	https://github.com/okovtun/PV_521/blob/54dc1005e6a623fb1476c732c23d7b5bdec858b0/IntroductionToOOP/Fraction/main.cpp#L414-L416
3. Проверочный код в секции 'HAVE_A_NICE_DAY' должен заработать:					DONE
	https://github.com/okovtun/PV_521/blob/54dc1005e6a623fb1476c732c23d7b5bdec858b0/IntroductionToOOP/Fraction/main.cpp#L419C1-L423C1

DONE:
0. !!!!!!! Выучить теорию !!!!!!!
1. Для класса 'Fraction' перегрузить все арифметические операторы:	/, +, -;
2. Перегрузить составные присваивания: +=, -=, *=, /=;
3. Перегрузить Incremento/Decremento (++/--);
4. Перегрузить операторы сравнения: ==, !=, >, <, >=, <=;

DONE:
0. !!!!!!! Выучить теорию !!!!!!!
1. В проекте 'IntroductionToOOP' реализовать метод   ??? distance(???),
   который возвращает расстояние ДО УКАЗАННОЙ ТОЧКИ;		DONE
2. В проекте 'IntroductionToOOP' реализовать функцию ??? distance(???),
   которая возвращает расстояние МЕЖДУ ДВУМЯ ТОЧКАМИ;