#pragma once
#include <iostream>
#include <vector>

template <typename T, int Cap>
class Registry {
private:
    std::vector<T> items;

public:
    void add(const T& item) {
        if (items.size() >= Cap) {
            items.erase(items.begin());
        }
        items.push_back(item);
    }

    size_t size() const { return items.size(); }

    const T& operator[](size_t index) const { return items[index]; }

    friend std::ostream& operator<<(std::ostream& os, const Registry& reg) {
        for (const auto& item : reg.items) {
            os << item << "\n";
        }
        return os;
    }
};