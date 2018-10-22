#include <prevc/pipeline/AST/arguments.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Arguments::Arguments(Pipeline* pipeline, util::Location&& location, std::vector<Expression*>&& arguments):
                CollectionNode(pipeline, std::move(location), std::move(arguments))
            {

            }

            void Arguments::check_semantics()
            {
                for (auto& argument : *this)
                    argument->check_semantics();
            }
        }
    }
}
