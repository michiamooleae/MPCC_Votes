#ifndef MPCC_H
#define MPCC_H

#include <unordered_map>
#include <string>

#include <QString>
#include <QStringList>

class MPCC
{
public:
    MPCC(const MPCC&) = delete;

    explicit MPCC(char* URL) : m_URL(URL)
    {
    }

    void get_voting_results();

private:
    MPCC();

    QStringList get_html_contents();

    void parse_html_contents(const QStringList& list);

    void print_votes();

private:
    char* m_URL;
    std::unordered_map<std::string, int> m_votes;
};

#endif // MPCC_H
