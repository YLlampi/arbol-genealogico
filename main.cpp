#include <bits/stdc++.h>

using namespace std;

const string HIJO = "hijo";
const string HIJA = "hija";
const string MASCULINO = "masculino";
const string FEMENINO = "femenino";

class Person;

vector<Person *> personList;

class Person {
private:
    string firstName;
    string lastName;
    string sex;

    Person *father{nullptr};
    Person *mother{nullptr};

    Person *firstChild{nullptr};
    Person *lastChild{nullptr};
    Person *next{nullptr};
public:
    Person(string firstName, string lastName, string sex) : firstName(std::move(firstName)),
                                                            lastName(std::move(lastName)),
                                                            sex(std::move(sex)) {}

    string getFirstName() const {
        return this->firstName;
    }

    string getLastName() const {
        return this->lastName;
    }

    string getFullName() const {
        string fullname = this->firstName + " " + this->lastName;
        return fullname;
    }

    void setFather(Person *father) {
        Person::father = father;
    }

    void setMother(Person *mother) {
        Person::mother = mother;
    }

    void addChild(Person *child) {
        if (this->lastChild) {
            this->next = child;
            this->lastChild = child;
        } else {
            this->firstChild = child;
            this->lastChild = child;
        }
        if (this->sex == MASCULINO) {
            child->setFather(this);
        } else if (this->sex == FEMENINO) {
            child->setMother(this);
        }
    }

    void getBrothers() const {
        set<Person *> brothers;

        Person *father_aux = this->father;
        Person *aux = father_aux->firstChild;
        while (aux) {
            brothers.insert(aux);
            aux = father_aux->next;
        }

        Person *mother_aux = this->mother;
        Person *aux_2 = mother_aux->firstChild;
        while (aux_2) {
            brothers.insert(aux);
            aux_2 = mother_aux->next;
        }

        for (auto &brother: brothers) {
            cout << brother->getFullName() << endl;
        }
    }

};

Person *findPerson(string fullName) {
    for (auto &person: personList) {
        if (person->getFullName() == fullName)
            return person;
    }
    return nullptr;
}

void menu() {
    int option;
    do {
        cout << "=======MENU=======" << endl;
        cout << "1. Hermanos" << endl;
        cout << "2. Hermanas" << endl;
        cout << "3. Padre" << endl;
        cout << "4. Madre" << endl;
        cout << "5. Primos" << endl;
        cout << "6. Primas" << endl;
        cout << "7. Tios" << endl;
        cout << "8. Tias" << endl;
        cout << "0. Salir" << endl;

        cout << "\nOpcion: ";
        cin >> option;

        switch (option) {
            case 1: {
                string firstName, lastName;
                cout << "Nombre y Apellido";
                cin >> firstName >> lastName;
                Person *person = findPerson(firstName + " " + lastName);
                if(person) {
                    person->getBrothers();
                } else cout << "Persona no registrada" << endl;
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                break;
            }
            case 0: {
                cout << "Saliendo..!" << endl;
                break;
            }
            default: {
                cout << "Opcion incorrecta" << endl;
                break;
            }
        }
    } while (option);
}

int main() {
    string firstName, lastName, sex;

    while (cin >> firstName >> lastName >> sex, firstName != "0", lastName != "0", sex != "0") {
        personList.push_back(new Person(firstName, lastName, sex));
    }

    sort(personList.begin(), personList.end(), [](const auto &a, const auto &b) {
        return a->getFirstName() + a->getLastName() < b->getFirstName() + b->getLastName();
    });

    string a, b, c, d, e;
    while (cin >> a >> b >> c >> d >> e, a != "0", b != "0", c != "0", d != "0", e != "0") {
        string fullName_first = a + " " + b;
        string fullName_second = c + " " + d;

        Person *firstPerson = nullptr;
        Person *secondPerson = nullptr;

        bool band = true;
        for (auto &person: personList) {
            if (person->getFullName() == fullName_first) {
                firstPerson = person;
            } else band = false;
            if (person->getFullName() == fullName_second) {
                secondPerson = person;
            } else band = false;
        }

        if (e == HIJO or e == HIJA and band) {
            firstPerson->addChild(secondPerson);
        }
    }

    menu();
    return 0;
}