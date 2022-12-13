#include <vector>
#include <list>
#include <iostream>
#include <iterator>

#pragma execution_character_set("utf-8")

//#include <cassert>


template<class T>
class VectorList
{
private:
    using VectT = std::vector<T>;
    using ListT = std::list<VectT>;
    using listT_it = typename ListT::const_iterator;
    using vecT_it = typename VectT::const_iterator;

public:
    using value_type = const T;

    VectorList() = default;
    VectorList(ListT& data) : data_(data) {};
    VectorList(VectorList const&) = default;
    VectorList(VectorList&&) = default;

    VectorList& operator=(VectorList&&) = default;
    VectorList& operator=(VectorList const&) = default;

    // метод, который будет использоваться для заполнения VectorList
    // гарантирует, что в списке не будет пустых массивов
    template<class It>
    void append(It p, It q); // определена снаружи  
/*  {
        if (p != q)
            data_.push_back(VectT(p,q));
    }
*/

    bool empty() const { return this->size() == 0; }

    // определите метод size
    size_t size() const
    {
        size_t sz = 0;
        for (auto it_list = this->data_.begin(); it_list != this->data_.end(); ++it_list)
        {
            sz += (*it_list).size();
        }
        return sz;
    }

    
    class const_iterator:  public std::iterator<std::bidirectional_iterator_tag, const T>  //, std::ptrdiff_t, T*, const T&>
    {
    public: 
        // constructors
        const_iterator() = default;
        const_iterator(ListT const* data, listT_it & lit, vecT_it & vit )   
        {        
            this->data_ = data;
            this->listT_iter = lit;
            if (!data->empty())
            {
                this->vecT_iter = vit;
            }
            else
            {
                this->vecT_iter = vecT_it();
            }
        };
        const_iterator(const const_iterator&) = default;

        // postfix
        const_iterator operator++ (int)
        {
            listT_it last_iter_list = --(this->data_->end());
            const_iterator old = *this;
            // if last  elem of list
            if (this->listT_iter == last_iter_list)
            {
                vecT_it end_iter_vec = (*this->listT_iter).end();
                if (this->vecT_iter == end_iter_vec)
                {
                    return *this;
                }
                else
                {
                    ++this->vecT_iter;
                    return old;
                }
            }
            // not last elem of list
            else
            {
                vecT_it last_iter_vec = --(*this->listT_iter).end();
                if (this->vecT_iter == last_iter_vec)
                {
                    ++this->listT_iter;
                    this->vecT_iter = (*this->listT_iter).begin();
                    return old;
                }
                else
                {
                    ++this->vecT_iter;
                    return old;
                }
            }
        };
        // prefix
        const_iterator& operator++ ()
        {
            listT_it last_iter_list = --(this->data_->end());
            // if last  elem of list
            if (this->listT_iter == last_iter_list)
            {
                vecT_it end_iter_vec = (*this->listT_iter).end();
                if (this->vecT_iter == end_iter_vec)
                {
                    return *this;
                }
                else
                {
                    ++this->vecT_iter;
                    return *this;
                }
            }
            // not last elem of list
            else
            {
                vecT_it last_iter_vec = --(*this->listT_iter).end();
                if (this->vecT_iter == last_iter_vec)
                {
                    ++this->listT_iter;
                    this->vecT_iter = (*this->listT_iter).begin();
                    return *this;
                }
                else
                {
                    ++this->vecT_iter;
                    return *this;
                }
            }
        }
       
        
        // postfix
        const_iterator operator-- (int)
        {
            listT_it first_iter_list = this->data_->begin();
            const_iterator old = *this;

            // if first  elem of list
            if (this->listT_iter == first_iter_list)
            {
                vecT_it first_iter_vec = (*this->listT_iter).begin();
                if (this->vecT_iter == first_iter_vec)
                {
                    return *this;
                }
                else
                {
                    --this->vecT_iter;
                    return old;
                }
            }
            // not first elem of list
            else
            {
                vecT_it first_iter_vec = (*this->listT_iter).begin();
                if (this->vecT_iter == first_iter_vec)
                {
                    --this->listT_iter;
                    this->vecT_iter = --(*this->listT_iter).end();
                    return old;
                }
                else
                {
                    --this->vecT_iter;
                    return old;
                }
            }
        }
        // prefix
        const_iterator& operator--()
        {
            listT_it first_iter_list = this->data_->begin();
            // if first  elem of list
            if (this->listT_iter == first_iter_list)
            {
                vecT_it first_iter_vec = (*this->listT_iter).begin();
                if (this->vecT_iter == first_iter_vec)
                {
                    return *this;
                }
                else
                {
                    --this->vecT_iter;
                    return *this;
                }
            }
            // not first elem of list
            else
            {
                vecT_it first_iter_vec = (*this->listT_iter).begin();
                if (this->vecT_iter == first_iter_vec)
                {
                    --this->listT_iter;
                    this->vecT_iter = --(*this->listT_iter).end();
                    return *this;
                }
                else
                {
                    --this->vecT_iter;
                    return *this;
                }
            }
        }
        
        bool operator!= (const const_iterator& it) const
        {
            
            return !this->operator==(it);
            // alternative realization
            //if (this->listT_iter != it.listT_iter)
            //{
            //    return true;
            //}
            //else
            //{
            //    return this->getConstIt() != it.getConstIt();
            //}
        }
  
