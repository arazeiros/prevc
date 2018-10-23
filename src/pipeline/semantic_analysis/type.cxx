#include <prevc/pipeline/semantic_analysis/type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            static bool is_word(const util::String& type)
            {
                return type == "bool"
                    || type == "char"
                    || type == "int"
                    || type.starts_with("ptr");
            }

            static bool is_returnable(const util::String& type)
            {
                return type == "void" || is_word(type);
            }

            Type::Type(prevc::util::String&& id):
                util::String(std::move(id)),
                can_be_assigned(is_word(*this)),
                can_be_passed(is_word(*this)),
                can_be_returned(is_returnable(*this))
            {

            }
        }
    }
}
