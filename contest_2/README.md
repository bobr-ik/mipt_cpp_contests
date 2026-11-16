# Проект «ФизКат»

Консольное приложение для учёта парка прокатной техники и инвентаря. Реализовано в рамках Домашнего задания №2 по курсу C++.

## 1. Как собрать и запустить

Для сборки проекта используется компилятор `g++` (стандарт C++17 или выше). 
Из корневой директории проекта (где лежит `main.cpp` и папки `include/`, `src/`) выполните команду:

```bash
g++ -std=c++17 main.cpp src/*.cpp -Iinclude -o fleet
./fleet
```

## 2. Схема наследования

В проекте используется абстрактный базис и множественное наследование.

```text
InventoryItem (Абстрактный базис, чисто виртуальный getDescription)
 ├── Transport (Абстрактный, добавляет difficulty_score)
 │    ├── Scooter (Самокат) : public EnergyConsumer
 │    └── Bike (Обычный велосипед)
 │          └── EBike (Электровелосипед) : public EnergyConsumer
 │
 ├── Helmet (Вещь, не потребляет энергию)
 │
 └── DockStation (Вещь) : public InventoryItem, public EnergyConsumer

EnergyConsumer (Интерфейс, чисто виртуальный getEnergyConsumption)
```
*   **Множественное наследование:** Реализовано в классах `EBike` и `Scooter` (наследуют свойства транспорта и интерфейс потребителя энергии), а также в `DockStation`.
*   **Virtual inheritance:** В текущей архитектуре ромбовидного наследования (Diamond problem) не возникает, так как `Bike` не наследует `EnergyConsumer`. Поэтому `virtual` наследование не требуется.

## 3. Использование умных указателей (Smart Pointers)

*   **`std::unique_ptr`**: Используется в `CmdReader` при парсинге команды `add` для создания объекта в куче до прохождения техосмотра. Если `ServiceCenter::inspect` выбрасывает исключение, `unique_ptr` автоматически уничтожает объект (строгая гарантия безопасности исключений). Если проверка пройдена — владение передаётся в парк через `std::move`.
*   **`std::shared_ptr`**: Используется в классе `Fleet` для хранения парка: `std::vector<std::shared_ptr<InventoryItem>> items`. Это позволяет объектам иметь общее владение (например, для витрины) и гарантирует, что объект будет жить, пока на него есть ссылки.
*   **`std::weak_ptr`**: Используется в классе `Fleet` для «витрины» (`weak_ptr<InventoryItem> focus_item`). Витрина не владеет объектом, а только наблюдает за ним. Если объект удаляют из парка, `shared_ptr` уничтожается, и `weak_ptr` при вызове `.lock()` возвращает `nullptr` (свойство `expired`).

## 4. Исключения

Все исключения наследуются от базового класса `FleetOperationError : public std::exception` (в файле `Errors.hpp`). Внутри доменных операций используется `throw`, а перехват (`catch`) происходит в `main.cpp` или `CmdReader`.

*   `InspectionError`: Бросается в `ServiceCenter::inspect`, если имя предмета содержит запрещенное слово (например, "broken").
*   `InvalidArgument`: Бросается при некорректном вводе (неизвестный тип команды, отрицательная энергия и т.д.).
*   `FocusError` / `RemoveError`: Бросаются, если запрошенный ID не найден в парке.
*   `Quit`: Бросается для корректного выхода из главного цикла программы.

## 5. Шаблоны

В файле `include/Registry.hpp` реализован шаблонный класс `Registry<T, Cap>`. 
Это «журнал» с фиксированной вместимостью `Cap`, который хранит последние добавленные элементы и умеет их выводить (`operator<<`).

**Где используется:**
В классе `Fleet` созданы два экземпляра:
1. `Registry<std::string, 5> event_log;` — журнал последних 5 текстовых событий (добавление, удаление).
2. `Registry<std::shared_ptr<InventoryItem>, 3> recent_items;` — реестр последних 3 добавленных или зафиксированных на витрине единиц техники (демонстрирует работу шаблона).


## 6. Список поддерживаемых команд

Приложение работает в интерактивном режиме. Введите команду и нажмите `Enter`. 
Если аргумент содержит пробелы (например, имя), он не поддерживается текущим парсером (считывание идет до первого пробела).

