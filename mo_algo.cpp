
const int BLOCK_SIZE = 750;
struct Query {
    int l, r, idx;

    bool operator<(Query other) const {
        if (l / BLOCK_SIZE != other.l / BLOCK_SIZE) 
            return make_pair(l, r) < make_pair(other.l, other.r);
        return (l / BLOCK_SIZE & 1) ? (r < other.r) : (r > other.r);
    }
};

vector<Query> queries;
vector<int> mo_algorithm() {
    vector<int> answers(queries.size()+1);
    sort(all(queries));

    // TODO: initialize data structure
    int res = 0, cur_l = 1, cur_r = 0;

    auto addL = [&] (int x) {
    };

    auto removeL = [&] (int x) {
    };

    auto addR = [&] (int x) {
    };

    auto removeR = [&] (int x) {
    };

    auto get_answer = [&] () {
    };

    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (Query &q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            addL(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            addR(cur_r);
        }
        while (cur_l < q.l) {
            removeL(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            removeR(cur_r);
            cur_r--;
        }
        
        answers[q.idx] = get_answer();
    }

    return answers;
}