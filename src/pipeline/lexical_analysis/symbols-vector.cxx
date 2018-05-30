#include <prevc/pipeline/lexical_analysis/symbols-vector.hxx>
#include <iostream>
#include <sstream>

namespace prevc
{
    namespace pipeline
    {
        namespace lexical_analysis
        {
            util::String SymbolsVector::to_string() const noexcept
            {
                std::stringbuf buffer;
                std::ostream out(&buffer);
                auto i = begin();
                auto n = end();
                out << "{\"symbols\": [";

                if (size() != 0)
                {
                    out << i->to_string().c_str();

                    while (++i != n)
                    {
                        out << ", ";
                        out << i->to_string().c_str();
                    }
                }
                out << "]}";
                return buffer.str();
            }
        }
    }
}
