#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>
#include <string>

namespace ft{

	template <class T1, class T2>
	class pair {

			public :


				typedef T1 first_type;
				typedef T2 second_type;

				first_type first;
				second_type second;

				pair(void){};
				pair(const first_type &a, const second_type &b){
					this->first = a;
					this->second = b;
				}
				
				template <class U, class V>
				pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {
					//*this = pr;
				}
				
				pair& operator=(pair const& p) {
					this->first = p.first;
					this->second = p.second;
					return *this;
				}

			private:


};

	template <class T1, class T2>
 	 pair<T1,T2> make_pair (T1 x, T2 y){
			return pair<T1,T2>(x, y);
	 }

	template <class T1, class T2>
 	 bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

template <class T1, class T2>
  	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs==rhs); }

template <class T1, class T2>
  	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

template <class T1, class T2>
  	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs<lhs); }

template <class T1, class T2>
  	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs<lhs; }

template <class T1, class T2>
  	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs<rhs); }
};
#endif 
