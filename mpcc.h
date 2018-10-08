#ifndef MPCC_H
#define MPCC_H

#include "httpretriever.h"

#include <memory>
#include <string>
#include <unordered_map>

class MPCC
{
public:
    explicit MPCC(char* URL)
    {
        m_httpRetriever.reset(new HttpRetriever(URL));
    }

    MPCC() = delete;
    MPCC(const MPCC&) = delete;
    MPCC& operator=(const MPCC&) = delete;
    MPCC(const MPCC&&) = delete;
    MPCC& operator=(const MPCC&&) = delete;

    void get_voting_results();

private:
    void parse_html_contents();

    void print_votes();

private:
    std::unique_ptr<HttpRetriever> m_httpRetriever;
    std::unordered_map<std::string, int> m_votes;
};

#endif // MPCC_H
