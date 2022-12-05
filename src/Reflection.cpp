#include "Reflection.h"

namespace Reflection
{
    // maybe there is a better way to do this
    Reflection_t Manager::functions = Reflection_t();

    Manager::Manager()
    {
        this->fname = nullptr;
    }

    Manager::~Manager()
    {
        this->fname = nullptr;
    }

    Manager::Manager(const char* fname)
    {
        Manager();
        this->fname = fname;
    }

    Manager::Manager(const char* fname, Pointer_t func){
        (Manager(fname));
        this->Add(func);
    }

    Pointer_t Manager::Get()
    {
        return functions.at(this->fname);
    }

    Pointer_t Manager::Get(const char* fname)
    {
        return functions.at(fname);
    }

    void Manager::Add(Pointer_t func)
    {
        if(this->fname && func)
            functions.insert_or_assign(this->fname, func);
    }

    void Manager::Add(const char* fname, Pointer_t func)
    {
        functions.insert_or_assign(fname, func);
    }
}
