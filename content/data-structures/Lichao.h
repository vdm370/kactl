/**
 * Author: shadowatyy
 * Source: library-checker
 * Description: LiChao tree for dynamic convex hull trick.
 * can query at any point and insert lines/segments on ranges. 
 * Time: O(n \log n)
 * Status: stress-tested
 */
template <typename T>
struct LichaoTree {
  const T INF = std::numeric_limits<T>::max();
  struct line {
    T a, b;
    line(T a, T b) : a(a), b(b) {}
    T operator()(T x) const { return a * x + b; }
  };
  int n;
  std::vector<line> fs;
  std::vector<T> xs;

  int index(T x) const { return lower_bound(xs.begin(), xs.end(), x) - xs.begin(); }

  void update(T a, T b, int l, int r) {
    line g(a, b);
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if(l & 1) descend(g, l++);
      if(r & 1) descend(g, --r);
    }
  }

  void descend(line g, int i) {
    int l = i, r = i + 1;
    while(l < n) l <<= 1, r <<= 1;
    while(l < r) {
      int c = (l + r) >> 1;
      T xl = xs[l - n], xr = xs[r - 1 - n], xc = xs[c - n];
      line &f = fs[i];
      if(f(xl) <= g(xl) && f(xr) <= g(xr)) return;
      if(f(xl) >= g(xl) && f(xr) >= g(xr)) {
        f = g;
        return;
      }
      if(f(xc) > g(xc)) swap(f, g);
      if(f(xl) > g(xl))
        i = i << 1 | 0, r = c;
      else
        i = i << 1 | 1, l = c;
    }
  }

   public:
  Tree(const std::vector<T> &xs_) : xs(xs_) {
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    n = xs.size();
    fs.assign(n << 1, line(T(0), INF));
  }

  // add f(x) = ax + b
  void add_line(T a, T b) { update(a, b, 0, n); }

  // add f(x) = ax + b (x in [xl, xr))
  void add_segment(T a, T b, T xl, T xr) {
    int l = index(xl), r = index(xr);
    update(a, b, l, r);
  }

  T get_min(T x) const {
    int i = index(x);
    T res = INF;
    for(i += n; i; i >>= 1) res = min(res, fs[i](x));
    return res;
  }
};
