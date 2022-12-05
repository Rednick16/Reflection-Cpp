#include <map>

namespace Reflection
{
    typedef void* (*Pointer_t)(void /* args ... */);
    typedef std::map<const char*, Pointer_t> Reflection_t;

    #define ToString(f) #f
    #define AddFunction(f) Manager::Add(ToString(f), reinterpret_cast<Pointer_t>(f))

    class Manager
    {
    private:
        const char* fname;
        static Reflection_t functions;
        
    public:
        Manager();
        Manager(const char* fname);
        Manager(const char* fname, Pointer_t func);
        
        ~Manager();
        
        Pointer_t Get();
        static Pointer_t Get(const char* fname);
        
        void Add(Pointer_t func);
        static void Add(const char* fname, Pointer_t func);
        
        template<typename T, typename ...ARGS>
        T Invoke(ARGS ...args){
            if(!this->Get()) return T();
            return reinterpret_cast<T (*)(ARGS...)>(this->Get())(args...);
        }
        
        template<typename T, typename ...ARGS>
        static T Invoke(const char* fname, ARGS ...args)
        {
            return reinterpret_cast<T (*)(ARGS...)>(Get(fname))(args...);
        }
    };
}
