//
// Created by void on 14/07/2021.
//

#ifndef ENI_EXCEPTION_H
#define ENI_EXCEPTION_H

#include <stdexcept>

namespace eni {

/**
 * The mother of all exceptions.
 */
class Exception : public std::runtime_error {
public:
    Exception();
    using std::runtime_error::runtime_error;
};

class StateException : public Exception {
public:
    using Exception::Exception;
};

class NotFoundException : public Exception {
public:
    using Exception::Exception;
};

class NotImplementedException : public Exception {
public:
    using Exception::Exception;
};

class NotSupportedException : public Exception {
public:
    using Exception::Exception;
};

class IllegalOperationException : public Exception {
public:
    using Exception::Exception;
};

class DuplicateKeyException : public Exception {
public:
    using Exception::Exception;
};

}// namespace eni

#endif//ENI_EXCEPTION_H
