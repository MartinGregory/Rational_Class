// Code is based on LinkedIn Course - C++ Advanced Topics by Bill Weinman
// rational.cpp by Bill Weinman [bw.org]
// updated 2022-07-21

//  Further modified and expanded by Martin Gregory Sendrowicz on 5/29/23.
//  Rational.cpp

#ifndef _Rational_h_
#define _Rational_h_



#include <string>
#include <iostream>

using std::string ; // We're using the 'string' symbol, importing it into our own name space.

const string nanstr {"[NAN]"};  // a constant string for NOT A Number

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
/* Rational class is a class that performs function arithmetic on rational numbers as fractions.*/
class Rational {
    
private:// data members
    int num {0};      // numerator
    int den {1};      // denominator
    
public:// member functions
    /* Default Constructor
    You notice that we have default values for the numerator and the denominator. This allows this
    constructor to operate as an implicitly converting constructor. E.g. passing const value of 3 to the
    Rational constructor will convert it into a fraction 3/1. */
    Rational(int numerator = 0, int denominator = 1) : num(numerator), den(denominator) {
        std::cout << "Default Constructor called\n" ;
    }
    //....................................................................................................
    /* Copy Constructor */
    Rational(const Rational& rhs) : num(rhs.num), den(rhs.den) {
        std::cout << "Copy Constructor called\n" ;
    }
    //....................................................................................................
    /* Move Constructor -- note that we can NOT move primitive datatypes like: int, float, etc... Ergo
    to emulate a move Move Constructor I'm resetting the rhs object's data.*/
    Rational( Rational && rhs ) noexcept : num{ std::move(rhs.num) } , den{ std::move(rhs.den) } {
        std::cout << "Move Constructor called\n" ;
        rhs.num = 0 ;
        rhs.den = 1 ;
    }
    //....................................................................................................
    
    ~Rational();
    //....................................................................................................
    // Utility Functions
    int get_numerator() const { return num ; }
    int get_denominator() const { return den ; }
    void set_numerator( int val ) { num=val ; }
    void set_denominator( int val ) { den=val ; }
    //....................................................................................................
    Rational reduce() const ;    // reduce fraction
    //....................................................................................................
    /* Converts rational object 'r' into its string representation i.e. it returns a formatted STL string.
     E.g. std::string s = r.str() ;
     Note that in the implementation below, str() also reduces the fraction. */
    string str() const;
    //....................................................................................................
    /* Converts rational object 'r' into its string representation i.e. it returns a formatted STL string.
     E.g. std::string s = r.raw_str() ;
     Note that in the implementation, raw_str() returns a non-reduced form of the fraction */
    string raw_str() const;
    //....................................................................................................
    /* An overloaded string conversion operator allows us to perform string concatenation between
     std::string 's' and rational object 'r' i.e. 's += r'. This works because the expression 's += r' is
     expecting a string which forces the compiler to look for a string conversion operator that will
     convert 'r' into a string. Ergo this overloaded string conversion operator allows every rational object
     to operate as if it were a string, and to return a viable string value that can then be concatenated
     to another string object. */
    operator string() {      // OR operator auto() { return str() ; }
        std::cout << "String Conversion operator called.\n" ;
        return str() ;
    }
    /* Note: the conversion operator overload is a common and useful technique that allows you to use your
       class as a first-class type, fully controlling how it is cast to other types. */
    //....................................................................................................
    // Operator Overloads
    /* copy assignment operator = */
    Rational& operator = ( const Rational & ) ;
    /* move assignment operator = */
    Rational& operator = ( Rational && ) noexcept ;
    //..................................................
    /* Below are overloaded operators + - * ÷
    Note that having the Overloaded Operators as member functions will NOT work for cases where and
    non-Rational object is on the left-hand-side, e.g. 3 + rat. To solve this dilemma you must overload
    each operator outside of the class and make these external functions friends of the class. Also each
    of the external functions must have two parameters so that when e.g. 3+rat is called, 3 will be
    implicitly promoted/converted into a valid Rational. So as a rule of thumb, whenever you have a
    constructor that allows implicit conversions like this one does, you'll want to think about non-number
    overload functions. These functions, of course, still go in your implementation file.
    So :
    Rational operator + (const Rational&) const ;
    Rational operator - (const Rational&) const ;
    Rational operator * (const Rational&) const ;
    Rational operator / (const Rational&) const ; */
    friend Rational operator +(const Rational& , const Rational&) ;
    friend Rational operator -(const Rational& , const Rational&) ;
    friend Rational operator *(const Rational& , const Rational&) ;
    friend Rational operator /(const Rational& , const Rational&) ;
    //....................................................................................................
    /* The unary increment and decrement operators are special cases with a few interesting twists.
    How does the compiler tell the difference from prefix and postfix? The postfix has the keyword ‘int’ in
    the parameter list. This is NOT because an integer is being passed as a parameter (in our case it clearly
    is NOT)—nor is it because our class is wrapping around an integer value (again in our case it clearly is
    NOT). The keyword ‘int’ is used in both postfix cases as a little hack to tell the compiler that this is
    the postfix version of the increment/decrement operator.*/
    Rational& operator++() ;        // pre-increment
    Rational operator++( int ) ;    // post-increment
    Rational& operator--() ;        // pre-decrement
    Rational operator--( int ) ;    // post-decrement
    //....................................................................................................
    friend std::ostream& operator <<( std::ostream & out , Rational & rat ) ;
} ;
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


#endif /* _Rational_h_ */
