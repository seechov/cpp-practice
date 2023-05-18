#include "newhandlersupport.h"

template <class T>
void* NewHandlerSupport<T>::operator new(size_t size) {
    // temporarily switch in new_handler_

    std::new_handler default_handler = std::set_new_handler(new_handler_);

    // allocate

    void* memory;
    try {
        memory = ::operator new(size);
    } catch (const std::bad_alloc&) {
        // restore handler and propogate exception
        std::set_new_handler (default_handler);
        throw;
    }

    // restore handler
    std::set_new_handler (default_handler);

    return memory;
}

template <class T>
std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler h) {
    std::new_handler old = new_handler_;
    new_handler_ = h;
    return old;
}

template <class T>
std::new_handler NewHandlerSupport<T>::new_handler_;