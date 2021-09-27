/**
 * Author: Benjamin Qi
 * Description: example of function object (functor); keeps default behavior
 * cmp(a, a) should always return FALSE(!)
 * Source: StackOverflow
 * Usage: set<int,cmp> s; map<int,int,cmp> m;
 */

struct cmp{bool operator()(int l,int r)const{return l<r;}};
