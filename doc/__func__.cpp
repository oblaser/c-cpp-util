
#include <stdio.h>

#ifdef _MSC_VER

#define LOG_TEST_FUNC()                         \
    printf("__func__:     %s\n", __func__);     \
    printf("__FUNCTION__: %s\n", __FUNCTION__); \
    printf("__FUNCSIG__:  %s\n\n", __FUNCSIG__)

#else

#define LOG_TEST_FUNC()                                \
    printf("__func__:            %s\n", __func__);     \
    printf("__FUNCTION__:        %s\n", __FUNCTION__); \
    printf("__PRETTY_FUNCTION__: %s\n\n", __PRETTY_FUNCTION__)

#endif



namespace namsp {

class Class
{
public:
    void log() { LOG_TEST_FUNC(); }
};

void log() { LOG_TEST_FUNC(); }

} // namespace namsp

class Other
{
public:
    void log() { LOG_TEST_FUNC(); }
};



int main()
{
    namsp::log();
    namsp::Class().log();
    Other().log();

    return 0;
}



/* GCC

__func__:            log
__FUNCTION__:        log
__PRETTY_FUNCTION__: void namsp::log()

__func__:            log
__FUNCTION__:        log
__PRETTY_FUNCTION__: void namsp::Class::log()

__func__:            log
__FUNCTION__:        log
__PRETTY_FUNCTION__: void Other::log()

*/



/* MSVC

__func__:     log
__FUNCTION__: namsp::log
__FUNCSIG__:  void __cdecl namsp::log(void)

__func__:     log
__FUNCTION__: namsp::Class::log
__FUNCSIG__:  void __cdecl namsp::Class::log(void)

__func__:     log
__FUNCTION__: Other::log
__FUNCSIG__:  void __cdecl Other::log(void)

*/
