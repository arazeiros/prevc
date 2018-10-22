#include <prevc/pipeline/AST/declarations.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Declarations::Declarations(Pipeline* pipeline, util::Location&& location, std::vector<Declaration*>&& declarations):
                CollectionNode(pipeline, std::move(location), std::move(declarations))
            {

            }

            void Declarations::check_semantics()
            {
                for (auto& declaration: *this)
                    declaration->check_semantics();
            }
        }
    }
}
