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
                type(type)
            {

            }

            Declaration::~Declaration()
            {
                delete type;
            }
        }
    }
}
