#include <prevc/pipeline/AST/atom.hxx>
#include <utility>
#include <prevc/error.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Atom::Atom(Pipeline* pipeline, util::Location&& location, Atom::Type type, const util::String& lexeme):
                Expression(pipeline, std::move(location)),
                type(type),
                lexeme(lexeme)
            {

            }

            Atom::~Atom() = default;

            static std::uint64_t string_to_uint64_t(const char* str)
            {
                std::uint64_t i = 0;

                while (*str != '\0')
                {
                    i *= 10;
                    i += *str - '0';
                    ++str;
                }

                return i;
            }

            void Atom::check_semantics()
            {
                // It's OK.
            }

            llvm::Value* Atom::generate_IR(llvm::IRBuilder<>* builder)
            {
                auto& context = pipeline->IR_module->getContext();

                switch (type)
                {
                    case Atom::Type::INTEGER:
                    {
                        auto type = llvm::Type::getInt64Ty(context);
                        return llvm::ConstantInt::get(type, string_to_uint64_t(lexeme.c_str()));
                    }

                    case Atom::Type::BOOLEAN:
                    {
                        auto type = llvm::Type::getInt8Ty(context);
                        return llvm::ConstantInt::get(type, (lexeme == "true") ? 1 : 0);
                    }

                    case Atom::Type::CHARACTER:
                    {
                        auto type = llvm::Type::getInt8Ty(context);
                        return llvm::ConstantInt::get(type, (std::uint64_t) lexeme.c_str()[1]);
                    }

                    case Atom::Type::VOID:
                    {
                        return llvm::ConstantInt::get(llvm::Type::getInt8Ty(context), 0); // just a random 0
                    }

                    case Atom::Type::POINTER:
                    {
                        return llvm::ConstantPointerNull::get(
                                llvm::PointerType::getUnqual(
                                        llvm::Type::getInt8Ty(context))); // aka NULL
                    }

                    default:
                        InternalError::raise("illegal state: case not handled: AST atom generating IR");
                        return nullptr;
                }
            }

            std::optional<int64_t> Atom::evaluate_as_integer() const noexcept
            {
                switch (type)
                {
                    case Atom::Type::INTEGER:
                        return std::atoll(lexeme.c_str()); // sure that the lexeme is a valid number

                    case Atom::Type::CHARACTER:
                        return lexeme.c_str()[1];

                    default:
                        return {};
                }
            }

            util::String Atom::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "atom", "location": %s, "data_type": "%s", "lexeme": "%s"})",
                        location.to_string().c_str(),
                        AST::to_string(type),
                        lexeme.c_str());
            }
        }
    }
}
