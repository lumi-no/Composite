#include <iostream>
#include <vector>
#include <string>


class Component {
public:
    virtual ~Component() = default;
    virtual void Operation() const = 0;

    
    virtual void Add(Component* component) {}
    virtual void Remove(Component* component) {}
    virtual bool IsComposite() const { return false; }
};


class Leaf : public Component {
public:
    void Operation() const override {
        std::cout << "Leaf: Виконується операція." << std::endl;
    }
};


class Composite : public Component {
private:
    std::vector<Component*> children_; 

public:
    ~Composite() {
        for (Component* child : children_) {
            delete child;
        }
    }

    void Add(Component* component) override {
        children_.push_back(component);
    }

    void Remove(Component* component) override {
        children_.erase(std::remove(children_.begin(), children_.end(), component), children_.end());
    }

    bool IsComposite() const override {
        return true;
    }

    void Operation() const override {
        std::cout << "Composite: Виконується операція для всіх дочірніх елементів (" << children_.size() << "):" << std::endl;
        for (const Component* child : children_) {
            child->Operation();
        }
    }
};

void ClientCode(const Component* component) {
    component->Operation();
}


void ClientCode2(Component* component1, Component* component2) {
    if (component1->IsComposite()) {
        component1->Add(component2);
    }
    component1->Operation();
}

int main() {
  
    Component* simple = new Leaf;
    std::cout << "Клієнт: Робота з простим компонентом:\n";
    ClientCode(simple);

   
    Component* tree = new Composite;
    Component* branch1 = new Composite;
    Component* branch2 = new Composite;

    Component* leaf1 = new Leaf;
    Component* leaf2 = new Leaf;
    Component* leaf3 = new Leaf;

    branch1->Add(leaf1);
    branch1->Add(leaf2);
    branch2->Add(leaf3);

    tree->Add(branch1);
    tree->Add(branch2);

    std::cout << "\nКлієнт: Робота зі складним деревом компонентів:\n";
    ClientCode(tree);

    std::cout << "\nКлієнт: Додавання компонента до контейнера:\n";
    ClientCode2(tree, simple);

 
    delete simple;
    delete tree;

    return 0;
}

