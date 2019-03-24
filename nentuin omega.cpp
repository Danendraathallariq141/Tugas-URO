#include <iostream>
#include <cmath>
//vx, vy, w, a, t
//rx,ry di waktu t

#define PI 3.14159265
const double dT= 1e-4;

struct Vector {
  double x;
  double y;
};

Vector add(Vector v1, Vector v2) {
  Vector v;
  v.x = v1.x + v2.x;
  v.y = v1.y + v2.y;
  
  return v;
}

Vector sub(Vector v1, Vector v2) {
  Vector v;
  v.x = v1.x - v2.x;
  v.y = v1.y - v2.y;
  
  return v;
}

Vector mul(Vector v, double k) {
  Vector w;
  w.x = v.x * k;
  w.y = v.y * k;
  
  return w;
}

// k dalam radian berlawanan arah jarum jam
Vector rot(Vector v, double k) {
  Vector w;
  w.x = std::cos(k)*v.x - std::sin(k)*v.y;
  w.y = std::sin(k)*v.x + std::cos(k)*v.y;
  
  return w;
}

// melakukan simulasi
Vector calc(Vector v, double w, double aM, double t) {
  Vector r;
  r.x = 0;
  r.y = 0;
  Vector a;
  a.x = aM;
  a.y = 0;
	for (double t1 = 0; t1 < t; t1 += dT) {
    r = add(r, mul(v, dT));
    v = add(v, mul(a,dT));
    a = rot(a, w*dT);
  }
  return r;
}


Vector calc1(Vector r, double t) {
  double w = 0.1;
  double aM = 0.1;
  double incr;
  bool tuned;
  Vector v0;
  v0.x=0;
  v0.y=0;
  Vector posisi=calc(v0,w,aM,t) ; 
	while (posisi.x!=r.x&&posisi.y!=r.y){
      Vector posisi = calc(v0,w,(aM+incr),t);
      if(posisi.x<=r.x){
        aM+=0.01;
      }
      else if(posisi.x>=r.x) {
        aM-=0.01;
    	}
      else if(posisi.y<=r.y){
          w+=0.01;
        }
      else{
          w-=0.01;
        }
      
    }
  
  Vector hasil;
  hasil.x=w;
  hasil.y=aM;
  return hasil;


}

int main() {
  Vector r;
  double  t;
  std::cin >> r.x >> r.y >> t;
  Vector hasil = calc1(r,t);
  std::cout << hasil.x << ' ' << hasil.y << std::endl;
}
