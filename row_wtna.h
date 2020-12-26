#ifndef ROW_WTNA_H
#define ROW_WTNA_H

#include "row_base.h"
#include <iosfwd>

class row_wtna : virtual public row_base
{
  public:
    row_wtna(addr_type assoc);
    result_t mem_write(addr_type index);
    void print(std::ostream &os) const;
    bool write_policy() const;
};

#endif // !ROW_WTNA_H