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
		HashTable(int size): n(0),max(size), table(new ListLinked<TableEntry<V>>[size]){}
		
		~HashTable(){
			delete[] table;
		}
		int capacity(){
			return max;
		}
		V operator[](std::string key){
			return this->search(key);
		}
		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
			out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
			out << "==============\n\n";
			for (int i = 0; i < th.max; i++) {
				out << "== Cubeta " << i << " ==\n\n";
				out << th.table[i]<<std::endl;
			}
			out << "==============\n";
			return out;
		}
		void insert(std::string key, V value) override {
		    int pos = h(key);
		    TableEntry<V> entry(key, value);
		    if (table[pos].search(entry) != -1) {
		        throw std::runtime_error("Key '" + key + "' already exists!");
		    }
		    table[pos].prepend(entry); // O append(entry)
		    n++;
		}
	
		V search(std::string key) override {
		    int pos = h(key);
		    TableEntry<V> entry(key);
		    int idx = table[pos].search(entry);
		    if (idx == -1) {
		        throw std::runtime_error("Key '" + key + "' not found!");
		    }
		    return table[pos].get(idx).value;
		}
	
		V remove(std::string key) override {
			int pos = h(key);
			TableEntry<V> entry(key);
			int idx = table[pos].search(entry);
			if (idx == -1) {
			    throw std::runtime_error("Key '" + key + "' not found!");
			}
			V val = table[pos].remove(idx).value;
			n--;
			return val;
		}
	
		int entries() override {
			return n;
		}
};

#endif
