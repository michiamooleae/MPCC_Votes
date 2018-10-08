#include "mpcc.h"

#include <iostream>
#include <iterator>
#include <stack>

void MPCC::parse_html_contents()
{
    QStringList list = m_httpRetriever->getHtmlContents();

    for (auto it = list.cbegin(); it != list.cend(); ++it)
    {
        if(it->contains("<tr id=", Qt::CaseInsensitive))
        {
            QString text;
            text = *(it+2);
            text = text.remove(QString::fromStdString("</a></strong>"), Qt::CaseInsensitive);

            std::stack<char> ppff;

            auto ssssss = text.toStdString();
            for (auto itt = ssssss.rbegin(); itt != ssssss.rend(); ++itt)
            {
                if (*itt == '>')
                {
                    break;
                }

                ppff.push(*itt);
            }

            std::string username;

            while(!ppff.empty())
            {
                username += ppff.top();
                ppff.pop();
            }

            while (!it->contains("post_text"))
            {
                std::advance(it,1);
            }

            std::advance(it,1);

            text = *it;
            text = text.remove(QString::fromStdString("\t\t\t\t"), Qt::CaseInsensitive);
            text = text.remove(QRegExp("[^0-9]", Qt::CaseInsensitive));

            if (m_votes.find(username) == m_votes.end() && text.length() == 1)
            {
                m_votes[username] = text.toInt();
            }
        }
    }
}

void MPCC::print_votes()
{
    unsigned int one = 0;
    unsigned int two = 0;

    for (const auto& vote : m_votes)
    {
        std::cout << vote.first << ": " << vote.second << "\n";

        if (vote.second == 1)
        {
            one++;
        }
        else
        {
            two++;
        }
    }

    std::cout << "---------------\n" << one << " " << two << std::endl;
}

void MPCC::get_voting_results()
{ 
    parse_html_contents();
    print_votes();
}
