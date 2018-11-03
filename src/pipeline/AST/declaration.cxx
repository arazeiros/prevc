#include <prevc/pipeline/AST/declaration.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Declaration::Declaration(Pipeline* pipeline, util::Location&& location, Kind kind,
                                     const util::String& name, Type* type):
                Node(pipeline, std::move(location)),
                kind(kind),
                name(name),
                type(type),
                semantic_type(nullptr)
            {

            }

            Declaration::~Declaration()
            {
                delete type;
            }

            void Declaration::check_semantics()
            {
                semantic_type = type->get_semantic_type();
            }

            const semantic_analysis::Type* Declaration::get_semantic_type()
            {
                return semantic_type;
            }
        }
    }
}
