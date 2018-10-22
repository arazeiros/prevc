#include <prevc/pipeline/AST/function-declaration.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            FunctionDeclaration::FunctionDeclaration(Pipeline* pipeline, util::Location&& location,
                                     const util::String& name, Type* type, AST::Parameters* parameters,
                                     Expression* implementation):
                Declaration(pipeline, std::move(location), name, type),
                parameters(parameters),
                implementation(implementation)
            {

            }

            FunctionDeclaration::~FunctionDeclaration()
            {
                delete parameters;

                if (implementation != nullptr)
                    delete implementation;
            }

            void FunctionDeclaration::check_semantics()
            {
                // TODO consider inserting declarations during semantic check of the "compound expression"

                auto& global_namespace = pipeline->global_namespace;

                global_namespace->push_scope();
                parameters->check_semantics();
                implementation->check_semantics();
                global_namespace->pop_scope();
            }

            util::String FunctionDeclaration::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "function-declaration", "location": %s, "name": "%s", "declarationType": %s, "parameters": %s, "implementation": %s})",
                        location.to_string().c_str(),
                        name.c_str(),
                        type->to_string().c_str(),
                        parameters->to_string().c_str(),
                        implementation == nullptr
                            ? "null"
                            : implementation->to_string().c_str());
            }
        }
    }
}