| Команда | Формат ввода | Описание |
| :--- | :--- | :--- |
| **Добавление техники** | | |
| `add bike` | `add bike <id> <name> <score>` | Добавить обычный велосипед (сложность 1..10). |
| `add ebike` | `add ebike <id> <name> <energy> <score>` | Добавить электровелосипед (энергия кВт·ч/сутки, сложность 1..10). |
| `add scooter` | `add scooter <id> <name> <energy> <score>` | Добавить электросамокат (энергия кВт·ч/сутки, сложность 1..10). |
| **Добавление вещей** | | |
| `add helmet` | `add helmet <id> <name>` | Добавить шлем на баланс (не потребляет энергию). |
| `add dockstation`| `add dockstation <id> <name> <energy>` | Добавить док-станцию (потребляет энергию). |
| **Отчёты и информация** | | |
| `list` | `list` | Вывести все позиции на балансе (отсортировано по инвентарному номеру). |
| `energy` | `energy` | Вывести суммарное суточное энергопотребление парка (с 1 знаком после запятой). |
| `novice` | `novice` | Вывести список техники, подходящей новичкам (сложность <= 5 !! ОТКЛОНЕНИЕ ОТ ТЗ !!). |
| `recent` | `recent` | *(Креатив)* Показать 3 последних добавленных единицы техники. |
| `log` | `log` | *(Креатив)* Показать журнал последних 5 событий парка (добавления, удаления, фокус). |
| **Управление витриной** | | |
| `focus` | `focus <id>` | Поставить выбранную единицу техники на «витрину» (самокат дня). |
| `show_focus` | `show_focus` | Показать, что сейчас на витрине. Если объект удален — выведет `Expired`. |
| **Удаление и выход** | | |
| `remove` | `remove <id>` | Удалить позицию из парка по инвентарному номеру. |
| `quit` | `quit` | Завершить работу приложения. |

> **Примечание:** При добавлении транспорта (bike, ebike, scooter) автоматически запускается техосмотр. Если в имени содержится подстрока `broken` (без учета регистра), техосмотр отклоняет устройство, выводится ошибка, и в парк оно не попадает.

## 7. Креативная часть

В качестве дополнительных операций реализованы команды **`log`** и **`recent`**. 
Они выводят историю последних действий, используя шаблонный класс `Registry`. Это позволяет отслеживать, что происходило в парке, не засоряя основной список инвентаря. Вся логика инкапсулирована в `Fleet::printLog()`.

### 8. Пример использования

Скопируйте и вставьте эти команды в консоль для проверки всех функций:

```text
add scooter S-1 ModelX 2.5 8
add bike B-1 City 4
add helmet H-1 Pro
add dockstation D-1 Hub 10.0
add ebike E-1 Speedster 1.5 7
add scooter S-2 BrokenX 1.0 9
add scooter S-3 BadScore 2.0 12
energy
novice
list
focus S-1
show_focus
remove S-1
show_focus
list
log
recent
quit
```

```text
error: Inspection error. Item with name BrokenX and id S-2 is not valid
error: Invalid argument. invalid difficulty score 
14
Bike. id: B-1, name: City, difficulty_score: 4.0
Bike. id: B-1, name: City, difficulty_score: 4.0
DockStation. id: D-1, name: Hub, energy_consumption: 10.0
EBike. id: E-1, name: Speedster, difficulty_score: 7.0, energy_consumption: 1.5
Helmet. id: H-1, name: Pro
Scooter. id: S-1, name: ModelX, difficulty_score: 8.0, energy_consumption: 2.5
Scooter. id: S-1, name: ModelX, difficulty_score: 8.0, energy_consumption: 2.5
Scooter. id: S-1, name: ModelX, difficulty_score: 8.0, energy_consumption: 2.5
Bike. id: B-1, name: City, difficulty_score: 4.0
DockStation. id: D-1, name: Hub, energy_consumption: 10.0
EBike. id: E-1, name: Speedster, difficulty_score: 7.0, energy_consumption: 1.5
Helmet. id: H-1, name: Pro
--- Event Log ---
Added: H-1
Added: D-1
Added: E-1
Focused: S-1
Removed: S-1
-----------------
--- Recent Items ---
DockStation. id: D-1, name: Hub, energy_consumption: 10.0
EBike. id: E-1, name: Speedster, difficulty_score: 7.0, energy_consumption: 1.5
Scooter. id: S-1, name: ModelX, difficulty_score: 8.0, energy_consumption: 2.5
--------------------
```


## 8. Использование ИИ

При выполнении задания использовались инструменты на базе ИИ (например, ChatGPT / DeepSeek) для следующих целей:
*   Обсуждение архитектуры умных указателей (как правильно передавать `unique_ptr` в `shared_ptr`).
*   Помощь в написании README.md, потому что я не умею красиво рисовать схемы из палочек, это сложно

Весь основной код был написан и протестирован самостоятельно.
