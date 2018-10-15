#include <prevc/pipeline/AST/compound.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Compound::Compound(Pipeline* pipeline, util::Location&& location, Statements* statements,
                               Expression* expression, Declarations* declarations):
                Expression(pipeline, std::move(location)),
                statements(statements),
                expression(expression),
                declarations(declarations)
            {

            }

            Compound::~Compound()
            {
                delete statements;
                delete expression;
                delete declarations;
            }

            llvm::Value* Compound::generate_IR(llvm::IRBuilder<>* builder)
            {
                for (auto statement : *statements)
                    statement->generate_IR(builder);

                return expression->generate_IR(builder);
            }

            std::optional<int64_t> Compound::evaluate_as_integer() const noexcept
            {
                return {};
            }

            util::String Compound::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "compound", "location": %s, "statements": %s, "expression": %s, "declarations": %s})",
                        location.to_string().c_str(),
                        statements->to_string().c_str(),
                        expression->to_string().c_str(),
                        declarations->to_string().c_str()
                    );
            }
        }
    }
}
