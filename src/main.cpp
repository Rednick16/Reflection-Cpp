// Created by Red16 (I hare function pointers).

#include "Reflection.h"

using namespace Reflection;

bool IsMe()
{
    return true;
}

int myValue()
{
    return 50;
}

void init()
{
    printf("init\n");
}

void init_with_args(const char* text)
{
    printf("%s\n", text);
}

void setup_rf()
{
    // first initilize the functions

# if 1
    // using add macro
    AddFunction(init);
    AddFunction(myValue);
    AddFunction(IsMe);
    AddFunction(init_with_args);
#endif

# if 0
    // manully add them lol -> tip use AddFunction macro
    Manager::Add("init", reinterpret_cast<Pointer_t>(init));
    Manager::Add("myValue", reinterpret_cast<Pointer_t>(myValue));
    Manager::Add("IsMe", reinterpret_cast<Pointer_t>(IsMe));
#endif

# if 0
    Manager("init").Add(reinterpret_cast<Pointer_t>(init));
    Manager("myValue").Add(reinterpret_cast<Pointer_t>(myValue));
    Manager("IsMe").Add(reinterpret_cast<Pointer_t>(IsMe));
    Manager("init_with_args").Add(reinterpret_cast<Pointer_t>(init_with_args));
#endif
}

int main()
{
    setup_rf();

    // calling functions
    Manager::Invoke<void>("init");
    Manager::Invoke<void, const char*>("init_with_args", "I was called with some args hahahaha");

    Manager init_with_args("init_with_args");
    init_with_args.Invoke<void, const char*>("I was called with some args hahahaha");

    Manager mv("init_with_args");
    printf("myValue: %d", mv.Invoke<int>());

    Manager isMe("IsMe");
    const char* isMeChar = isMe.Invoke<bool>() ? "true" : "false";
    printf("IsMe: %s", isMeChar);

    return 0;
}