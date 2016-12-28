#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

using namespace std;

void PrintInfo(CHttpUrl const& url)
{
    std::cout << "Protocol " << url.ToStringProtocol() << "\n"
			  << "Domain " << url.GetDomain() << "\n"
		      << "Port " << url.GetPort() << "\n"
			  << "Document " << url.GetDocument() << std::endl;
}
int main()
{
    string url;
    while (getline(cin, url))
    {
        try
        {
            CHttpUrl httpUrl(url);
            PrintInfo(url);
        }
        catch (CUrlParsingError const& error)
        {
            cout << error.what() << endl;
        }
    }
    return 0;
}
