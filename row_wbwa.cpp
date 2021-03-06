#include "row_wbwa.h"
#include <iomanip>
#include <ostream>

row_wbwa::row_wbwa(addr_type assoc) : row_base(assoc), dirty(assoc)
{
}

row_wbwa::result_t row_wbwa::mem_read(addr_type index)
{
    const auto it = pgmap.find(index);
    result_t r{};
    if (it == pgmap.end())
    {
        const addr_type d = replace();
        pgmap.erase(row[d]);
        row[d] = index;
        pgmap[index] = d;
        r.bf.miss = true;
        if (dirty[d])
        {
            r.bf.wb = true;
            dirty[d] = false;
        }
    }
    else
    {
        update(index);
    }
    return r;
}

row_wbwa::result_t row_wbwa::mem_write(addr_type index)
{
    const auto it = pgmap.find(index);
    result_t r{};
    if (it == pgmap.end())
    {
        const addr_type d = replace();
        pgmap.erase(row[d]);
        row[d] = index;
        pgmap[index] = d;
        r.bf.miss = true;
        if (dirty[d])
        {
            r.bf.wb = true;
        }
        else
        {
            dirty[d] = true;
        }
    }
    else
    {
        dirty[it->second] = true;
        update(index);
    }
    return r;
}

void row_wbwa::output(std::ostream &os) const
{
    auto fmt = os.flags();
    os << std::hex << std::right << std::noshowbase << std::nouppercase;
    for (addr_type i = 0; i < dirty.size(); i++)
    {
        os << std::setw(sizeof(addr_type) * 2 + 2) << row[i] << ' ' << (dirty[i] ? 'D' : ' ');
    }
    os.setf(fmt);
}

bool row_wbwa::write_policy() const
{
    return false;
}
