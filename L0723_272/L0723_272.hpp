#ifndef L0723_272_HPP
#define L0723_272_HPP

#include "../L0517_194/L0517_194.hpp"
#include "../L0705_244/L0705_244.hpp"


// Выполняет топологическую сортировку ориентированного графа.
// Бросает std::invalid_argument для неориентированного графа
// и std::runtime_error при обнаружении цикла.
std::vector<int> topological_sort(const graph &g);
extern std::vector<bool> discovered;     // Для отслеживания посещенных вершин
extern std::vector<int> entry_time;      // Время входа в вершину
extern std::vector<int> exit_time;       // Время выхода из вершины

#endif