        bool operator== (const const_iterator& it) const
        {
            if (this->listT_iter != it.listT_iter)
            {
                return false;
            }
            else
            {
                return this->getConstIt() == it.getConstIt();
            }
        }

        T& operator*() const
        {
           // auto vec_data = *this->vecT_iter;
            return (T&)(*this->vecT_iter);
        }

        T* operator->() const
        {
            return (T*)&(*this->vecT_iter);
        }

        const vecT_it getConstIt() const
        {
            return static_cast<const vecT_it>(this->vecT_iter);
        }

    protected:
    ListT const* data_ = nullptr;
    listT_it listT_iter;
    vecT_it vecT_iter;     
    };

    using const_iterator = VectorList<T>::const_iterator;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        
        // определите методы begin / end
    const_iterator begin() const
    {
        if (this->empty())
        {
            return const_iterator{};
        }
        else
        {
            ListT const* list_data = &this->data_;
            listT_it lit_beg = list_data->begin();
            vecT_it vit_beg = list_data->empty() ? vecT_it{} : (*lit_beg).begin();
            return const_iterator{ list_data, lit_beg, vit_beg };
        }
    }

    const_iterator end() const 
    { 
        if (this->empty())
        {
            return const_iterator{};
        }
        else
        {
            ListT const* list_data = &this->data_;
            listT_it lit_end = --list_data->end();
            vecT_it vit_end = list_data->empty() ? vecT_it{} : (*lit_end).end();
            return const_iterator{ list_data, lit_end, vit_end };

        }
    }
    
    // определите const_reverse_iterator
  //  typedef std::reverse_iterator<iterator> reverse_iterator;
    // определите методы rbegin / rend
    const_reverse_iterator rbegin() const { return const_reverse_iterator{ this->end() }; }

    const_reverse_iterator rend()   const { return const_reverse_iterator{ this->begin() }; }

private:
    ListT data_;
};


template<class T>
template<class It>
void VectorList<T>::append(It p, It q)
{
    if (p != q)
        data_.push_back(VectT(p, q));
}







size_t size_l(std::list<std::vector<int>> l)
{
    size_t sz = 0;
    for (auto it_list = l.begin(); it_list != l.end(); ++it_list)
    {
        sz += (*it_list).size();
    }
    return sz;
};


int main(int argc, char * argv)
{
  /*  using vec_int = std::vector<int>;
    // {};
    vec_int v1 = { 1, 2 }; 
    vec_int v2 =  { 3, 4 };
    vec_int v3 = { 5, 6 };

    std::list<vec_int> l = { v1 , v2, v3};  
   // std::list<int>::iterator
    auto &lv = *l.begin();
//    auto itv = v1.begin();
    VectorList<int> vl_test(l);
  //  vl_test.append(v1.begin(), v1.end());
  //  vl_test.append(v2.begin(), v2.end());
   // vl_test.append(v3.begin(), v3.end());

    VectorList<int>::const_iterator beg_iter = vl_test.begin();    */
   // std::cout << beg_iter << std::endl;


    //std::cout << *beg_iter << std::endl;
   // auto it = vl_test.begin();
    /*
    for (VectorList<int>::const_iterator it = vl_test.begin(); it != vl_test.end(); it++)
    {
        std::cout << *it << std::endl;
    }  
    */
  /*
    for (VectorList<int>::const_iterator it = --vl_test.end(); ; it--)
    {
        std::cout << *it << std::endl;
        if (it == vl_test.begin())
            break;
    }  
  */  
    //auto it = v1.begin();
    //++it; ++it;
    //auto end_it = v1.end();
    //bool res = it == end_it;
    //std::cout << "test it = " << (it == v1.end()) << std::endl;
 //   std::cout <<  l.size() << std::endl;




    std::vector<char> v1{ 'A', 'B', 'C'};
    std::vector<char> v2{'D', 'E', 'F', 'G'};

    std::list<std::vector<char>> l{ v1 , v2 };
    VectorList<char> vlist{ l };

    auto i = vlist.begin();

    std::cout << "Size is " << vlist.size() << std::endl;
    std::cout << "begin is " << *i << std::endl;
 //   std::cout << "std::distance(begin,end)﻿ " << (std::distance(vlist.begin(), vlist.end())) << std::endl;
    std::cout << "*(++begin) == 'B'? " << (*++vlist.begin() == 'B') << std::endl;
    std::cout << "*(++begin) == 'A'? " << (*++vlist.begin() == 'A') << std::endl;
    std::cout << std::endl;


    std::cout << "Test ++i" << std::endl;
    for (i = vlist.begin(); i != vlist.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Test i++" << std::endl;
    for (i = vlist.begin(); i != vlist.end(); i++)
        std::cout << *i << " ";
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Test --i" << std::endl;
    for (i = vlist.end(); i != vlist.begin();)
        std::cout << *--i << " ";
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Test i--" << std::endl;
    for (i = vlist.end(); i != vlist.begin();) {
        i--;
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    
    std::cout << std::endl;
    auto j = vlist.rbegin();
    std::cout << "rbegin is " << *j << std::endl;
    j = --vlist.rend();
    std::cout << "--rend is " << *j << std::endl;

    std::cout << "Test reverse_const_iterator ++" << std::endl;
    for (j = vlist.rbegin(); j != vlist.rend(); ++j)
        std::cout << *j << " ";
    std::cout << std::endl;  


    system("pause");

    
    return 0;
}