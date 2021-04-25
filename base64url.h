#pragma once

#include <string>

namespace base64url
{
    std::string encode(const char *data, const size_t dataSize)
    {
        static const char lut[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

        size_t resultLen = 4 * ((dataSize + 2) / 3);
        std::string result(resultLen, '\0');
        size_t i;
        char *p = const_cast<char *>(result.c_str());

        for (i = 0; i < dataSize - 2; i += 3)
        {
            *p++ = lut[(data[i] >> 2) & 0x3F];
            *p++ = lut[((data[i] & 0x3) << 4) | ((int)(data[i + 1] & 0xF0) >> 4)];
            *p++ = lut[((data[i + 1] & 0xF) << 2) | ((int)(data[i + 2] & 0xC0) >> 6)];
            *p++ = lut[data[i + 2] & 0x3F];
        }

        if (i < dataSize)
        {
            *p++ = lut[(data[i] >> 2) & 0x3F];
            if (i == (dataSize - 1))
            {
                *p++ = lut[((data[i] & 0x3) << 4)];
            }
            else
            {
                *p++ = lut[((data[i] & 0x3) << 4) | ((int)(data[i + 1] & 0xF0) >> 4)];
                *p++ = lut[((data[i + 1] & 0xF) << 2)];
            }
        }

        return result;
    }
}