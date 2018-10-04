#ifndef NODE_H
#define NODE_H

template <typename G>
struct Node {

  typedef typename G::N N;
  typedef typename G::E E;
  typedef typename G::edge edge;
  typedef typename G::EdgeSeq EdgeSeq;

  EdgeSeq edges;

  N data;
  double x;
  double y;

  Node(N value):data(value){}
};

#endif
