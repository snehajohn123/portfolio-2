#include <iostream>
#include <ctime>
using namespace std;


class Machine
{
  class State *current;
  public:
    Machine();
    void setCurrent(State *s)
    {
        current = s;
    }
    void sensing();
    void idle();
    void processing();
};

class State
{
  public:
    virtual void sensing(Machine *m)
    {
        cout << "   already SENSING\n";
    }
    virtual void idle(Machine *m)
    {
        cout << "   already IDLE\n";
    }
    virtual void processing(Machine *m)
    {
        cout << "PROCESSING\n";
    }
};

void Machine::sensing()
{
  current->sensing(this);
}

void Machine::idle()
{
  current->idle(this);
}

void Machine::processing()
{
  current->processing(this);
}


class SENSING: public State
{
  public:
    SENSING()
    {
        cout << "   SENSING-ctor ";
    };
    ~SENSING()
    {
        cout << "   dtor-SENSING\n";
    };
    void idle(Machine *m);
};

class PROCESSING: public State
{
  public:
    PROCESSING()
    {
        cout << "   PROCESSING-ctor ";
    };
    ~PROCESSING()
    {
        cout << "   dtor-PROCESSING\n";
    };
    void idle(Machine *m);
};

class IDLE: public State
{
  public:
    IDLE()
    {
        cout << "   IDLE-ctor ";
    };
    ~IDLE()
    {
        cout << "   dtor-IDLE\n";
    };
    void sensing(Machine *m)
    {
        cout << "   going from IDLE to SENSING";
        m->setCurrent(new SENSING());
        delete this;
    }

     void processing(Machine *m)
    {
        cout << "   going from IDLE to processing";
        m->setCurrent(new PROCESSING());
        delete this;
    }
};

void SENSING::idle(Machine *m)
{
  cout << "   going from SENSING to IDLE";
  m->setCurrent(new IDLE());
  delete this;
}


void PROCESSING::idle(Machine *m)
{
  cout << "   going from PROCESSING to IDLE";
  m->setCurrent(new IDLE());
  delete this;
}

Machine::Machine()
{
  current = new IDLE();
  cout << '\n';
}




int main()
{
  void(Machine:: *ptrs[])() =
  {
    Machine::idle, Machine::sensing, Machine::processing
  };
  Machine fsm;
  int num;
while(1)
  {
    cout << "Enter 1 to start sensing / 2 for processing data / 0 to go back ideal: ";
    cin >> num;
    (fsm.*ptrs[num])();

  }
}
