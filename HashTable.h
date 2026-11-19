#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../P1/PRA_2627_P1-/ListLinked.h"  // ¡ADAPTA A TU RUTA!

template <typename V>
class HashTable: public Dict<V> {

    private:
        // ...
		int n;
		int max;
		ListLinked<TableEntry<V>>* table;
		int h(std::string key){
            int sum = 0;
            for (size_t i = 0; i < key.length(); i++) {
                sum += int(key.at(i));
            }
            return sum % max;
        }

    public:
        // ...
		HashTable(int size){
			n=0;
			max= size;
			table= new ListLinked<TableEntry<V>>[size];
		}
		~HashTable(){
			delete[] table;
		}
		int capacity(){
			return max;
		}
		V operator[](std::string key){
			return this->search(key);
		}
		friend std::ostream operator<<(std::ostream &out, const HashTable<V> &th){
			out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
			out << "==============\n\n";
			for (int i = 0; i < th.max; i++) {
				out << "== Cubeta " << i << " ==\n\n";
				out << th.table[i] << "\n\n";
			}
			out << "==============\n";
			return out;
		}
};

#endif
