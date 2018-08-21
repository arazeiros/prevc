#include <prevc/pipeline/AST/function-declaration.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            FunctionDeclaration::FunctionDeclaration(Pipeline* pipeline, util::Location&& location,
                                     const util::String& name, Type* type, AST::Parameters* parameters):
                Declaration(pipeline, std::move(location), name, type),
                parameters(parameters)
            {

            }

            FunctionDeclaration::~FunctionDeclaration()
            {
                delete parameters;
            }

            util::String FunctionDeclaration::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "function-declaration", "location": %s, "name": "%s", "declarationType": %s, "parameters": %s})",
                        location.to_string().c_str(),
                        name.c_str(),
                        type->to_string().c_str(),
                        parameters->to_string().c_str());
            }
        }
    }
}
