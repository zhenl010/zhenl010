// saw this online but i think this is WRONG!
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
const static double INFINITY = numeric_limits<double>::infinity();
struct Position
{
  int m, n;
  Position (int m_ = -1,  int n_ = -1) :  m (m_), n(n_) {}
  Position left() const {return Position( m , n - 1);}
  Position right() const {return Position (m ,n + 1);}
  Position above() const {return Position (m - 1, n );}
  Position below() const {return Position (m + 1, n );}

};

class DamLakeSolver
{
  int m_row, m_col;
  int m_level;
  double m_inc_cost;
  double m_dec_cost;
  vector<int> m_matrix;
  vector<double> m_cost_matrix;
  vector<bool> m_done_matrix;
  vector<Position> m_traceback_matrix;
  inline int idx(Position pos) const{ return (pos.m) * (m_col)  + (pos.n) ;}
  void relax(Position pos0, Position pos1);
  void dijkstra(Position lake_pos) ;
  Position extractMin() const;
  void printPath(Position lake_pos) const;
public:
  inline void setIncrementalCost(double cost) {m_inc_cost = cost;}
  inline void setDecrementalCost(double cost) {m_dec_cost = cost;}
  double solve(Position lake_pos, Position dam_pos);

  DamLakeSolver(int * matrix, int row, int col)
    :m_row(row), m_col(col), m_level(0), m_matrix(matrix, matrix + col * row), m_inc_cost(1.), m_dec_cost(1.)
  {

  }

};
void DamLakeSolver::printPath(Position lake_pos) const
{
  Position cur_pos = lake_pos;
  cout<<"Position: "<<cur_pos.m + 1 <<" "<<cur_pos.n + 1;
  Position pre_pos = cur_pos;
  cur_pos = m_traceback_matrix[idx(cur_pos)];

  while (cur_pos.m != -1)
  {
    double cost = m_cost_matrix[idx(pre_pos)] - m_cost_matrix[idx(cur_pos)];
    cout<<" Cost: "<<cost<<endl<<"Position: "<<cur_pos.m + 1 <<" "<<cur_pos.n + 1;
    pre_pos = cur_pos;
    cur_pos = m_traceback_matrix[idx(cur_pos)];
  }
  cout<<endl;
}
double DamLakeSolver::solve(Position lake_pos, Position dam_pos)
{
  //programmers count index from 0!
  lake_pos.m --;
  lake_pos.n --;
  dam_pos.m --;
  dam_pos.n --;

  m_cost_matrix.assign(m_row * m_col , INFINITY);
  m_traceback_matrix.assign(m_col * m_row, Position());

  for (m_level = m_matrix[idx(dam_pos)]; m_level <= m_matrix[idx(lake_pos)]; ++ m_level)
  {
    dijkstra(dam_pos);
  }
  printPath(lake_pos);
  return m_cost_matrix[idx(lake_pos)];

}
Position DamLakeSolver::extractMin() const
{
  Position min_pos(0, 0);
  double min_cost = INFINITY;
  for (int i = 0; i < m_row ; ++i)
    for (int j = 0; j < m_col; ++j)
    {
      Position cur_pos(i, j);
      if (m_done_matrix[idx(cur_pos)])
        continue;
      if (min_cost > m_cost_matrix[idx(cur_pos)])
      {
        min_cost = m_cost_matrix[idx(cur_pos)];
        min_pos = cur_pos;
      }
    }
    return min_pos;
}
void DamLakeSolver::dijkstra(Position dam_pos)
{
  m_cost_matrix[idx(dam_pos)] = 0;

  m_done_matrix.assign(m_row * m_col, false);
  m_done_matrix[idx(dam_pos)] = true;
  Position cur_pos = dam_pos;
  for (int i = 0; i < m_col * m_row; ++i)
  {
    if (cur_pos.n > 0){ relax(cur_pos, cur_pos.left());}
    if (cur_pos.n < m_col - 1) {relax(cur_pos, cur_pos.right());}
    if (cur_pos.m > 0) {relax(cur_pos, cur_pos.above());}
    if (cur_pos.m < m_row - 1) {relax(cur_pos, cur_pos.below());}
    cur_pos = extractMin();

    m_done_matrix[idx(cur_pos)] = true;

  }

}
void DamLakeSolver::relax(Position pos0, Position pos1)
{
  int path_cost = m_cost_matrix[idx(pos0)];
  double &cur_cost = m_cost_matrix[idx(pos1)];
  double new_cost  = 0;
  if (m_matrix[idx(pos1)] < m_level)
    new_cost = path_cost + m_inc_cost * (m_level - m_matrix[idx(pos1)]);
  else
    new_cost = path_cost + m_dec_cost * (m_matrix[idx(pos1)] - m_level);
  if (new_cost < cur_cost)
  {
    cur_cost = new_cost;
    m_traceback_matrix[idx(pos1)] = pos0;
  }
}

int main()
{
  int matrix[] = {2, 7, 3, 1, 0,
    2, 1, 1, 7, 1,
    7, 7, 7, 2, 1};
  DamLakeSolver dls(matrix, 3, 5);
  dls.setIncrementalCost(1); // the cost of decreasing 1 unit of elevation of the hill.
  dls.setDecrementalCost(1); // the cost of increasing 1 unit of elevation of the hill.
  cout<<dls.solve(Position(1,1), Position (3,4))<<endl;// lake --> dam
  //if you change the cost ratio, the answer changes.
  dls.setIncrementalCost(100);
  dls.setDecrementalCost(1);
  cout<<dls.solve(Position(1,1), Position (3,4))<<endl;

  return 0;
}