// =====================================================================================
// Optional.cpp // std::optional
// =====================================================================================

module modern_cpp:optional;

namespace OptionalExamples {

    /*
    * Introduction
    */

    class Employee
    {
        operator int() {
            return 123;
        }
    };

    class AnyClass
    {
    private:
        int m_value;

    public:
        AnyClass() : AnyClass{ 0 } {}  // constructor chaining

        explicit AnyClass(int n) {
            m_value = n;
        }

        explicit AnyClass(double n) {
            m_value = (int) n;

        }

        explicit AnyClass(auto n) : m_value{} {  
        }

        operator bool() { 
            return true; 
        }

        operator int() {
            return 123;
        }
    };

    //bool cmp(const Employee& a, const Employee& b)
    //{
    //    return a.getAge() < b.getAge();
    //}

    static void test_01_optional() {

        // ====================================
        // 2 Richtungen:
        // 
        // Klasse nach Wert :  n = ac;    ac (Objekt) wird nach Wert gewandelt
        //                     ===> Type Conversion Operator  // operator type
        // Wert nach Klasse:   ac = 123;  Wert nach Objekt
        //                     ===> Type Conversion Contructors
        //                     Alle Konstruktoren mit EINEM Parameter sind solche Konstruktoren

        AnyClass ac;

        AnyClass ac2{ 123 };

        AnyClass ac3{ 123.456 };

        AnyClass ac4{ "123.456" };

        int n{};
        n = ac;

        if (ac) {
            ;
        }

        // Nebeneffekt // implizite Konvertierung
        // Achtung: Mit Keyword explicit wird das eine explizite Konvertierung
        ac = (AnyClass) 123;  // !!!!!!!! ????????? Wertzuweisung / Assignment

        std::optional<int> someValue{ 123 };

        int m = 123;

        std::optional<int*> ptrValue2{ };
        // nullptr

        auto z = ptrValue2.value();

        std::optional<int*> ptrValue{ nullptr };

        auto b = ptrValue.has_value();

        auto z2 = ptrValue.value();

        ptrValue = &m;

        if (ptrValue.has_value()) {
            std::println("Value: {}", someValue.value());
        }

        if (someValue.has_value()) {
            std::println("Value: {}", someValue.value());
        }

        if (someValue) {
            // providing an interface similar to smart pointers
            std::println("Value: {}", *someValue);
        }

        someValue = std::nullopt;

        if (someValue.has_value()) {
            std::println("Value: {}", someValue.value());
        }
        else {
            std::println("someValue does not contain a value!");
        }
    }

    /*
    * Using optionals to represent the absence of a value
    */ 

    class Contact
    {
    private:
        std::optional<std::string> m_phone;

    public:
        Contact() : m_phone{ std::nullopt } {}

        void setPhone(std::string phone) { m_phone = phone; }

        std::optional<std::string> getPhone() { return m_phone; }
    };

    static void test_02_optional() {

        Contact contact{};

        if (contact.getPhone()) {
            std::println("Number: {}", contact.getPhone().value());
        }
        else {
            std::println("No Number found!");
        }

        contact.setPhone("123456789");

        auto phone = contact.getPhone();

        if (phone.has_value()) {
            std::println("Number: {}", phone.value());
        }
        else {
            std::println("No Number found!");
        }
    }

    /*
    * Using optionals as return value / std::optional<T>::value_or()
    */

    static std::optional<double> divide(double a, double b) {

        if (b != 0.0) { 
            return a / b; 
        }

        return std::nullopt;
    }

    static void test_03_optional() {

        auto result{ divide(1.0, 3.0) };

        if (result.has_value()) {
            std::println("Result: {}", result.value());
        }
        else {
            std::println("Division by zero!");
        }

        result = divide(1.0, 0.0);

        if (result.has_value()) {
            std::println("Result: {}", result.value());
        }
        else {
            std::println("Division by zero!");
        }

        // Alternatively you can use std::optional<T>::value_or()
        // to use either the result or a default value

        result = divide(1.0, 1.0);

        const double defaultValue{};

        auto value = result.value_or(defaultValue);

        std::println("Result (or default value): {}", value);
    }

    /*
    * Demonstrating std::optional and emplace
    */

    static void test_04_optional() {

        // construct a std::vector<int> object inside std::optional in-place
        std::optional<std::vector<int>> optVec{
            std::make_optional<std::vector<int>>(5, 123)   // { 123, 123, 123, 123, 123 }
        };

        std::copy(
            optVec->begin(),
            optVec->end(),
            std::ostream_iterator<int>(std::cout, ", ")
        );
        std::cout << std::endl;

        std::set<int> ints{ 1, 2, 3, 4, 5 };

        // construct a std::vector<int> object inside std::optional in-place
        optVec.emplace(ints.begin(), ints.end());

        std::copy(
            optVec->begin(),
            optVec->end(),
            std::ostream_iterator<int>(std::cout, ", ")
        );
        std::cout << std::endl;
    }
}

void main_optional()
{
    using namespace OptionalExamples;
    test_01_optional();
    test_02_optional();
    test_03_optional();
    test_04_optional();
}

// =====================================================================================
// End-of-File
// =====================================================================================
