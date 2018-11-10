#include <prevc/pipeline/AST/unary-operation.hxx>
#include <prevc/pipeline/semantic_analysis/atom-type.hxx>
#include <prevc/pipeline/semantic_analysis/pointer-type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            UnaryOperation::UnaryOperation(Pipeline* pipeline, util::Location&& location, UnaryOperation::Operator operator_, Expression* sub_expression):
                Expression(pipeline, std::move(location)),
                operator_(operator_),
                sub_expression(sub_expression)
            {

            }

            UnaryOperation::~UnaryOperation()
            {
                delete sub_expression;
            }

            void UnaryOperation::check_semantics()
            {
                sub_expression->check_semantics();

                const auto& expression_type = sub_expression->get_semantic_type();

                switch (operator_)
                {
                    case Operator::PLUS:
                    case Operator::MINUS:
                    {
                        if (!expression_type->is_int())
                            CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                                    "arithmetic unary operators can be used only on expressions of type `int`, "
                                    "but the given expression is of type `%s`",
                                    expression_type->to_string().c_str()));

                        break;
                    }

                    case Operator::NOT:
                    {
                        if (!expression_type->is_bool())
                            CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                                    "negation unary operator can be used only on expressions of type `bool`, "
                                    "but the given expression is of type `%s`",
                                    expression_type->to_string().c_str()));
                        break;
                    }

                    case Operator::DEL:
                    {
                        if (!(expression_type->is_pointer() &&
                            !((const semantic_analysis::PointerType*) expression_type)->sub->is_void()))
                                CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                                        "`del` command requires an expression of type `ptr <non-void>`, "
                                        "but the given expression is of type `%s`",
                                        expression_type->to_string().c_str()));

                        break;
                    }

                    case Operator::MEM:
                    {
                        if (!sub_expression->is_lvalue())
                            CompileTimeError::raise(pipeline->file_name, location,
                                    "only lvalue expressions can be referenced, "
                                    "but the given expression is not");

                        if (expression_type->is_void())
                            CompileTimeError::raise(pipeline->file_name, location,
                                    "expressions of type `void` can't be referenced, "
                                    "but the given expression is of type `void`");

                        break;
                    }

                    case Operator::VAL:
                    {
                        if (!(expression_type->is_pointer() &&
                              !((const semantic_analysis::PointerType*) expression_type)->sub->is_void()))
                            CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                                    "only expression of type `ptr <non-void>` can be dereferenced, "
                                    "but the given expression is of type `%s`",
                                    expression_type->to_string().c_str()));
                        break;
                    }
                }
            }

            llvm::Value* UnaryOperation::generate_IR(llvm::IRBuilder<>* builder)
            {
                auto sub = sub_expression->generate_IR(builder);
                auto& module = pipeline->IR_module;

                switch (operator_)
                {
                    case Operator::PLUS:
                        return sub;

                    case Operator::MINUS:
                        return builder->CreateNeg(sub);

                    case Operator::NOT:
                        return builder->CreateXor(sub, 1);

                    case Operator::DEL:
                    {
                        auto  f_free = module->getFunction("free");
                        builder->CreateCall(f_free, llvm::ArrayRef<llvm::Value*>({sub}));
                        return sub; // returning the freed address
                    }

                    case Operator::MEM:
                        // TODO implement...
                        break;

                    case Operator::VAL:
                        return builder->CreateLoad(sub);
                }

                InternalError::raise("illegal state: case not handled: UnaryOperation::generate_IR");
                return nullptr;
            }

            std::optional<int64_t> UnaryOperation::evaluate_as_integer() const noexcept
            {
                auto optional_sub = sub_expression->evaluate_as_integer();

                if (!optional_sub.has_value())
                    return {};

                auto evaluated = optional_sub.value();

                switch (operator_)
                {
                    case Operator::PLUS:
                        return +evaluated;

                    case Operator::MINUS:
                        return -evaluated;

                    default:
                        return {};
                }
            }

            bool UnaryOperation::is_lvalue() const noexcept
            {
                return (operator_ == Operator::VAL) && sub_expression->is_lvalue();
            }

            const semantic_analysis::Type* UnaryOperation::get_semantic_type()
            {
                using SAtom = semantic_analysis::AtomType;
                using SPointer = semantic_analysis::PointerType;

                switch (operator_)
                {
                    case Operator::PLUS:
                    case Operator::MINUS:
                    case Operator::NOT:
                        return sub_expression->get_semantic_type();

                    case Operator::DEL:
                        return pipeline->type_system->get_or_insert("void", [] () { return new SAtom(SAtom::Kind::VOID); });

                    case Operator::MEM:
                    {
                        auto sub_type = sub_expression->get_semantic_type();
                        return pipeline->type_system->get_or_insert(util::String("ptr ") + sub_type->id,
                                [sub_type] () { return new SPointer(sub_type); });
                    }

                    case Operator::VAL:
                        return ((SPointer*) sub_expression->get_semantic_type())->sub;
                }
            }

            util::String UnaryOperation::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "unary-operation", "location": %s, "operator": "%s", "sub": %s})",
                        location.to_string().c_str(),
                        AST::to_string(operator_),
                        sub_expression->to_string().c_str());
            }
        }
    }
}
