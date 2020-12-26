#include "row.h"
#include "row_lfu.h"
#include "row_lru.h"
#include "row_wbwa.h"
#include "row_wtna.h"

std::unique_ptr<row_base> make_row(row_base::addr_type assoc, bool replacement_policy, bool write_policy)
{
    if (replacement_policy)
    {
        if (write_policy)
        {
            return std::make_unique<row<row_lfu, row_wtna>>(assoc);
        }
        else
        {
            return std::make_unique<row<row_lfu, row_wbwa>>(assoc);
        }
    }
    else
    {
        if (write_policy)
        {
            return std::make_unique<row<row_lru, row_wtna>>(assoc);
        }
        else
        {
            return std::make_unique<row<row_lru, row_wbwa>>(assoc);
        }
    }
}