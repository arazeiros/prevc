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
                id(pipeline->next_declaration_id++),
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
                type->check_semantics();
                get_semantic_type(); // also generate the semantic type if not generated yet
            }

            const semantic_analysis::Type* Declaration::generate_semantic_type()
            {
                return type->get_semantic_type();
            }

            const semantic_analysis::Type* Declaration::get_semantic_type()
            {
                if (semantic_type == nullptr)
                    semantic_type = generate_semantic_type();

                return semantic_type;
            }
        }
    }
}
