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
                // TODO ...
                sub_expression->check_semantics();
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
