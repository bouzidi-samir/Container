#ifndef MAP_HPP
#define MAP_HPP

#include "iterator.hpp"
#include "binary_tree.hpp"
#include "pair.hpp"
#include "../Utils.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {

	public:
	
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef ft::pair<key_type, mapped_type>						value_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef size_t												size_type;
		typedef ptrdiff_t											difference_type;
		typedef typename ft::iterator<value_type>					iterator;
		typedef typename ft::const_iterator<value_type>				const_iterator;
		typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		class value_compare { 

				friend class map<key_type, mapped_type, key_compare, allocator_type>;

				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}

				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
						{
							return comp(x.first, y.first);
						}
		};


		binary_tree<value_type, key_compare>	tree;
		
	private:
		value_type								value;
		key_compare								comp;
		allocator_type							alloc;

	public:

		//Construit une map vide. 

		explicit map(key_compare const& comp = key_compare(), 
		allocator_type const& alloc = allocator_type())
		{
			this->comp = comp;
			this->alloc = alloc;
			this->tree.compare = comp;
			this->tree.allocator = alloc;
		}

		//Contruit un map avec une liste de pair cles : valeur

		template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr)
		{
			(void)enable;
			this->comp = comp;
			this->alloc = alloc;
			this->insert(first, last);
		}

		//Copy contructor.

		map(const map &ref)
		{
			this->alloc = ref.alloc;
			this->comp = ref.comp;
			this->insert(ref.begin(), ref.end());
		}
		
		key_compare key_comp() const
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return value_compare(key_compare());
		}


		~map(void) {}

		iterator begin(void)
		{
			return iterator(this->tree.getFirstNode(), this->tree.getLastNode());
		}

		const_iterator begin(void) const
		{
			return const_iterator(this->tree.getFirstNode(), this->tree.getLastNode());
		}

		iterator end(void)
		{
			return iterator(this->tree.null_leaf, this->tree.getLastNode());
		}

		const_iterator end(void) const
		{
			return const_iterator(this->tree.null_leaf, this->tree.getLastNode());
		}

					// reverse begin  &&  end

		reverse_iterator rend(void)
		{
			return reverse_iterator(this->begin());
		}

		const_reverse_iterator rend(void) const
		{
			return const_reverse_iterator(this->begin());
		}

		reverse_iterator rbegin(void)
		{
			return reverse_iterator(this->end());
		}

		const_reverse_iterator rbegin(void) const
		{
			return const_reverse_iterator(this->end());
		}

	    //   iterator find (const key_type& k)
		//   {

		//   }

		map& operator= (const map& x)
		{
			this->clear();
			this->insert(x.begin(), x.end());
			return *this;
		}

		mapped_type& operator[] (const key_type& k)
		{

			return (((this->insert(ft::make_pair(k,mapped_type()))).first))->second;
		}

		size_type size() const
		{
			return (this->tree.size(tree.Root));
		}

		size_type max_size() const
		{
			return (this->alloc.max_size() / 2);
		}

		pair<iterator,bool> insert (const value_type& val)
		{
			bool true_or_false;
			if(this->tree.search(this->tree.Root ,val) == this->tree.null_leaf)
			{
				this->tree.insert(val);
				true_or_false = true;
			}
			else
				true_or_false = false;
			iterator it = this->begin();
			while (it != this->end() && it->first != val.first)
				it++;
			return ft::make_pair(it, true_or_false);

		}

		iterator insert (iterator position, const value_type& val)
		{
			(void) position;
			this->tree.insert(val);
			iterator it = this->begin();
			while (it != this->end() && it->first != val.first)
				it++;
			return it;
		}

		template< class InputIt >
		void insert( InputIt first, InputIt last )
		{
			for(;first != last; first++)
				this->insert(*first);
		}

		// fct pour supprimer 

		void erase(iterator position)
		{
			this->tree.deleteNode(this->tree.Root, *position);
		}

		size_type erase (const key_type& k)
		{
			iterator it = this->begin();

			for (; it != this->end(); it++)
			{
				if (k == it->first)
				{
					this->tree.deleteNode(this->tree.Root, *it);
					return (1);
				}
			}
			return (0);
		}

		void erase (iterator first, iterator last)
		{
			while (first != last)
			{
				iterator tmp(first);
				++tmp;
				this->erase(first);
				first = tmp;
			}
		}

		void clear()
		{
			iterator it = this->begin();
			iterator ite = this->end();
			erase(it, ite);
		}

		bool empty() const
		{
			if(size() == 0)
				return true;
			else
				return false;
			return false;
		}


		pair<iterator,iterator> equal_range( const Key& key )
		{
			iterator lower = lower_bound(key);
			iterator upper = upper_bound(key);
			return(ft::make_pair(lower, upper));
		}

		pair<const_iterator,const_iterator> equal_range( const Key& key ) const
		{
			const_iterator lower = lower_bound(key);
			const_iterator upper = upper_bound(key);
			return(ft::make_pair(lower, upper));
		}

		iterator lower_bound( const Key& key )
		{
			iterator it = this->begin();
			iterator ite= this->end();
			for (; it != ite; it++)
			{
				if(comp(it->first, key) == false)
				{
					return(it);
				}	
			}
			return(ite);
		}

		const_iterator lower_bound( const Key& key ) const
		{
			const_iterator it = this->begin();
			const_iterator ite= this->end();
			for (; it != ite; it++)
			{
				if(comp(it->first, key) == false)
				{
					return(it);
				}	
			}
			return(ite);
		}

		iterator upper_bound( const Key& key )
		{
			iterator it = this->begin();
			iterator ite= this->end();
			for (; it != ite; it++)
			{
				if(comp(key, it->first))
				{
					return(it);
				}	
			}
			return(ite);
		}

		const_iterator upper_bound( const Key& key ) const
		{
			const_iterator it = this->begin();
			const_iterator ite= this->end();
			for (; it != ite; it++)
			{
				if(comp(key, it->first))
				{
					return(it);
				}	
			}
			return(ite);
		}

		iterator find( const Key& key )
		{
			iterator it = this->begin();
			iterator ite = this->end();
			for (; it != ite; it++)
			{
				if(comp(key, it->first) == false && comp(it->first, key) == false)
					return (it);
			}
			return(it);
		}

		const_iterator find( const Key& key ) const
		{
			const_iterator it = this->begin();
			const_iterator ite = this->end();
			for (; it != ite; it++)
			{
				if(comp(key, it->first) == false && comp(it->first, key) == false)
					return (it);
			}
			return(it);
		}

		size_type count( const Key& key ) const
		{
			const_iterator it = this->begin();
			const_iterator ite = this->end();
			for (; it != ite; it++)
			{
				if(comp(key, it->first) == false && comp(it->first, key) == false)
					return (1);
			}
			return(0);
		}

		void swap (map& x)
		{
			binary_tree<value_type, key_compare>	temp_tree;
			temp_tree = tree;
			tree = x.tree;
			x.tree = temp_tree;
			//tree.swap(x.tree);
		}


};

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return false;
	else if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) == true)
		return true;
	return false;
}

template <class Key, class T, class Compare, class Alloc>
  bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
  {
	  return (!(lhs == rhs));
  }

template <class Key, class T, class Compare, class Alloc>
  bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
  {
	  return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
  }

template <class Key, class T, class Compare, class Alloc>
  bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
  {
	  return (rhs < lhs);
  }

template <class Key, class T, class Compare, class Alloc>
  bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
  {
	  return (!(lhs < rhs));
  }

template <class Key, class T, class Compare, class Alloc>
  bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
  {
	  	  return (!(rhs < lhs));
  }

template <class Key, class T, class Compare, class Alloc>
  void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
  {
	  x.swap(y);
  }


};

#endif
