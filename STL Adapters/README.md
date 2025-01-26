# Библиотека адаптеров для упрощенной работы с алгоритмами и контейнерами.
## Требования:
Адаптеры должны применяться к контейнерам, и выдвигать собственные требования к ним, которые должны проверяться с помощью метода static_assert
- transform - изменяют значения элементов наподобие того как это делает алгоритм transform
- filter - фильтрация по определенному признаку, признак передается в качестве аргумента
- take - берет только N первых элементов
- drop - пропускаем N первых элементов
- reverse - реверсия
- keys - ключи для ассоциативных контейнеров
- values - значения для ассоциативных контейнеров
## Пример:
Зачастую стоит задача применения нескольких алгоритмов одновременно, например:
```rb
std::vector<int> v = {1,2,3,4,5,6};
std::vector<int> result;

std::copy_if(v.begin(), v.end(), std::back_inserter(result), [](int i){return i % 2;});
std::transform(result.begin(), result.end(), result.begin(), [](int i){return i * i;});

for(int i : result)
    std::cout << i << " ";
```
Эту задачу можно было бы решить более "элегантно":
```rb
std::vector<int> v = {1,2,3,4,5,6};

auto removed = v | filter([](int i){return i % 2;});
auto result = removed | transform([](int i){return i * i;});

for(int i : result)
    std::cout << i << " ";
```
или еще более коротко, использовав конвейер, наподобие того как это принято в unix-системах:
```rb
std::vector<int> v = {1,2,3,4,5,6};

for(int i : v | filter([](int i){return i % 2;}) | transform([](int i){return i * i;}))
     std::cout << i << " ";
```
