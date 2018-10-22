#include <prevc/pipeline/AST/statements.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Statements::Statements(Pipeline* pipeline, util::Location&& location, std::vector<Statement*>&& nodes):
                CollectionNode(pipeline, std::move(location), std::move(nodes))
            {

            }

            void Statements::check_semantics()
            {
                for (auto& statement : *this)
                    statement->check_semantics();
            }

            void Statements::generate_IR(llvm::IRBuilder<>* builder)
            {
                for (auto statement : *this)
                    statement->generate_IR(builder);
            }
        }
    }
}
