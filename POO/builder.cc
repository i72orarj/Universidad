#include <string>
#include <iostream>

using namespace std;

// "Pizza" or any other product is complex to build because it needs many ingredients (operations, algorithms, steps, etc.)
class Pizza
{
	public:
		void setDough(const string& dough)
		{
			m_dough = dough;
		}
		void setSauce(const string& sauce)
		{
			m_sauce = sauce;
		}
		void setTopping(const string& topping)
		{
			m_topping = topping;
		}
		void open() const
		{
			cout << "Pizza with " << m_dough << " dough, " << m_sauce << " sauce and "
			<< m_topping << " topping. Mmmm." << endl;
		}
	private:
		string m_dough;
		string m_sauce;
		string m_topping;
};

// "Abstract Builder"
class PizzaBuilder
{
	public:
	    virtual ~PizzaBuilder() {};  // Declarar el destructor virtual es obligatorio
                          // si se redefine en la clase derivada.
                          // Por ello suele ponerse por si acaso.
		Pizza* getPizza()
		{
			return m_pizza;
		}
		void createNewPizzaProduct()
		{
			m_pizza = new Pizza;
		}
		virtual void buildDough() = 0;
		virtual void buildSauce() = 0;
		virtual void buildTopping() = 0; // And all necessary build methods
	protected:
		Pizza* m_pizza;     // Protected because will be modified by derived classes
};

//----------------------------------------------------------------
// Concrete builder 1
class HawaiianPizzaBuilder : public PizzaBuilder
{
	public:
	    virtual ~HawaiianPizzaBuilder() {}; 
		virtual void buildDough()
		{
			m_pizza->setDough("cross");  // Changing the protected m_pizza inherited object
		}
		virtual void buildSauce()
		{
			m_pizza->setSauce("mild");
		}
		virtual void buildTopping()
		{
			m_pizza->setTopping("ham+pineapple");
		}
};

// Concrete builder 2
class SpicyPizzaBuilder : public PizzaBuilder
{
	public:
	    virtual ~SpicyPizzaBuilder() {};
		virtual void buildDough()
		{
			m_pizza->setDough("pan baked"); // Changing the protected m_pizza inherited object
		}
		virtual void buildSauce()
		{
			m_pizza->setSauce("hot");
		}
		virtual void buildTopping()
		{
			m_pizza->setTopping("pepperoni+salami");
		}
};

//----------------------------------------------------------------

class Cook    // Director class
{
	public:
		void setPizzaBuilder(PizzaBuilder* pb)
		{
			m_pizzaBuilder = pb;
		}
		Pizza* getPizza()
		{
			return m_pizzaBuilder->getPizza();
		}
		void constructPizza()
		{      // CODIGO GENÉRICO
                       // el proceso dificil complejo de construir una Pizza
			m_pizzaBuilder->createNewPizzaProduct();
			m_pizzaBuilder->buildDough();
			m_pizzaBuilder->buildSauce();
			m_pizzaBuilder->buildTopping();
		}
	private:
		PizzaBuilder* m_pizzaBuilder;
};

int main()
{
	Cook cook;
    cout << "Cooking.... \n\n";
	PizzaBuilder* hawaiianPizzaBuilder = new HawaiianPizzaBuilder;
	PizzaBuilder* spicyPizzaBuilder   = new SpicyPizzaBuilder;
	
	cook.setPizzaBuilder(hawaiianPizzaBuilder);
	cook.constructPizza();   
	
	Pizza* hawaiian = cook.getPizza();
	hawaiian->open();
	// or cook.getPizza()->open();

	cook.setPizzaBuilder(spicyPizzaBuilder);
	cook.constructPizza();
	
	Pizza* spicy = cook.getPizza();
	spicy->open();
	
	delete hawaiianPizzaBuilder;
	delete spicyPizzaBuilder;
	delete hawaiian;  
	delete spicy;     
}