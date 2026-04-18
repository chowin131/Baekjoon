#include <bits/stdc++.h>
using namespace std;
#define INF INT32_MAX
namespace dlx {
    struct node {
        int row;
        int size;
        node* column;
        node* up;
        node* down;
        node* left;
        node* right;
    };
    void cover(node* c) {
        c->right->left = c->left;
        c->left->right = c->right;
        for (node* it = c->down; it != c; it = it->down) {
            for (node* jt = it->right; jt != it; jt = jt->right) {
                jt->down->up = jt->up;
                jt->up->down = jt->down;
                jt->column->size--;
            }
        }
    }
    void uncover(node* c) {
        for (node* it = c->up; it != c; it = it->up) {
            for (node* jt = it->left; jt != it; jt = jt->left) {
                jt->down->up = jt;
                jt->up->down = jt;
                jt->column->size++;
            }
        }
        c->right->left = c;
        c->left->right = c;
    }
    bool search(node* head, vector<int>& ret) {
        if (head->right == head) return 1;
        node* ptr = nullptr;
        int low = INF;
        for (node* it = head->right; it != head; it = it->right) {
            if (it->size < low) {
                if (it->size == 0) return 0;
                low = it->size;
                ptr = it;
            }
        }
        cover(ptr);
        for (node* it = ptr->down; it != ptr; it = it->down) {
            ret.push_back(it->row);
            for (node* jt = it->right; jt != it; jt = jt->right) {
                cover(jt->column);
            }
            if (search(head, ret)) return 1;
            else {
                ret.pop_back();
                for (node* jt = it->left; jt != it; jt = jt->left) {
                    uncover(jt->column);
                }
            }
        }
        uncover(ptr);
        return 0;
    }
    vector<int> sol(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};
        int n = matrix[0].size();
        vector<node> column(n);
        node head;
        head.right = &column[0];
        head.left = &column[n - 1];
        for (int i = 0; i < n; i++) {
            column[i].size = 0;
            column[i].up = &column[i];
            column[i].down = &column[i];
            if (i == 0) column[i].left = &head;
            else column[i].left = &column[i - 1];
            if (i == n - 1) column[i].right = &head;
            else column[i].right = &column[i + 1];
        }
        vector<node*> nodes;
        for (int i = 0; i < matrix.size(); i++) {
            node* last = nullptr;
            for (int j = 0; j < n; j++) if (matrix[i][j]) {
                node* now = new node;
                now->row = i;
                now->column = &column[j];
                now->up = column[j].up;
                now->down = &column[j];
                if (last) {
                    now->left = last;
                    now->right = last->right;
                    last->right->left = now;
                    last->right = now;
                }
                else {
                    now->left = now;
                    now->right = now;
                }
                column[j].up->down = now;
                column[j].up = now;
                column[j].size++;
                last = now;
                nodes.push_back(now);
            }
        }
        vector<int> ret;
        search(&head, ret);
        for (node* ptr : nodes) delete ptr;
        return ret;
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    while (cin >> s && s != "end") {
        vector<vector<int>> mat;
        vector<tuple<int, int, int>> data;
        mat.reserve(729);
        data.reserve(729);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                auto make_row = [&](int k) {
                    vector<int> row(324, 0);
                    row[i * 9 + j] = 1;
                    row[81 + i * 9 + k] = 1;
                    row[81 * 2 + j * 9 + k] = 1;
                    row[81 * 3 + (i / 3 * 3 + j / 3) * 9 + k] = 1;
                    mat.push_back(row);
                    data.push_back({ i, j, k });
                };
                if (s[i * 9 + j] != '.') make_row(s[i * 9 + j] - '1');
                else for (int k = 0; k < 9; k++) make_row(k);
            }
        }
        for (auto i : dlx::sol(mat)) {
            auto [x, y, k] = data[i];
            s[x * 9 + y] = k + '1';
        }
        cout << s << '\n';
    }
}