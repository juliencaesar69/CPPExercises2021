#include "disjoint_set.h"

#define ROOT -1 // объявили макрос (считайте константу) равный минус единице - чтобы не было "волшебной переменной", а была именованная константа "корень дерева"


DisjointSet::DisjointSet(int size) {
    parents = std::vector<int>(size);
    ranks = std::vector<int>(size);
    sizes = std::vector<int>(size);
    // TODO - заполните вектора так чтобы на этапе конструирования эта система непересекающихся множеств состояла из:
    // size элементов, каждый из которых состоит в своем множестве (а значит ссылка на родителя у него - на корень, т.е. на ROOT, а какой тогда ранк и размер у множества каждого элемента?)
    // TODO заполнить parents
    // TODO заполнить ranks
    // TODO заполнить sizes
    for (int i = 0; i < size; i++) {
        parents[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        ranks[i] = 0;
    }
    for (int i = 0; i<size; i++) {
        sizes[i] = 1;
    }
}

int	DisjointSet::get_set(int element)
{
    // TODO по номеру элемента нужно переходя по ссылкам на родителя дойти до самого верхнего элемента,
    // номер этого корневого элемента - номер множества на данный момент (кто вверху тот и главный, множество названо в его честь)
    int first_of_their_kind = 0;
    int i = element;
    if (parents[i] != i && parents[i]!= -1) {
        parents[i] = get_set(parents[element]);
    }else {
        first_of_their_kind = i;
    }
    return first_of_their_kind;
}

int DisjointSet::count_differents() const
{
    // TODO посчитать сколько разных множеств (подсказка: в каждом множестве ровно один корень, а корень - это тот у кого родитель = ROOT)
    int count = 0;
    for (size_t i = 0; i < this->parents.size(); i++) {
        if (parents[i]==-1) count++;
    }
    return count;
}

int DisjointSet::get_set_size(int element)
{
    int c = 0;
    int root = get_set(element);
    for (int i = 0; i < this->parents.size(); i++) {
        if (get_set(i)==root) c++;
    }
    // TODO сообщить сколько элементов в множестве, которому принадлежит данный элемент (да, это очень просто)
    return c;
}

int	DisjointSet::union_sets(int element0, int element1)
{
    // TODO узнать корневые элементы этих двух элементов и посмотрев на них - решить,
    // кого из них подвесить к другому (тем самым объединить два множества)
    // при этом стоит подвешивать менее высокое дерево к более высокому (т.е. учитывая ранк),
    // а так же важно не забыть после переподвешивания у корневого элемента обновить ранк и размер множества
    element0 = get_set(element0);
    element1 = get_set(element1);
    int set_position = 0;
    if (element1 == element0) {
        return element0;
    }
    if (ranks[element0]==ranks[element1]) {
        parents[element0] = element1;
        set_position = element1;
    }
    if (ranks[element0]<ranks[element1]) {
        ranks[element0]++;
    }else{
        parents[element1] = element0;
        set_position = element0;
    }

    return set_position; // вернуть номер объединенного множества
}
