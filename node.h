#ifndef NODE_H
#define NODE_H

template <typename G>
class Node {
  public:
    typedef typename G::N N;
    typedef typename G::E E;
    typedef typename G::edge edge;
    typedef typename G::EdgeSeq EdgeSeq;

    EdgeSeq edges;

    Node(N value):data(value){}
  
    Node(N name, double x, double y){
        data = name;
        this -> x = x;
        this -> y = y;
    }

    N getData(){
      return data;
    }
  
    double getX(){
        return x;
    }

    double getY(){
        return y;
    }

  private:
    N data;
    double x;
    double y;

};

#endif
