#include "rangelist.h"
#include<sstream>
using namespace std;

// use binary search to find the center for the element
int RangeList::search(const Interval &elem)
{
    int l = 0, r = vec_.size()-1;
    while(l<=r) {
        int mid = (l + r) /2;
        if (vec_[mid].intersect(elem)) {
            return mid;
        }
        if(vec_[mid] < elem) {
            l = mid+1;
        } else {
            r = mid-1;
        }
    }
    return l;
}

void RangeList::merge(int index)
{
    int left = index;
    // search left bondary and right bondary from center
    while(left>=0) {
        if (vec_[left] < vec_[index]) {
            break;
        }
        left --;
    }
    int right = index;
    while(right < vec_.size()) {
        if(vec_[right] > vec_[index]) {
            break;
        }
        right ++;
    }
    // merge from left + 1 to right -1
    int del_left = -1, del_right = -1, target = -1;
    for(int i=left+1; i< right -1; i++) {
        int j = i +1;
        // use element at target index to merge the behind
        if (vec_[i].intersect(vec_[j]) && target == -1) {
            if (target == -1) {
                del_left = j;
                target = i;
            }
        }
        if (target != -1) {
            if(vec_[target].intersect(vec_[j])) {
                del_right = j;
            }
            // if overlap, only keep the first one, use del_left to track the scope to remove
            vec_[target].merge(vec_[j]);
        }
    }
    if (target == -1) {
        return;
    }
    // remove element from del_left to del_right, del_right +1 as erase do not include the last index.
    vec_.erase(vec_.begin() + del_left, vec_.begin() + del_right+1);
}

void RangeList::minus(int index, const Interval &elem)
{
    int left = index;
    // search left bondary and right bondary from center
    while(left>=0) {
        if (vec_[left] < elem) {
            break;
        }
        left --;
    }
    int right = index;
    while(right < vec_.size()) {
        if(vec_[right] > elem) {
            break;
        }
        right ++;
    }
    int del_left = -1, del_right = -1;
    for(int i=left+1; i<right; i++) {
        if(!vec_[i].intersect(elem)) {
            continue;
        }
        vector<Interval> ret = vec_[i].minus(elem);
        if (ret.size()== 0) {
            // cover case, need to find the remove scope from the loop
            // xxxxxxxxxxxxxxxxx
            //   yy  yyy  yy
            if(del_left == -1) {
                del_left = i;
            }
            del_right = i;
        }
        // split case
        //       xx
        // yyyyyyyyyyyyyyyyy
        if (ret.size() == 2) {
            vec_.insert(vec_.begin() + i+1, ret[1]);
            break;
        }
        // ret.size() == 1 do nothing, already modify inside
    }

    if (del_left != -1) {
        vec_.erase(vec_.begin() + del_left, vec_.begin() + del_right+1);
    }
}

void RangeList::Add(const Interval &elem)
{
    if (vec_.empty()) {
        vec_.push_back(elem);
        return;
    }
    int index = search(elem);
    vec_.insert(vec_.begin() + index, elem);
    merge(index);
}

void RangeList::Remove(const Interval &elem)
{
    if (vec_.empty()) {
        return;
    }
    int index = search(elem);
    minus(index, elem);
}

std::string RangeList::ToString() const
{
    std::ostringstream ostr;
    for(int i=0; i<vec_.size(); i++ ) {
        Interval elem = vec_[i];
        if (i != vec_.size() -1) {
            ostr << "[" << elem.start << "," <<  elem.end << ") ";
        } else {
            ostr << "[" << elem.start << "," << elem.end << ")";
        }
    }
    return ostr.str();
}
