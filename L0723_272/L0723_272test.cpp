// L0723_272
// Тесты для листинга 7.23
// Гаврилюк Екатерина, МЕН-243201 (ПМ-201)
#include "L0723_272.hpp"
#include "../L0517_194/L0517_194.hpp"
#include "../L0705_244/L0705_244.hpp"


#include <cassert>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
std::vector<int> topological_sort(const graph &g);
void add_edges(graph &g, const std::vector<std::pair<int, int>> &edges) {
    for (const auto &edge : edges) {
        insert_edge(&g, edge.first, edge.second, 1, true); // добавляем ориентированное ребро с весом 1
    }
}

bool precedes(const std::vector<int> &order, int u, int v) {
    std::unordered_map<int, std::size_t> pos;
    for (std::size_t i = 0; i < order.size(); ++i) {
        pos[order[i]] = i; // сохраняем позицию каждой вершины в порядке
    }
    return pos[u] < pos[v]; // проверяем, что u идет раньше v
}

void test_simple_dag() {
    graph g{};
    initialize_graph(&g, true);
    g.nvertices = 6;
    add_edges(g, {{1, 2}, {1, 3}, {3, 4}, {2, 4}, {4, 5}, {5, 6}}); // простой связный DAG

    auto order = topological_sort(g);
    assert(order.size() == 6);
    assert(precedes(order, 1, 2));
    assert(precedes(order, 1, 3));
    assert(precedes(order, 2, 4));
    assert(precedes(order, 3, 4));
    assert(precedes(order, 4, 5));
    assert(precedes(order, 5, 6));
}

void test_disconnected_dag() {
    graph g{};
    initialize_graph(&g, true);
    g.nvertices = 4;
    add_edges(g, {{1, 2}}); // несвязный DAG: компонент {3}, {4}

    auto order = topological_sort(g);
    assert(order.size() == 4);
    assert(precedes(order, 1, 2));
}

void test_cycle_detection() {
    graph g{};
    initialize_graph(&g, true);
    g.nvertices = 3;
    add_edges(g, {{1, 2}, {2, 3}, {3, 1}}); // цикл из трех вершин

    bool raised = false; // флаг срабатывания исключения
    try {
        (void)topological_sort(g);
    } catch (const std::runtime_error &) {
        raised = true;
    }
    assert(raised);
}

} 

int main() {
    test_simple_dag();
    test_disconnected_dag();
    test_cycle_detection();
    std::cout << "All tests passed" << std::endl;
    return 0;
}
