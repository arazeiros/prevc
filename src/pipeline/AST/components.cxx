#include <prevc/pipeline/AST/components.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Components::Components(Pipeline* pipeline, util::Location&& location, std::vector<Component*>&& components):
                CollectionNode(pipeline, std::move(location), std::move(components))
            {

            }

            void Components::check_semantics()
            {
                for (auto& component : *this)
                    component->check_semantics();
            }
        }
    }
}
