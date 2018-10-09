#ifndef UNCROPPEDIMAGESFINDER_H
#define UNCROPPEDIMAGESFINDER_H

#include "httpretriever.h"

#include <iostream>
#include <memory>

class UncroppedImagesFinder
{
public:
    explicit UncroppedImagesFinder(const std::string& country)
        : m_country(country),
          m_countryListURL("https://en.numista.com/catalogue/pays.php")
    {
        m_httpRetriever.reset(new HttpRetriever(m_countryListURL));
        m_countryListContent = m_httpRetriever->getHtmlContents();
    }

    UncroppedImagesFinder() = delete;
    UncroppedImagesFinder(const UncroppedImagesFinder&) = delete;
    UncroppedImagesFinder& operator=(const UncroppedImagesFinder&) = delete;
    UncroppedImagesFinder(const UncroppedImagesFinder&&) = delete;
    UncroppedImagesFinder& operator=(const UncroppedImagesFinder&&) = delete;

    void print()
    {
        std::string res = "";

        for (const auto& str : m_countryListContent)
        {
            if (str.toStdString().find(m_country) != std::string::npos)
            {
                res = str.toStdString();
                size_t last = res.find_last_of("\"");
                size_t first = res.find_last_of("\"", last-1);

                res = res.substr(first+1, last-first-1);
                break;
            }
        }

        std::cout << res << std::endl;

        m_countryListContent.clear();

        //m_countryURL = (char*) res.c_str();

        std::string temp {"https://en.numista.com/catalogue/"};

        temp.append(res);

        m_countryURL = temp.c_str();

        std::cout << m_countryURL << std::endl;
    }

private:
    std::string m_country;
    char* m_countryListURL;
    const char* m_countryURL;
    std::unique_ptr<HttpRetriever> m_httpRetriever;
    QStringList m_countryListContent;
};

#endif // UNCROPPEDIMAGESFINDER_H
