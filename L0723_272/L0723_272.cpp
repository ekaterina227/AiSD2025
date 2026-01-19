//L0723_272
//Топологическая сортировка
//Гаврилюк Екатерина, МЕН-243201 (ПМ-201) 11.11.2025
#include "L0723_272.hpp"

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <vector>

#include "../L0705_244/L0705_244.hpp"
#include "../L0517_194/L0517_194.hpp"


std::vector<int> topological_sort(const graph &g) {
    if (!g.directed) {
        throw std::invalid_argument("Topological sort requires a directed graph");
    }

    initialize_search(const_cast<graph *>(&g));
    for (int i = 1; i <= g.nvertices; ++i) {
        if (!discovered[i]) {
            dfs(const_cast<graph *>(&g), i);
        }
    }

    // Проверяем наличие обратных ребер постфактум через интервалы времени входа/выхода
    bool found_cycle = false;
    for (int u = 1; u <= g.nvertices && !found_cycle; ++u) {
        for (edgenode *p = g.edges[u]; p != nullptr; p = p->next) {
            int v = p->y;
            // back-edge: v предок u в дереве DFS
            if (entry_time[v] < entry_time[u] && exit_time[u] < exit_time[v]) {
                found_cycle = true;
                break;
            }
        }
    }

    if (found_cycle) {
        throw std::runtime_error("Directed cycle detected; graph is not a DAG");
    }

    // Топологический порядок: убывание времени выхода
    std::vector<int> order(g.nvertices);
    std::iota(order.begin(), order.end(), 1);
    std::sort(order.begin(), order.end(), [](int a, int b) {
        return exit_time[a] > exit_time[b];
    });
    return order;
}
