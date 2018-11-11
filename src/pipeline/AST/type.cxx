#include <prevc/pipeline/AST/type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Type::Type(Pipeline* pipeline, util::Location&& location):
                Node(pipeline, std::move(location)),
                semantic_type(nullptr)
            {

            }

            const semantic_analysis::Type* Type::get_semantic_type() noexcept
            {
                if (semantic_type != nullptr)
                    return semantic_type;

                semantic_type = generate_semantic_type(true);
                return semantic_type;
            }
        }
    }
}
