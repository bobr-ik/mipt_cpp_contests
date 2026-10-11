#include <iostream>

// Задача: учёт продаж и возвратов товаров по регионам, месяцам и товарам.
//
// int*** data — трёхмерная таблица [регион][месяц][товар] для подсчёта
//   проданных единиц. Без трёх уровней пришлось бы вручную считать
//   плоский индекс (r*MONTHS + m)*PRODUCTS + p и легко ошибиться.
//
// void* payload — событие может нести SaleInfo или ReturnInfo, тип
//   заранее неизвестен. Без void* пришлось бы делать
//   отдельные поля под каждый тип события.

enum class EventType {
  EV_SALE = 0,   // payload включает в себя SaleInfo
  EV_RETURN = 1  // payload включает в себя Return_info
};

struct SaleInfo {
  int price;
  int region;
  int month;
  int product_id;
  const char* buyer_name;
};

struct ReturnInfo {
  int price;
  int region;
  int month;
  int product_id;
  const char* buyer_name;
  char* return_reason;
};

struct Event {
  EventType type;
  void* payload;
};

int main() {
  const int REGIONS = 10;
  const int MONTHS = 12;
  const int PRODUCTS = 200;

  int*** data = new int**[REGIONS];
  for (int r = 0; r < REGIONS; ++r) {
    data[r] = new int*[MONTHS];
    for (int m = 0; m < MONTHS; ++m) {
      data[r][m] = new int[PRODUCTS];
      for (int p = 0; p < PRODUCTS; ++p) data[r][m][p] = 0;
    }
  }

  Event events[2];

  events[0].type = EventType::EV_SALE;
  SaleInfo event_payload_0{.price = 100,
                           .region = 1,
                           .month = 1,
                           .product_id = 0,
                           .buyer_name = "Yaroslav"};
  events[0].payload = &event_payload_0;

  events[1].type = EventType::EV_RETURN;
  ReturnInfo event_payload_1{.price = 100,
                             .region = 1,
                             .month = 1,
                             .product_id = 0,
                             .buyer_name = "Yaroslav",
                             .return_reason = "Да чет не зашло ваще"};
  events[1].payload = &event_payload_1;

  for (const Event& event : events) {
    if (event.type == EventType::EV_SALE) {
      SaleInfo event_info = *static_cast<SaleInfo*>(event.payload);
      data[event_info.region][event_info.month][event_info.product_id]++;
      std::cout << event_info.buyer_name << " Только что отдал нам свои "
                << event_info.price << " рублей! \n";
    } else if (event.type == EventType::EV_RETURN) {
      ReturnInfo event_info = *static_cast<ReturnInfo*>(event.payload);
      data[event_info.region][event_info.month][event_info.product_id]--;
      std::cout << event_info.buyer_name << " Только что вернул свои "
                << event_info.price << " рублей(( это все потому что "
                << event_info.return_reason << '\n';
    }
  }

  for (int r = 0; r < REGIONS; ++r) {
    for (int m = 0; m < MONTHS; ++m) {
      delete[] data[r][m];
    }
    delete[] data[r];
  }
  delete[] data;

  return 0;
}