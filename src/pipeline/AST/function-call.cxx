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
                arguments(arguments)
            {

            }

            FunctionCall::~FunctionCall()
            {
                delete arguments;
            }

            llvm::Value* FunctionCall::generate_IR(llvm::IRBuilder<>* builder)
            {
                auto& module   = pipeline->IR_module;
                auto  function = module->getFunction(this->name.c_str());
                std::vector<llvm::Value*> args;

                for (auto argument : *arguments)
                    args.emplace_back(argument->generate_IR(builder));

                return builder->CreateCall(function, args);
            }

            std::optional<int64_t> FunctionCall::evaluate_as_integer() const noexcept
            {
                return {};
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
