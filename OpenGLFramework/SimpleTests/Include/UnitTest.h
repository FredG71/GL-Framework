#pragma once
#include <string>
#include <vector>
#include "Platform.h"

class UnitTest
{
public:
    explicit UnitTest(char* TestName)
        : szTestName(TestName)
    {}

    virtual ~UnitTest() {}
    virtual void ExecTests()
    {
        PlatformUtils::Logging::Printf("-------------------BEGIN unit tests for: %s -------------------\n", GetTestName());
        PlatformUtils::Logging::Printf("-------------------END unit tests for: %s -------------------\n", GetTestName());
    }
    virtual char* GetTestName()
    {
        return szTestName;
    }
    virtual bool IS_NULL(void* Ptr, char* Meta)
    {
        nInvocationCount += 1;
        if (Ptr == nullptr)
        {
            nErrorCount += 1;
            PlatformUtils::Logging::LogWarning("%s %s\n", Meta, "PTR IS NULL");
        }
        return Ptr == nullptr;
    }
    virtual bool IS_STRING_SET(std::wstring& A, const std::wstring& B, char* Meta)
    {
        nInvocationCount += 1;
        if (A.compare(B) == 1)
        {
            nErrorCount += 1;
            PlatformUtils::Logging::LogWarning("ERROR: %s || NOT TRUE\n", Meta);
        }
        return !A.compare(B);
    }
    virtual bool IS_STRING_SET(std::string& A, const std::string& B, char* Meta)
    {
        nInvocationCount += 1;
        if (A.compare(B) == 1)
        {
            nErrorCount += 1;
            PlatformUtils::Logging::LogWarning("ERROR: %s || NOT TRUE\n", Meta);
        }
        return !A.compare(B);
    }
    virtual bool IS_WIDE_RAW_STRING_SET(wchar_t* A, const wchar_t* B, char* Meta)
    {
        nInvocationCount += 1;
        if (wcscmp(A, B) == 1)
        {
            nErrorCount += 1;
            PlatformUtils::Logging::LogWarning("ERROR: %s || NOT TRUE\n", Meta);
        }
        return !wcscmp(A, B);
    }
    virtual bool IS_WIDE_RAW_STRING_SET(const wchar_t* A, const wchar_t* B, char* Meta)
    {
        nInvocationCount += 1;
        if (wcscmp(A, B) == 1)
        {
            nErrorCount += 1;
            PlatformUtils::Logging::LogWarning("ERROR: %s || NOT TRUE\n", Meta);
        }
        return !wcscmp(A, B);
    }
    virtual bool IS_RAW_STRING_SET(char* A, const char* B, char* Meta)
    {
        nInvocationCount += 1;
        if (strcmp(A, B) == 1)
        {
            nErrorCount += 1;
            PlatformUtils::Logging::LogWarning("ERROR: %s || NOT TRUE\n", Meta);
        }
        return !strcmp(A, B);
    }
    virtual bool IS_RAW_STRING_SET(const char* A, const char* B, char* Meta)
    {
        nInvocationCount += 1;
        if (strcmp(A, B) == 1)
        {
            nErrorCount += 1;
            PlatformUtils::Logging::LogWarning("ERROR: %s || NOT TRUE\n", Meta);
        }
        return !strcmp(A, B);
    }
    virtual void ASSUME_ASSERT(bool bInvariant, char* Meta)
    {
        nInvocationCount += 1;
        if (!bInvariant)
        {
            nErrorCount += 1;
            PlatformUtils::Logging::LogWarning("%s %s\n", Meta, "IS FALSE");
        }
        assert(bInvariant);
    }
    virtual void ASSUME(bool bInvariant, char* Meta)
    {
        nInvocationCount += 1;
        if (!bInvariant)
        {
            nErrorCount += 1;
            PlatformUtils::Logging::LogWarning("%s %s\n", Meta, "IS FALSE");
        }
    }
    virtual void Output();
protected:
    char* szTestName;
    int nInvocationCount;
    int nErrorCount;
};

#define DECLARE_SIMPLE_UNIT_TESTS( ClassName )\
class ClassName : public UnitTest\
{\
public:\
    explicit ClassName(char* TestName)\
        : UnitTest(TestName){}\
    virtual void ExecTests() override;\
};

#define INIT_AND_RUN_DECLARED_TESTS( ClassName, TestName )\
        ClassName __ClassName##TestName = ClassName((char*)#TestName);\
        __ClassName##TestName.ExecTests();

#ifdef __cplusplus
#define Breakpoint() __debugbreak();
#define assertf( Condition, Message )\
if (!(Condition)) {\
    std::cerr << " Assertion failed " #Condition " failed in " << __FILE__ << " line " << __LINE__ << ": " << Message << std::endl;\
    Breakpoint()}
#endif
#define IsAligned( Data, Alignment ) assertf( !(((int32_t)Data % Alignment)), "Data is not aligned on " << Alignment );
static_assert(sizeof(std::uint8_t)  == 1, "Error uint8_t test failed");
static_assert(sizeof(std::uint16_t) == 2, "Error uint16_t test failed");
static_assert(sizeof(std::uint32_t) == 4, "Error uint32_t test failed");
static_assert(sizeof(std::uint64_t) == 8, "Error uint64_t test failed");
static_assert(sizeof(std::int8_t)   == 1, "Error int8_t test failed");
static_assert(sizeof(std::int16_t)  == 2, "Error int16_t test failed");
static_assert(sizeof(std::int32_t)  == 4, "Error int32_t test failed");
static_assert(sizeof(std::int64_t)  == 8, "Error int64_t test failed");
