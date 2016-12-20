// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../HttpURL/CHttpURL.h"
#include "../HttpURL/CUrlParsingError.h"
#include "../HttpURL/Errors.h"

template <typename Ex, typename Fn>
void ExpectException(Fn && fn, std::string const& expectedDescription)
{
    BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
        return e.what() == expectedDescription;
    });
}

void VerifyUrl(CHttpUrl url,
    std::string const& urlStr,
    Protocol protocol,
    std::string const& domain,
    std::string const& document,
    unsigned short port)
{
    BOOST_CHECK(url.GetProtocol() == protocol);
    BOOST_CHECK_EQUAL(url.GetDomain(), domain);
    BOOST_CHECK_EQUAL(url.GetDocument(), document);
    BOOST_CHECK_EQUAL(url.GetPort(), port);
    BOOST_CHECK_EQUAL(url.GetURL(), urlStr);
}


BOOST_AUTO_TEST_SUITE(CHttpURL)

    BOOST_AUTO_TEST_SUITE(ParseUrl)
        BOOST_AUTO_TEST_CASE(can_parse_url)
        {
            {
                std::string url = "https://mysite.com/page.php?id=100";
                VerifyUrl(CHttpUrl(url), url, Protocol::HTTPS, "mysite.com", "/page.php?id=100", 443);
            }

            {
                VerifyUrl(CHttpUrl("vk.com", "/id132524"), "http://vk.com/id132524", Protocol::HTTP, "vk.com", "/id132524", 80);
            }

            {
                VerifyUrl(CHttpUrl("vk.com", "/id132524", Protocol::HTTPS, 2425), "https://vk.com:2425/id132524", Protocol::HTTPS, "vk.com", "/id132524", 2425);
            }
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(ParseProtocol)
        BOOST_AUTO_TEST_CASE(can_throw_an_exception)
        {
            ExpectException<CUrlParsingError>([&] {
                CHttpUrl url("mysite.com");
            }, PROTOCOL_PARSING_ERROR);

            ExpectException<CUrlParsingError>([&] {
                CHttpUrl url("htt://mysite.com");
            }, INVALID_PROTOCOL);
        }

        BOOST_AUTO_TEST_CASE(can_parse_protocol)
        {
            BOOST_CHECK(CHttpUrl("https://mysite.com/").GetProtocol() == Protocol::HTTPS);
            BOOST_CHECK(CHttpUrl("http://mysite.com/").GetProtocol() == Protocol::HTTP);
        }
    BOOST_AUTO_TEST_SUITE_END()


    BOOST_AUTO_TEST_SUITE(ParseDomain)
        BOOST_AUTO_TEST_CASE(can_throw_an_exception)
        {
            ExpectException<CUrlParsingError>([&] {
                CHttpUrl url("https://mys ite.com/");
            }, INVALID_DOMAIN);

            ExpectException<CUrlParsingError>([&] {
                CHttpUrl url("https://");
            }, DOMAIN_PARSING_ERROR);

            ExpectException<CUrlParsingError>([&] {
                CHttpUrl url("https://mysi'te.com");
            }, INVALID_DOMAIN);
        }

        BOOST_AUTO_TEST_CASE(can_parse_domain)
        {
            BOOST_CHECK(CHttpUrl("https://mysite.com").GetDomain() == "mysite.com");
            BOOST_CHECK(CHttpUrl("https://localhost:8221").GetDomain() == "localhost");
            BOOST_CHECK(CHttpUrl("http://mysite.ru/").GetDomain() == "mysite.ru");
            BOOST_CHECK(CHttpUrl("http://mysite.ru:266/index.html").GetDomain() == "mysite.ru");
        }
    BOOST_AUTO_TEST_SUITE_END()


    BOOST_AUTO_TEST_SUITE(ParsePort)
        BOOST_AUTO_TEST_CASE(can_throw_an_exception)
        {
            ExpectException<CUrlParsingError>([&] {
                CHttpUrl url("https://mysite.com:");
            }, PORT_PARSING_ERROR);

            ExpectException<CUrlParsingError>([&] {
                CHttpUrl url("https://mysite.com:/");
            }, PORT_PARSING_ERROR);

            ExpectException<CUrlParsingError>([&] {
                CHttpUrl url("https://mysite.com:23h41/");
            }, BAD_LEXICAL_CAST);

            ExpectException<CUrlParsingError>([&] {
                CHttpUrl url("https://mysite.ru:232353241/");
            }, INVALID_PORT);
			ExpectException<CUrlParsingError>([&] {
				CHttpUrl url("https://mysite.ru:-1/");
			}, INVALID_PORT);
        }

        BOOST_AUTO_TEST_CASE(can_parse_port)
        {
            BOOST_CHECK(CHttpUrl("https://mysite.com:3424").GetPort() == 3424);
            BOOST_CHECK(CHttpUrl("https://mysite.com").GetPort() == 443);
            BOOST_CHECK(CHttpUrl("http://vk.com").GetPort() == 80);
        }
    BOOST_AUTO_TEST_SUITE_END()


    BOOST_AUTO_TEST_SUITE(ParseDocument)
        BOOST_AUTO_TEST_CASE(can_throw_an_exception)
        {
            ExpectException<CUrlParsingError>([&] {
                CHttpUrl url("https://mysite.com/index. php");
            }, INVALID_DOCUMENT);
        }

        BOOST_AUTO_TEST_CASE(can_parse_document)
        {
            BOOST_CHECK(CHttpUrl("https://mysite.com").GetDocument() == "/");
            BOOST_CHECK(CHttpUrl("https://mysite.com:3424").GetDocument() == "/");
            BOOST_CHECK(CHttpUrl("http://alenacpp.blogspot.ru/2005/09/const-2.html").GetDocument() == "/2005/09/const-2.html");
        }
    BOOST_AUTO_TEST_SUITE_END()


    BOOST_AUTO_TEST_SUITE(GetUrl)
        BOOST_AUTO_TEST_CASE(can_return_url)
        {
            BOOST_CHECK(CHttpUrl("https://mysite.com").GetURL() == "https://mysite.com/");
            BOOST_CHECK(CHttpUrl("http://alenacpp.blogspot.ru:3256/2005/09/const-2.html").GetURL() == "http://alenacpp.blogspot.ru:3256/2005/09/const-2.html");
        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()