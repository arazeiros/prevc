#include <prevc/pipeline/AST/function-call.hxx>
#include <utility>
#include <prevc/error.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            FunctionCall::FunctionCall(Pipeline* pipeline, util::Location&& location,
                    const util::String& name, Arguments* arguments):
                Expression(pipeline, std::move(location)),
                name(name),
                arguments(arguments),
                declaration(nullptr)
            {

            }

            FunctionCall::~FunctionCall()
            {
                delete arguments;
            }

            void FunctionCall::check_semantics()
            {
                auto declaration_optional = pipeline->global_namespace->find_declaration(name);

                if (!declaration_optional.has_value())
                    CompileTimeError::raise(pipeline->file_name, location,
                            util::String::format("function `%s` not declared", name.c_str()));

                auto declaration = declaration_optional.value();

                if (declaration->kind != Declaration::Kind::Function)
                    CompileTimeError::raise(pipeline->file_name, location,
                            util::String::format("declared identifier `%s` is not a function", name.c_str()));

                this->declaration = (FunctionDeclaration*) declaration;
                arguments->check_semantics();
                auto& parameters = this->declaration->parameters;
                auto size = arguments->size();

                if (size != parameters->size())
                    CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                            "calling function `%s`, number of arguments must match the number of parameters of defined function, "
                            "but there are `%i` arguments for `%i` required parameters",
                            name.c_str(), size, parameters->size()));

                for (size_t i = 0; i < size; ++i)
                {
                    auto&      argument       = arguments->at(i);
                    const auto argument_type  = argument->get_semantic_type();
                    const auto parameter_type = parameters->at(i)->get_semantic_type();

                    if (!argument_type->equals(parameter_type))
                        CompileTimeError::raise(pipeline->file_name, argument->location, util::String::format(
                                "calling function `%s`, types of arguments and parameters at the same positions have to match, "
                                "but the argument #%i is of type `%s`, when type `%s` is required",
                                name.c_str(), i + 1, argument_type->to_string().c_str(), parameter_type->to_string().c_str()));
                }
            }

            llvm::Value* FunctionCall::generate_IR(llvm::IRBuilder<>* builder)
            {
                auto& module   = pipeline->IR_module;
                auto  function = module->getFunction(this->declaration->get_native_name().c_str());

                if (function == nullptr)
                    InternalError::raise(util::String::format(
                            "function `%s` doesn't exists", this->declaration->get_native_name().c_str()));

                std::vector<llvm::Value*> args;

                for (auto argument : *arguments)
                    args.emplace_back(argument->generate_IR(builder));

                return builder->CreateCall(function, args);
            }

            std::optional<int64_t> FunctionCall::evaluate_as_integer() const noexcept
            {
                return {};
            }

            const semantic_analysis::Type* FunctionCall::get_semantic_type()
            {
                return declaration->type->get_semantic_type();
            }

            util::String FunctionCall::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "function-call", "location": %s, "name": "%s", "arguments": %s})",
                        location.to_string().c_str(),
                        name.c_str(),
                        arguments->to_string().c_str());
            }
        }
    }
}
