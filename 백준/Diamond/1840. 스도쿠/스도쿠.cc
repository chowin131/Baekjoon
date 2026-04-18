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

    bool search(node* head) {
        if (head->right == head) return true;
        node* ptr = nullptr;
        int low = INF;
        for (node* it = head->right; it != head; it = it->right) {
            if (it->size < low) {
                if (it->size == 0) return false;
                low = it->size;
                ptr = it;
            }
        }
        cover(ptr);
        for (node* it = ptr->down; it != ptr; it = it->down) {
            for (node* jt = it->right; jt != it; jt = jt->right) {
                cover(jt->column);
            }
            if (search(head)) return true;
            for (node* jt = it->left; jt != it; jt = jt->left) {
                uncover(jt->column);
            }
        }
        uncover(ptr);
        return false;
    }

    bool has_solution(const vector<vector<int>>& matrix) {
        if (matrix.empty()) return false;
        int n = matrix[0].size();
        vector<node> column(n);
        node head;
        head.right = &column[0];
        head.left = &column[n - 1];
        for (int i = 0; i < n; i++) {
            column[i].size = 0;
            column[i].up = &column[i];
            column[i].down = &column[i];
            column[i].left = (i == 0) ? &head : &column[i - 1];
            column[i].right = (i == n - 1) ? &head : &column[i + 1];
        }
        vector<node*> nodes;
        for (int i = 0; i < matrix.size(); i++) {
            node* last = nullptr;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j]) {
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
                    } else {
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
        }
        bool res = search(&head);
        for (node* ptr : nodes) delete ptr;
        return res;
    }
}

struct Step { int r, c, v; };
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    while (true) {
        vector<Step> steps(81);
        bool eof = false;
        for (int i = 0; i < 81; i++) {
            if (!(cin >> steps[i].r >> steps[i].c >> steps[i].v)) {
                eof = true;
                break;
            }
            steps[i].r--;
            steps[i].c--;
        }
        if (eof) break;

        int left = 1, right = 81;
        int ans = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int board[9][9] = {0};
            bool valid = true;
            int row_mask[9] = {0}, col_mask[9] = {0}, box_mask[9] = {0};

            for (int i = 0; i < mid; i++) {
                int r = steps[i].r, c = steps[i].c, v = steps[i].v;
                int b = (r / 3) * 3 + (c / 3);
                
                if (board[r][c] != 0) {
                    valid = false;
                    break;
                }
                if ((row_mask[r] & (1 << v)) || (col_mask[c] & (1 << v)) || (box_mask[b] & (1 << v))) {
                    valid = false;
                    break;
                }
                board[r][c] = v;
                row_mask[r] |= (1 << v);
                col_mask[c] |= (1 << v);
                box_mask[b] |= (1 << v);
            }

            bool possible = false;
            if (valid) {
                vector<vector<int>> mat;
                mat.reserve(729);
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        if (board[i][j]) {
                            int k = board[i][j] - 1;
                            vector<int> row(324, 0);
                            row[i * 9 + j] = 1;
                            row[81 + i * 9 + k] = 1;
                            row[81 * 2 + j * 9 + k] = 1;
                            row[81 * 3 + (i / 3 * 3 + j / 3) * 9 + k] = 1;
                            mat.push_back(row);
                        } else {
                            for (int k = 0; k < 9; k++) {
                                vector<int> row(324, 0);
                                row[i * 9 + j] = 1;
                                row[81 + i * 9 + k] = 1;
                                row[81 * 2 + j * 9 + k] = 1;
                                row[81 * 3 + (i / 3 * 3 + j / 3) * 9 + k] = 1;
                                mat.push_back(row);
                            }
                        }
                    }
                }
                possible = dlx::has_solution(mat);
            }

            if (possible) {
                left = mid + 1;
            } else {
                ans = mid;
                right = mid - 1;
            }
        }
        cout << ans << '\n';
    }
}