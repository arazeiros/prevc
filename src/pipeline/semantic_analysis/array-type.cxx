#include <prevc/pipeline/semantic_analysis/array-type.hxx>
#include <sstream>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            static inline util::String to_semantic_string(const Type* sub, size_t length)
            {
                std::stringstream stream;
                stream << "arr [";
                stream << length;
                stream << "] ";
                stream << sub->id.c_str();
                return stream.str();
            }

            ArrayType::ArrayType(const Type* sub, size_t length):
                Type(to_semantic_string(sub, length), Type::Kind::ARRAY),
                sub(sub),
                length(length)
            {

            }

            util::String ArrayType::to_string() const noexcept
            {
                return id;
            }
        }
    }
}
