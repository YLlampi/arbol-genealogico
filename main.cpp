#include <bits/stdc++.h>
#include <fstream>

using namespace std;

const string HIJO = "hijo";
const string HIJA = "hija";
const string MASCULINO = "masculino";
const string FEMENINO = "femenino";

class Person;

vector<Person *> personList;
set<Person *> listUncles;

class Person {
private:
    string firstName;
    string lastName;
    string sex;

    Person *father{nullptr};
    Person *mother{nullptr};

    Person *firstChild{nullptr};
    Person *lastChild{nullptr};
    Person *nextChild{nullptr};
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

    const string &getSex() const {
        return this->sex;
    }

    Person *getFather() const {
        return father;
    }

    Person *getMother() const {
        return mother;
    }

    Person *getFirstChild() const {
        return this->firstChild;
    }

    Person *getLastChild() const {
        return this->lastChild;
    }

    Person *getNextChild() const {
        return this->nextChild;
    }


    void addChild(Person *child) {
        if (this->lastChild) {
            this->lastChild->nextChild = child;
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

    void getBrothers(string genero) const {
        set<Person *> brothers;

        Person *aux = this->father->firstChild;
        while (aux) {
            if (aux->getSex() == genero and aux != this) {
                brothers.insert(aux);
            }
            aux = aux->nextChild;
        }

        Person *aux_2 = this->mother->firstChild;
        while (aux_2) {
            if (aux_2->getSex() == genero and aux_2 != this) {
                brothers.insert(aux_2);
            }
            aux_2 = aux_2->nextChild;
        }
        for (auto &brother: brothers) {
            cout << brother->getFullName() << endl;
        }
    }

    void getCousins(string genero) const {
        Person *grandFather_mother = this->mother->getFather();
        Person *aux1 = grandFather_mother->getFirstChild();

        Person *grandMother_mother = this->mother->getMother();
        Person *aux2 = grandMother_mother->getFirstChild();

        set<Person *> listP;
        while (aux1) {
            Person *child = aux1->getFirstChild();
            while (child) {
                if (child->getSex() == genero and child != this and child->getFather() != this->father and
                    child->getMother() != this->mother) {

                    listP.insert(child);
                }
                child = child->nextChild;
            }
            aux1 = aux1->nextChild;
        }

        while (aux2) {
            Person *child = aux2->getFirstChild();
            while (child) {
                if (child->getSex() == genero and child != this and child->getFather() != this->father and
                    child->getMother() != this->mother) {

                    listP.insert(child);
                }
                child = child->nextChild;
            }
            aux2 = aux2->nextChild;
        }
        /*
        Person *grandFather_father = this->father->getFather();
        Person *aux3 = grandFather_father->getFirstChild();

        Person *grandMother_father = this->father->getMother();
        Person *aux4 = grandMother_father->getFirstChild();

        while (aux3) {
            Person *child = aux3->getFirstChild();
            while (child) {
                if (child->getSex() == genero and child != this and child->getFather() != this->father and
                    child->getMother() != this->mother){
                    listP.insert(child);
                }
                child = child->nextChild;
            }
            aux3 = aux3->nextChild;
        }

        while (aux4) {
            Person *child = aux4->getFirstChild();
            while (child) {
                if (child->getSex() == genero and child != this and child->getFather() != this->father and
                    child->getMother() != this->mother){
                    listP.insert(child);
                }
                child = child->nextChild;
            }
            aux4 = aux4->nextChild;
        }
         */

        for (auto &i: listP) {
            cout << i->getFullName() << endl;
        }
    }

    void getUncles(string genero) const {
        Person *grandFather_mother = this->mother->getFather();
        Person *aux1 = grandFather_mother->getFirstChild();

        Person *grandMother_mother = this->mother->getMother();
        Person *aux2 = grandMother_mother->getFirstChild();

        set<Person*> listP;
        while (aux1) {
            if (aux1->getSex() == genero and aux1 != this->mother and aux1 != this->father){
                listP.insert(aux1);
            }
            listUncles.insert(aux1);
            aux1 = aux1->nextChild;
        }

        while (aux2) {
            if (aux2->getSex() == genero and aux2 != this->mother and aux2 != this->father){
                listP.insert(aux2);
            }
            listUncles.insert(aux2);
            aux2 = aux2->nextChild;
        }

        /*
        Person *grandFather_father = this->father->getFather();
        Person *aux3 = grandFather_father->getFirstChild();

        Person *grandMother_father = this->father->getMother();
        Person *aux4 = grandMother_father->getFirstChild();

        while (aux3) {
            if (aux3->getSex() == genero and aux3 != this->mother and aux3 != this->father)
                listUncles.insert(aux3);
            aux3 = aux3->nextChild;
        }

        while (aux4) {
            if (aux4->getSex() == genero and aux4 != this->mother and aux4 != this->father)
                listUncles.insert(aux4);
            aux4 = aux4->nextChild;
        }
         */

        for (auto &i: listP) {
            cout << i->getFullName() << endl;
        }
    }

    void unclesInLaw() {
        Person *grandFather_mother = this->mother->getFather();
        Person *aux1 = grandFather_mother->getFirstChild();

        Person *grandMother_mother = this->mother->getMother();
        Person *aux2 = grandMother_mother->getFirstChild();

        set<Person *> listP;
        while (aux1) {
            Person *child = aux1->getFirstChild();
            while (child) {
                auto it = listUncles.find(child->getFather());
                if (it == listUncles.end() and child->getFather() != this->father) {
                    listP.insert(child->getFather());
                }
                auto it2 = listUncles.find(child->getMother());
                if (it2 == listUncles.end() and child->getMother() != this->mother) {
                    listP.insert(child->getMother());
                }
                child = child->nextChild;
            }
            aux1 = aux1->nextChild;
        }

        while (aux2) {
            Person *child = aux2->getFirstChild();
            while (child) {
                auto it = listUncles.find(child->getFather());
                if (it == listUncles.end() and child->getFather() != this->father) {
                    listP.insert(child->getFather());
                }
                auto it2 = listUncles.find(child->getMother());
                if (it2 == listUncles.end() and child->getMother() != this->mother) {
                    listP.insert(child->getMother());
                }
                child = child->nextChild;
            }
            aux2 = aux2->nextChild;
        }

        for (auto &i: listP) {
            cout << i->getFullName() << endl;
        }

    }

    void getChilds() {
        Person *aux = this->firstChild;
        while (aux) {
            cout << aux->getFullName() << endl;
            aux = aux->nextChild;
        }
    }

};

void printData() {
    for (auto &person: personList) {
        cout << person->getFullName() << endl;
    }
}


Person *findPerson(string fullName) {
    // cout << fullName << endl;
    // cout << "-----------------" << endl;
    for (auto &person: personList) {
        // cout << person->getFullName() << "  ===  " << fullName << endl;
        if (person->getFullName() == fullName)
            return person;
    }
    return nullptr;
}

void menu() {
    int option;
    do {
        cout << "===========MENU===========" << endl;
        cout << "1. Hermanos" << endl;
        cout << "2. Hermanas" << endl;
        cout << "3. Padre" << endl;
        cout << "4. Madre" << endl;
        cout << "5. Primos" << endl;
        cout << "6. Primas" << endl;
        cout << "7. Tios" << endl;
        cout << "8. Tias" << endl;
        cout << "9. Print Data" << endl;
        cout << "10. Hij@s" << endl;
        cout << "11. Tios(as) Politicos" << endl;
        cout << "0. Salir" << endl;

        cout << "\nOpcion: ";
        cin >> option;

        switch (option) {
            case 1: {
                string firstName, lastName;
                cout << "Nombre y Apellido: ";
                cin >> firstName >> lastName;
                Person *person = findPerson(firstName + " " + lastName);
                if (person) {
                    cout << "*****************************************************" << endl;
                    person->getBrothers(MASCULINO);
                    cout << "*****************************************************" << endl;

                } else cout << "Persona no registrada" << endl;
                break;
            }
            case 2: {
                string firstName, lastName;
                cout << "Nombre y Apellido: ";
                cin >> firstName >> lastName;
                Person *person = findPerson(firstName + " " + lastName);
                if (person) {
                    cout << "*****************************************************" << endl;

                    person->getBrothers(FEMENINO);
                    cout << "*****************************************************" << endl;

                } else cout << "Persona no registrada" << endl;
                break;
            }
            case 3: {
                string firstName, lastName;
                cout << "Nombre y Apellido: ";
                cin >> firstName >> lastName;
                Person *person = findPerson(firstName + " " + lastName);
                if (person) {
                    cout << "*****************************************************" << endl;

                    cout << person->getFather()->getFullName() << endl;
                    cout << "*****************************************************" << endl;

                } else cout << "Persona no registrada" << endl;
                break;
            }
            case 4: {
                string firstName, lastName;
                cout << "Nombre y Apellido: ";
                cin >> firstName >> lastName;
                Person *person = findPerson(firstName + " " + lastName);
                if (person) {
                    cout << "*****************************************************" << endl;

                    cout << person->getMother()->getFullName() << endl;
                    cout << "*****************************************************" << endl;

                } else cout << "Persona no registrada" << endl;
                break;
            }
            case 5: {
                string firstName, lastName;
                cout << "Nombre y Apellido: ";
                cin >> firstName >> lastName;
                Person *person = findPerson(firstName + " " + lastName);
                if (person) {
                    cout << "*****************************************************" << endl;

                    person->getCousins(MASCULINO);
                    cout << "*****************************************************" << endl;

                } else cout << "Persona no registrada" << endl;
                break;
            }
            case 6: {
                string firstName, lastName;
                cout << "Nombre y Apellido: ";
                cin >> firstName >> lastName;
                Person *person = findPerson(firstName + " " + lastName);
                if (person) {
                    cout << "*****************************************************" << endl;

                    person->getCousins(FEMENINO);
                    cout << "*****************************************************" << endl;

                } else cout << "Persona no registrada" << endl;
                break;
            }
            case 7: {
                string firstName, lastName;
                cout << "Nombre y Apellido: ";
                cin >> firstName >> lastName;
                Person *person = findPerson(firstName + " " + lastName);
                if (person) {
                    cout << "*****************************************************" << endl;

                    person->getUncles(MASCULINO);
                    cout << "*****************************************************" << endl;

                } else cout << "Persona no registrada" << endl;
                break;
            }
            case 8: {
                string firstName, lastName;
                cout << "Nombre y Apellido: ";
                cin >> firstName >> lastName;
                Person *person = findPerson(firstName + " " + lastName);
                if (person) {
                    cout << "*****************************************************" << endl;

                    person->getUncles(FEMENINO);
                    cout << "*****************************************************" << endl;

                } else cout << "Persona no registrada" << endl;
                break;
            }
            case 9: {
                printData();
                break;
            };
            case 10: {
                string firstName, lastName;
                cout << "Nombre y Apellido: ";
                cin >> firstName >> lastName;
                Person *person = findPerson(firstName + " " + lastName);
                if (person) {
                    cout << "*****************************************************" << endl;

                    person->getChilds();
                    cout << "*****************************************************" << endl;

                } else cout << "Persona no registrada" << endl;
                break;
            };
            case 11: {
                string firstName, lastName;
                cout << "Nombre y Apellido: ";
                cin >> firstName >> lastName;
                Person *person = findPerson(firstName + " " + lastName);
                if (person) {
                    cout << "*****************************************************" << endl;

                    person->unclesInLaw();
                    cout << "*****************************************************" << endl;

                } else cout << "Persona no registrada" << endl;
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

void inputData(ifstream &file) {
    if (file.is_open()) {  // Verifica si el archivo se abrió correctamente
        std::string firstName, lastName, sex;
        while (file >> firstName >> lastName >> sex, firstName != "0", lastName != "0", sex != "0") {
            personList.push_back(new Person(firstName, lastName, sex));
        }

        //sort(personList.begin(), personList.end(), [](const auto &a, const auto &b) {
        //    return a->getFirstName() + a->getLastName() < b->getFirstName() + b->getLastName();
        //});

        std::string a, b, c, d, e;
        while (file >> a >> b >> c >> d >> e, a != "0", b != "0", c != "0", d != "0", e != "0") {
            string fullName_first = a + " " + b;
            string fullName_second = c + " " + d;

            Person *firstPerson = nullptr;
            Person *secondPerson = nullptr;

            bool band = false;
            for (auto &person: personList) {
                if (person->getFullName() == fullName_first) {
                    firstPerson = person;
                    band = true;
                }
                if (person->getFullName() == fullName_second) {
                    secondPerson = person;
                    band = true;
                }
            }
            if (e == HIJO or e == HIJA and band) {
                // cout << "Add -> " << firstPerson->getFullName() << " -> Child = " << secondPerson->getFullName() << endl;
                firstPerson->addChild(secondPerson);
            }
        }


        file.close();  // Cierra el archivo
    } else {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }
}

int main() {
    ifstream file("input.in");
    inputData(file);

    /*
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
    */

    menu();
    return 0;
}