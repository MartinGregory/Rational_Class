// Code is based on LinkedIn Course - C++ Advanced Topics by Bill Weinman
// rational.cpp by Bill Weinman [bw.org]
// updated 2022-07-21

//  Further modified and expanded by Martin Gregory Sendrowicz on 5/29/23.
//  Rational.cpp

#include "Rational.h"

//........................................................................................................
/* Below is the 1st ever written recursion in history—it appears in Euclid's Elements (c. 300 BC). The GCF
(the Greatest Common Factor) aka GCD (the Greatest Common Divisor) of two (usually positive) integers is
the largest integer that divides both of them without leaving a remainder. In its simplest form, Euclid's
algorithm starts with a pair of positive integers, and forms a new pair that consists of the smaller number
and the difference between the larger and smaller numbers. The process repeats until the numbers in the pair
are equal. That number then is the greatest common divisor of the original pair of integers. The main
principle is that the GCD does not change if the smaller number is subtracted from the larger number. */
int gcf( int a , int b ){
    if( a==b ) return b ;
    if( a > b ) a = a - b ;
    if( b > a ) b = b - a ;
    return gcf( a , b ) ;
}
/* Reduces the current fraction to its lowest form. There are many ways of doing it, a recursive way or an
iterative way. */
Rational Rational::reduce() const {
    
    std::cout << "\n    reduce() \n" ;
    
    // Recursive approach
    int divisor = gcf( (*this).num , (*this).den ) ;
    return Rational( num/divisor, den/divisor ) ;
    
    // Iterative approach
//    if( n==0 || d<=3) return *this ;        // we do NOT reduce 0, 1/2 or 1/3  (warning! 1/1 2/2 and 3/3)
//
//    for( auto div = d-1 ; div ; --div ){
//        if( n%div == 0 && d%div == 0 ){
//            return Rational( n/div, d/div ) ;
//        }
//    }
//    return *this ;
}
//........................................................................................................
/* Prints out a string representation of the fraction with an integer part if the numerator is greater than
the denominator and a fractional part that's been reduced by the reduce function */
string Rational::str() const {
    if(den == 0) return nanstr ;
    if(den == 1 || num == 0) return std::to_string( num ) ;

    auto abs_n = std::abs( num ) ;     // absolute value
    if(abs_n > den) {
        auto whole = num / den ;
        auto remainder = abs_n % den ;
        if(remainder) return std::to_string( whole ) + " " + Rational( remainder,den ).str() ;
        else return std::to_string( whole ) ;
    } else {
        return reduce().raw_str();
    }
}
//........................................................................................................
/* Prints out the numerator and denominator as stored */
string Rational::raw_str() const {
    return std::to_string( num ) + "/" + std::to_string( den ) ;
}
//........................................................................................................
/* Copy Assignment operator=. Notice the use of 'this' ('this' is a keyword and not a variable). 'This' is
a pointer to the current object. I.e., when the class is instantiated as an object, 'this' contains the
address to that object. Note that having 'this' as a pointer allows us to compare it against the object on
the right hand side (rhs). Having a reference to the right hand side, allows us to use the address of
operator '&' to get the address of the right hand side, and we can compare them to see if they're the same
object. And if they are the same object (x = x), then obviously, we don't need to copy anything over. And
we just return, the reference to the current object. And so we do this by dereferencing the pointer i.e.
return *this, which gives us the object itself. And we can return a reference to that object with the
reference operator. The point of all of that is that this allows us to chain assignment operations. And so
we can say x = y = z, which is required by the C++ standard. So assignment operators will usually look very
much like this. */
Rational& Rational::operator = (const Rational& rhs) {
    std::cout << "Copy Assignment operator= called\n" ;
    if( this != &rhs) {     // the value stored in 'this' is the address so compare it against the address
        num = rhs.get_numerator() ;
        den = rhs.get_denominator() ;
    }
    return *this;   // dereference the pointer 'this' to get-to/return the object to which it points to
}
//........................................................................................................
/* Move Assignment operator = */
Rational& Rational::operator = ( Rational && rhs ) noexcept {
    std::cout << "Move Assignment operator= called\n" ;
    if( this != &rhs ){
        num = std::move( rhs.num ) ;
        den = std::move( rhs.den ) ;
        // Note that the primitive datatypes can NOT be moved hence I'm resetting the values below
        rhs.num = 0 ;
        rhs.den = 1 ;
    }
    return *this ;
}
//..................................................
/* Below we have our four arithmetic operators. We have addition, subtraction, multiplication, division.
Each of these simply uses the formula that we learned in high school for performing these operations on
fractions.
Note that each parameter list contains 2 parameters. This is necessary for situations in which a non-Rational
object is on the lhs -- e.g. 3 + rat. As explained above, they must be declared outside of the class -- i.e.
they can NOT be member functions */
Rational operator +(const Rational& lhs , const Rational& rhs) {
    std::cout << "  operator +\n" ;
    return Rational((lhs.num * rhs.den) + (lhs.den * rhs.num), lhs.den * rhs.den);
}
Rational operator -(const Rational& lhs , const Rational& rhs) {
    std::cout << "  operator -\n" ;
    return Rational(( lhs.num * rhs.den) - (lhs.den * rhs.num), lhs.den * rhs.den);
}
Rational operator *(const Rational& lhs , const Rational& rhs) {
    std::cout << "  operator *\n" ;
    return Rational(lhs.num * rhs.num, lhs.den * rhs.den);
}
Rational operator /(const Rational& lhs , const Rational& rhs) {
    std::cout << "  operator ÷\n" ;
    return Rational(lhs.num * rhs.den, lhs.den * rhs.num);
}
//........................................................................................................
/* The destructor doesn't really need to do anything, because we're not allocating any memory, and so it is
just resetting the values -- which is probably pointless in a destructor, but it's just there.*/
Rational::~Rational() {
    num = 0; den = 1 ;
    std::cout << "Destructor called\n" ;
}
//........................................................................................................
/* Unary Operators
Note that: the postfix versions are more expensive than the prefix versions. This is why many engineers
prefer the prefix operators in cases where it otherwise doesn't matter. The postfix version must first call
the copy constructor to instantiate temporary rational object 'temp', then perform the same job as its prefix
counterpart and then call the copy constructor once again to return the rational object by value. All this
extra work, while the prefix version calls NO constructors at all.
Note that modern compilers perform many optimizations and may implement a prefix versions on their own.*/
Rational& Rational::operator++(){        // pre-increment
    (*this).num += (*this).den ;
    return *this ;
}
Rational Rational::operator++( int ){    // post-increment
    auto temp = *this ;
    (*this).num += (*this).den ;
    return temp ;
}
Rational& Rational::operator--(){        // pre-decrement
    (*this).num -= (*this).den ;
    return *this ;
}
Rational Rational::operator--( int ){    // post-decrement
    auto temp = *this ;
    (*this).num -= (*this).den ;
    return temp ;
}
//........................................................................................................
//........................................................................................................
/* Below I tell the output stream operator how to print Rational objects. */
std::ostream & operator <<( std::ostream & out , Rational & r ){
    if( r.num == 0 )              // if the numerator is 0 print 0
        out << 0 << std::endl ;
    else if( r.num == r.den )       // if num == den print 1
        out << 1 << std::endl ;
    else if( r.num > r.den ) {      // if num > den we have an improper fraction, thus NOT a rational number
        out << r.num / r.den << " ";// print how many 'd'(s) in 'n'
         
        r = r.reduce() ;
        
        if( r.num % r.den==0 )      // and if they divide each other without any reminders we are done
            out << std::endl ;
        else out << r.num % r.den << "/" << r.den << std::endl ;  // else print the remainder over den
    }
    else
        out << r.num << "/" << r.den << std::endl ; // otherwise just print the fraction as is
    return out ;
}
//........................................................................................................









