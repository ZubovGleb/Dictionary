#include "DictionaryList.h"

int main()
{
    DictionaryList list1;
    std::cout << "list1: ";
    std::cout << list1 << std::endl;
    std::cout << "Is list1 empty?\n";
    list1.isEmpty() ? std::cout << "Yes\n\n" : std::cout << "No\n\n";
    list1.insert(7);
    list1.insert(19);
    list1.insert(19);
    list1.insert(32);
    std::cout << "list1: ";
    std::cout << list1 << std::endl;

    std::cout << "7 in list1: ";
    list1.searchItem(7) ? std::cout << "Yes\n" : std::cout << "No\n";
    std::cout << "9 in list1: ";
    list1.searchItem(9) ? std::cout << "Yes\n" : std::cout << "No\n";
    std::cout << '\n';

    list1.deleteItem(7);
    list1.deleteItem(19);
    std::cout << "Removing 7 and 19 from list1" << std::endl;
    std::cout << "list1: ";
    std::cout << list1 << "\n\n";

    DictionaryList list2;
    list2.insert(8);
    list2.insert(2);
    list2.insert(1);

    std::cout << "list2: ";
    std::cout << list2 << std::endl;
    try {
        std::cout << "list1 merge with list2" << std::endl;
        list1.merge(&list2);
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "list1: ";
    std::cout << list1 << std::endl;

    std::cout << "list2: ";
    std::cout << list2 << "\n\n";

    std::cout << "Inserting 12 and 1 in list2" << std::endl;
    list2.insert(12);
    list2.insert(1);
    try {
        std::cout << "Removing list2 from list1" << std::endl;
        list1.remove(&list2);
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
    }
    std::cout << "list1: ";
    std::cout << list1 << std::endl;

    std::cout << "list2: ";
    std::cout << list2 << "\n\n";
    std::cout << "Inserting 12 in list1 and 32 in list2" << std::endl;
    list1.insert(12);
    list2.insert(32);

    std::cout << "list1: ";
    std::cout << list1 << std::endl;

    std::cout << "list2: ";
    std::cout << list2 << "\n\n";
    try {
        std::cout << "Recording the intersection of list1 and list2 in list3" << std::endl;
        DictionaryList* list3;
        list3 = getIntersection(&list1, &list2);
        std::cout << "list3: ";
        std::cout << *list3 << std::endl;
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 3;
    }

    return 0;
}