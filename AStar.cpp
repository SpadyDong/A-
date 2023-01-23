// AStar.cpp : A*算法
//

#include <iostream>
#include <vector>

using namespace std;

class P
{
public:
    int x, y;
public:
    P()
    {
        x = 0;
        y = 0;
    }
    P(int x_in, int y_in)
    {
        x = x_in;
        y = y_in;
    }
    bool operator==(const P& t)
    {
        if (this->x == t.x && this->y == t.y)
        {
            return true;
        }
        return false;
    }

    bool operator!=(const P& t)
    {
        if (this->x == t.x && this->y == t.y)
        {
            return false;
        }
        return true;
    }
};

class AStar
{
private:
    float get_h(P p)
    {
        return abs(p.x - target.x) + abs(p.y - target.y);
    }
    vector<int> neighbor_x = { 0,0,-1,1,-1,1,-1,1 };
    vector<int> neighbor_y = { -1,1,0,0,-1,1,1,-1 };
public:
    P target;
    P start;
    std::vector<std::vector<float>> G;
    std::vector<std::vector<int>> map;
    std::vector<std::vector<P>> parent;

    void search()
    {
        std::vector<P> open_list, close_list;
        open_list.push_back(start);

        G.resize(map.size());
        parent.resize(map.size());
        for (int i = 0; i < map.size(); i++)
        {
            G[i].resize(map[0].size());
            parent[i].resize(map[0].size());
        }

        while (!open_list.empty())
        {
            // 查找最优点
            int best_point_index = 0;
            float best_cost = G[open_list[best_point_index].x][open_list[best_point_index].y] + get_h(open_list[best_point_index]);
            for (int i = 0; i < open_list.size(); i++)
            {
                if (best_cost > G[open_list[i].x][open_list[i].y] + get_h(open_list[i]))
                {
                    open_list[best_point_index] = open_list[i];
                    best_cost = G[open_list[i].x][open_list[i].y] + get_h(open_list[i]);
                }
            }
            // 找到目标点
            if (open_list[best_point_index] == target)
            {
                P t = target;
                while (t != start)
                {
                    cout << t.x << " " << t.y << endl;
                    t = parent[t.x][t.y];
                }
                return;
            }
            // 未找到目标点
            P best_point = open_list[best_point_index];
            open_list[best_point_index] = open_list[open_list.size()-1];
            open_list[open_list.size()-1] = best_point;
            open_list.pop_back();
            close_list.push_back(best_point);
            // 遍历bset_point的所有临近点
            for (int i = 0; i < neighbor_x.size(); i++)
            {
                if (best_point.x + neighbor_x[i] > map.size() - 1 || best_point.y + neighbor_y[i] > map[0].size() - 1 || best_point.x + neighbor_x[i] < 0 || best_point.y + neighbor_y[i] < 0)
                {
                    continue;
                }
                if (map[best_point.x + neighbor_x[i]][best_point.y + neighbor_y[i]] == 1)
                {
                    continue;
                }
                P temp(best_point.x + neighbor_x[i], best_point.y + neighbor_y[i]);
                bool m = false; 
                for (int j = 0; j < close_list.size(); j++)
                {
                    if (temp == close_list[j])
                    {
                        m = true;
                        break;
                    }
                }
                if (m)
                {
                    continue;
                }
                open_list.push_back(temp);
                G[best_point.x][best_point.y] = G[temp.x][temp.y] + 1;
                parent[temp.x][temp.y] = best_point;
            }
        }
        return;


    }

};

int main()
{
    AStar astar;
    std::vector<std::vector<int>> map = { {0,1,0,0} ,{0,1,0,0} ,{0,0,0,0} ,{0,0,0,0} };
    astar.map = map;
    P t(3, 3);
    astar.target = t;
    P s(0, 0);
    astar.start = s;
    astar.search();
}

