#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>

#define TIME 100
#define N 5000

using namespace std;


random_device seed_gen;
mt19937 engine(seed_gen());
static const double pi = 3.1415926535893;


class Needle {
private:
  double l;             //length
  double o;             //center coordinates
  double theta;         //angle
  double dist;          //distance between needle and line
  double dist_needle;   //distance between center and end of needle

public:
  Needle(int l){
    this->l = (double)l;
    o = 0;
    theta = 0.0;
    dist = 0.0;
    dist_needle = 0.0;
  }

  bool drop_needle(double d){
    uniform_real_distribution<> range_o(0, d / 2.0);
    uniform_real_distribution<> range_t(0, pi / 2.0);

    o = range_o(engine);
    theta = range_t(engine);

    dist_needle = (l / 2.0) * sin(theta);

    if(o <= dist_needle){
      return true;
    }else{
      return false;
    }
  }
};



int main(){
  double prob, d, my_pi = 0.0, avg = 0.0;
  double  near = 0.0, diff = 1.0;
  int l = 3, count;
  bool jdge;
  
  Needle obj(l);
  d = 2 * l;

  for(int j = 0; j < TIME; j++){
    count = 0;
    
    for(int i = 0; i < N; i++){
      jdge = obj.drop_needle(d);
      if(jdge == true){
	count++;
      }
    }

    prob = (double)count / (double)N;
    my_pi = 1.0 / prob;

    cout << "[" << j + 1 << "]: "
	 << fixed << setprecision(13) << my_pi << endl;

    if(diff > abs(my_pi - pi)){
      near = my_pi;
      diff = abs(my_pi - pi);
    }
    avg += my_pi;
  }

  cout << endl << "Average: " << avg / TIME << endl;
  cout << "optimul solution: " << near << endl;
  
  return 0;
}
