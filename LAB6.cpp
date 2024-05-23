#include <iostream>
#include <random>
#include <chrono>
#ifndef RND_MIN
#define RND_MIN -10
#endif
#ifndef RND_MAX
#define RND_MAX 25
#endif
#include <vector>
#include <algorithm>
const double EPSILON = 1e-3; // Погрешность
std::default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
template<typename T, typename B>
class MyClass {
public:
    T key;
    B data;
    // Конструктор класса
     MyClass(){
      double random;
        std::uniform_real_distribution<double> dist_key(RND_MIN, RND_MAX);
           random = dist_key(generator);
           key =  static_cast<T>(random);
        std::uniform_real_distribution<double> dist_data(RND_MIN, RND_MAX);
        random = dist_data(generator);
         data =  static_cast<B>(random);
	}
    bool operator>(const MyClass& other) const {
        return key > other.key;
    }
    bool operator<(const MyClass& other) const {
        return key < other.key;
    }
   //bool operator==(const MyClass& other) const {
   // return (key == other.key) && (data == other.data);
    //}
MyClass operator/(double divisor) const {
    MyClass result;
    result.key = key / divisor;
    result.data = data /divisor;
    return result;
}
MyClass operator/=(double divisor) {
    key /= divisor;
    //data /= divisor;
    return *this;
}
bool operator==(const MyClass& other) const {
    return fabs(key - other.key) < EPSILON && data == other.data;
}
     friend std::ostream& operator<<(std::ostream& os, const MyClass<T, B>& obj) {
        os << obj.key << " " << obj.data;
        return os;
    }
  MyClass(const T& k, const B& d) : key(k), data(d) {}
};

int main() {  MyClass<double, int> search_key; 
    double large; double key;
    int data;
   double average;
    double sum;
     int N = 5; // Размер вектора
    int choice; // Переменная для выбора из меню
    double min_val;
    std::vector<MyClass<double, int>> v1(N);
     double max1;
     double max2;
     int max1_index;
     int max2_index;
     auto remove_two_largest = [&](const MyClass<double, int>& obj) {
                   return obj == v1[max1_index] || obj == v1[max2_index];
                };
    auto iter= std::find(v1.begin(), v1.end(), search_key);
    while (true) {
        std::cout << "\nМеню:" << std::endl;
        std::cout << "1. Просмотреть вектор" << std::endl;
        std::cout << "2. Заменить значения" << std::endl;
        std::cout << "3. Удалить 2 самых больших значения" << std::endl;
        std::cout << "4. Выйти" << std::endl;
        std::cout << "5. Отсортировать" << std::endl;
        std::cout << "6. Найден ли элемент?" << std::endl;
        std::cout << "7. Разделить элемент" << std::endl;
        std::cout << "Выберите вариант: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                for(const MyClass<double, int>& obj : v1) {
                    std::cout << obj << "\t"; 
                }
                break;
            case 2:
                sum = 0;
                for(const MyClass<double, int>& obj : v1) {
                    sum += obj.key; 
                }
                 average = sum / N;
                std::cout << "\nСреднее значение: " << average << "\n";
                 min_val = v1[0].key;
                for (int i = 1; i < N; ++i) {
                    if (v1[i].key < min_val) {
                        min_val = v1[i].key;
                    }
                }
                for (int i = 0; i < N; ++i) {
                    if (v1[i].key > average) {
                        v1[i].key = min_val;
                    }
                }
                for(const MyClass<double, int>& obj : v1) {
                    std::cout << obj << "\t";
                }
                break;
            case 3:
                 max1 = -std::numeric_limits<double>::infinity();
                 max2 = -std::numeric_limits<double>::infinity();
                 max1_index = 0;
                 max2_index = 0;

                for (int i = 1; i < N; ++i) {
                    if (v1[i].key >= max1) {
                        max2 = max1;
                        max2_index = max1_index;
                        max1 = v1[i].key;
                        max1_index = i;
                    } else if (v1[i].key > max2 && v1[i].key != max1) {
                        max2 = v1[i].key;
                        max2_index = i;
                    }
                }
                std::cout << "\nСамые большие значения: " << v1[max1_index] << " " << v1[max2_index] << "\n";
              //  auto remove_two_largest = [&](const MyClass<double, int>& obj) {
               //     return obj == v1[max1_index] || obj == v1[max2_index];
               // };
                v1.erase(std::remove_if(v1.begin(), v1.end(), remove_two_largest), v1.end());
                std::cout << "после удаления " <<"\n";
                for(const MyClass<double, int>& obj : v1) {
                    std::cout << obj << "\t";
                }
                break;
            case 4:
                return 0; // Выход из программы
          
           case 5:
    
                  std::sort(v1.begin(), v1.end(), [](const MyClass<double, int>& a, const MyClass<double, int>& b) {
     return a < b;
    });
                // Вывод отсортированного вектора
                for (const auto& obj : v1) {
                    std::cout << obj << "\t";
                }break;
                case 6:
                std::cout << "(double): ";
                std::cin >> key;
                std::cout << " (int): ";
                std::cin >> data;search_key.key = key;
    search_key.data = data;
           std::cout << "Значение search_key: " << search_key << std::endl;
                iter= std::find(v1.begin(), v1.end(), search_key);
                if ( iter!= v1.end()) {
                    std::cout << "Элемент найден: " << *iter << std::endl;
                } else {
                    std::cout << "Элемент не найден." << std::endl;
                }break;
                case 7:
                large = v1[0].key;

	for (int i = 1; i < N; ++i) {
 	   if (v1[i].key > large) {
  	      large = v1[i].key;
    
  	  }
	}
         std::cout << "Наибольшее значение: " << large << std::endl;
             std::for_each(v1.begin(), v1.end(), [large](MyClass<double, int>& obj) { obj/= large; });
                break;
             default:
                std::cout << "Неверный выбор" << std::endl;
                return 0; // Добавлено
        }
    }

    return 0;
}
