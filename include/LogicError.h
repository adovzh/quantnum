//
// Created by Alexander Dovzhikov on 8/4/18.
//

#ifndef QUANTNUM_LOGICERROR_H
#define QUANTNUM_LOGICERROR_H

#include <stdexcept>

namespace quantnum {

    class LogicError: public std::logic_error {
    public:
        explicit LogicError(const std::string& what_arg): logic_error(what_arg) {}
        explicit LogicError(const char* what_arg): logic_error(what_arg) {}
        LogicError(const LogicError& that) = default;
        LogicError& operator=(const LogicError& that) noexcept { logic_error::operator=(that); return *this; }
    };

} // namespace quantnum

#endif //QUANTNUM_QUANTNUMEXCEPTION_H
