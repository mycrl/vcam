#pragma once

class WinHandle
{
    HANDLE handle = INVALID_HANDLE_VALUE;

    inline void Clear()
    {
        if (handle && handle != INVALID_HANDLE_VALUE)
            CloseHandle(handle);
    }

public:
    inline WinHandle()
    {
    }
    inline WinHandle(HANDLE handle_) : handle(handle_)
    {
    }
    inline ~WinHandle()
    {
        Clear();
    }

    inline operator HANDLE() const
    {
        return handle;
    }

    inline WinHandle& operator=(HANDLE handle_)
    {
        if (handle_ != handle)
        {
            Clear();
            handle = handle_;
        }

        return *this;
    }

    inline HANDLE* operator&()
    {
        return &handle;
    }

    inline bool Valid() const
    {
        return handle && handle != INVALID_HANDLE_VALUE;
    }
};
