#include <iostream>

using namespace std;

class ExecuteInterface {
    public:
        virtual ~ExecuteInterface() {}
        virtual void execute() = 0;
};

template <class TYPE>
class ExecuteAdapter: public ExecuteInterface {
    public:
        ExecuteAdapter(TYPE *o, void(TYPE:: *m) ()) {
            object = o;
            method = m;
        }
        ~ExecuteAdapter() {
            delete object;
        }
        void execute() {
            (object->*method)();
        }
    private:
        TYPE *object;
        void(TYPE:: *method)();
};

class Fea {
    public:
        ~Fea() {
            cout << "Fea::dtor" << endl;
        }
        void doThis() {
            cout << "Fea::doThis()" << endl;
        }
};

class Feye {
    public:
        ~Feye() {
            cout << "Feye::dtor" << endl;
        }
        void doThat() {
            cout << "Feye::doThat()" << endl;
        }
};

class Pheau {
    public:
        ~Pheau() {
            cout << "Pheau::dtor" << endl;
        }
        void doTheOther() {
            cout << "Pheau::doTheOther()" << endl;
        }
};

ExecuteInterface **initialize() {
    ExecuteInterface **array = new ExecuteInterface *[3];

    array[0] = new ExecuteAdapter <Fea> (new Fea(), &Fea::doThis);
    array[1] = new ExecuteAdapter <Feye> (new Feye(), &Feye::doThat);
    array[2] = new ExecuteAdapter <Pheau> (new Pheau(), &Pheau::doTheOther);

    return array;
}

int main() {
    ExecuteInterface **objects = initialize();
    for (int i =0; i < 3; i++) {
        objects[i]->execute();
    }

    for (int i = 0; i < 3; i++) {
        delete objects[i];
    }
    delete objects;

    return 0;
}
