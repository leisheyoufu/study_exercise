#include<vector>
#include<tuple>
#include<algorithm>
#include<iostream>

struct Interval {
    int start;
    int end;
    Interval(int start, int end)
    {
        assert(start <= end);
        this->start = start;
        this->end = end;
    }

    bool operator <( const Interval &elem ) const
    {
        return end < elem.start? true: false;
    }
    bool operator >( const Interval &elem) const
    {
        return start > elem.end? true: false;
    }
    bool operator == (const Interval &elem) const
    {
        return (start == elem.start ) && (end == elem.end);
    }
    // check if has common part
    bool intersect(const Interval &elem) const
    {
        if (elem.end>=start && elem.start<=start ||
            elem.start<=end && elem.end >= end ||
            elem.start>=start && elem.end <=end ||
            elem.start <=start && elem.end >= end)
            return true;
        return false;
    }
    bool merge(const Interval &elem)
    {
        if(!intersect(elem)) {
            return false;
        }
        start = std::min(start, elem.start);
        end = std::max(end, elem.end);
        return true;
    }
    std::vector<Interval> minus(const Interval &elem)
    {
        if(!intersect(elem)) {
            return std::vector<Interval> {Interval(start, end)};
        }
        // smaller than the original, will split
        //     xxx
        // yyyyyyyyyyyyyy
        if (elem.end<end && elem.start > start) {
            // cut the first part, then return a new part to insert
            std::vector<Interval> v = std::vector<Interval> {Interval(start, elem.start), Interval(elem.end, end)};
            end = elem.start;
            return v;
        }
        // totally cover case
        // xxxxxxxxx
        //    yyyy
        if (elem.start <= start && elem.end >= end) {
            return std::vector<Interval>();
        }
        //    xxxx
        // yyyyy
        if (elem.start < end && elem.end >= end) {
            end = elem.start;
            return std::vector<Interval> {Interval(start, elem.start)};
        }
        // xxxx
        //    yyyy
        if (elem.end > start && elem.start <= start) {
            start = elem.end;
            return std::vector<Interval> {Interval(elem.end, end)};
        }
        // should not reach here
        return std::vector<Interval> {Interval(start, end)};
    }
};
class RangeList
{
private:
    std::vector<Interval> vec_;
    int search(const Interval &elem);
    void merge(int index);
    void minus(int index, const Interval &elem);
public:
    RangeList() {}
    RangeList(const RangeList&) = delete;
    RangeList& operator=(const RangeList&) = delete;

    ~RangeList() {}
    void Add(const Interval &elem);
    void Remove(const Interval &elem);
    std::string ToString() const;
};
