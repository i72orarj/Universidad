#include <iostream>

class Pizza {
public:
    virtual int getPrice() const = 0;
    virtual ~Pizza() {};  // Declarar el destructor virtual es obligatorio
                          // si se redefine en la clase derivada.
                          // Por ello suele ponerse por si acaso.
};
 
class HamAndMushroomPizza : public Pizza {
public:
    virtual int getPrice() const { return 850; }; 
    virtual ~HamAndMushroomPizza() {}; 
};
 
class DeluxePizza : public Pizza {
public:
    virtual int getPrice() const { return 1050; }; 
    virtual ~DeluxePizza() {};
};
 
class HawaiianPizza : public Pizza {
public:
    virtual int getPrice() const { return 1150; }; 
    virtual ~HawaiianPizza() {}; 
};
 
class PizzaFactory {
public:
    enum PizzaType {
         HamMushroom,
         Deluxe,
         Hawaiian
    };
 
    static Pizza* createPizza(PizzaType pizzaType) {
        switch (pizzaType) {
            case HamMushroom:
                return new HamAndMushroomPizza();
            case Deluxe:
                return new DeluxePizza();
            case Hawaiian:
                return new HawaiianPizza();
        }
        throw "invalid pizza type.";
    }
};
 
/*
 * Create all available pizzas and print their prices
 */

/*
// Usando una función auxiliar

void pizza_information( PizzaFactory::PizzaType pizzatype )
{
	Pizza* pizza = PizzaFactory::createPizza(pizzatype);
	std::cout << "Price of " << pizzatype << " is " << pizza->getPrice() << std::endl;
	delete pizza;
}

int main ()
{
	pizza_information( PizzaFactory::HamMushroom );
	pizza_information( PizzaFactory::Deluxe );
	pizza_information( PizzaFactory::Hawaiian );
}
*/


// O directamente:

int main()
{
Pizza* pizza;

pizza = PizzaFactory::createPizza(PizzaFactory::HamMushroom);
std::cout << "Price of " << "HamMushroom" << " is " << pizza->getPrice() << std::endl;

pizza = PizzaFactory::createPizza(PizzaFactory::Deluxe);
std::cout << "Price of " << "Deluxe"<< " is " << pizza->getPrice() << std::endl;

pizza = PizzaFactory::createPizza(PizzaFactory::Hawaiian);
std::cout << "Price of " << "Hawaiian" << " is " << pizza->getPrice() << std::endl;
}

