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

            void Compound::check_semantics()
            {
                auto& global_namespace = pipeline->global_namespace;
                global_namespace->push_scope();

                for (auto& declaration : *declarations)
                {
                    if (global_namespace->insert_declaration(declaration))
                        continue;

                    auto  duplicate = global_namespace->find_declaration(declaration->name).value();
                    auto& location  = duplicate->location;

                    CompileTimeError::raise(pipeline->file_name, declaration->location,
                            util::String::format("identifier `%s` already used in current scope (at %d:%d)",
                                    declaration->name.c_str(), location.line_0, location.column_0));
                }

                declarations->check_semantics();
                statements->check_semantics();
                expression->check_semantics();

                global_namespace->pop_scope();
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

            const semantic_analysis::Type* Compound::get_semantic_type()
            {
                return expression->get_semantic_type();
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
