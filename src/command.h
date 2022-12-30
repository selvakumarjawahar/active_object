#ifndef COMMAND_H
#define COMMAND_H

#include <future>

namespace active_object
{
    template<typename DerivedT>
    class AsyncCommandT
    {
        public:
           auto GetFuture() const 
            {
                return Derived().GetFuture();
            }
            void Execute()
            {
                Derived().Execute();
            }
        protected:
            ~AsyncCommandT() = default;
        private:
            DerivedT& Derived()
            {
                return static_cast<DerivedT&> (*this);
            }
            const DerivedT& Derived() const
            {
                return static_cast<const DerivedT&> (*this);
            }
    };

    template<typename T>
    class InferEmotions : AsyncCommandT<InferEmotions<T>>
    {
        std::future<T> GetFuture() const
        {
            return async_result.get_future();
        }
        void Execute()
        {

        }
        private:
            std::promise<T> async_result;
    };
}

#endif
