// Hierholzer's algo for Eular circuit(i.e., visiting each edge exactly once and end at source vertex) code for bidirectional graph
// gset is adjacency list representation of the graph
// for unidirectional graph, use a vector instead of set and each time only erase the forward edge with pop_back

multiset<int> gset[100007];
vector<int> circuit;

void eularcircuit(int src)
{
    stack<int> curr_path;

    circuit.clear();
    if(gset[src].empty())return;
    curr_path.push(src);
    int curr_v = src;

    while (!curr_path.empty())
    {
        if (!gset[curr_v].empty())
        {
            curr_path.push(curr_v);
            auto it=gset[curr_v].begin();
            int next_v = *it;
            gset[curr_v].erase(next_v);
            gset[next_v].erase(curr_v);
            curr_v = next_v;
        }

        else
        {
            circuit.push_back(curr_v);
            curr_v = curr_path.top();
            curr_path.pop();
        }
    }

    reverse(circuit.begin(),circuit.end());
}
