#include <iostream>
#include <vector>
using namespace std;

class Subject;
class Observer;


class Subject
{
public:
    Subject() {}
    void attach(Observer* ob);
    void set_value(const int value);
    void notify();
private:
    int m_value;
    vector<Observer*> m_views;
};


inline void
Subject::attach(Observer* ob)
{
    m_views.push_back(ob);
}

inline void
Subject::set_value(const int value)
{
    m_value = value;
    notify();
}

inline void
Subject::notify()
{
    for (int i = 0; i < m_views.size(); ++i)
    {
        m_views[i]->update(this, m_value);
    }
}


class Observer
{
    Observer() {}
    ~Observer() {}
    virtual void update(Subject* sub, const int m_value) = 0;
};

int main(int argc, char const* argv[])
{

    return 0;
}

