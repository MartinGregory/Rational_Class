//  Code By Martin Gregory Sendrowicz on 5/29/23.
//  Rational.cpp

#include "Rational.h"
#include <iostream>

//........................................................................................................
void test1(){
    
    Rational a {7};         // default constructor
    std::cout <<"a = "<< a.raw_str() <<" is "<< a ;         // → a = 7/1 is 7

    Rational b(25, 15);     // default constructor
    std::cout <<"b = "<< b.raw_str() <<" is "<< b ;         // → b = 25/15 is 1 2/3

    auto c = b;             // copy constructor
    std::cout <<"c = "<< c.raw_str() <<" is "<< c ;         // → c = 5/3 is 1 2/3

    Rational d;             // default constructor
    std::cout <<"d = "<< d.raw_str() <<" is "<< d ;         // → d = 0/1 is 0

    d = c;                  // copy assignment operator=
    std::cout <<"d = "<< d.raw_str() <<" is "<< d ;         // → d = 5/3 is 1 2/3

    auto & e = d;           // reference
    d = e;                  // assignment to self!
    std::cout <<"e = "<< e.raw_str() <<" is "<< e ;         // → e = 5/3 is 1 2/3
    std::cout <<"d = "<< d.raw_str() <<" is "<< d ;         // → d = 5/3 is 1 2/3
    
    /*  Default Constructor called for 'a'
        a = 7/1 is 7
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational

        Default Constructor called for 'b'
        b = 25/15 is 1
            reduce()
                Default Constructor called
                Move Assignment operator= called
                Destructor called
        2/3
        Copy Constructor called for 'c'
        c = 5/3 is 1
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        2/3
        Default Constructor called for 'd'
        d = 0/1 is 0
        Copy Assignment operator= called for 'd' (i.e. d = c)
        d = 5/3 is 1
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        2/3
        Copy Assignment operator= called for 'd' (i.e. d = e )
        e = 5/3 is 1
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        2/3
        d = 5/3 is 1
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        2/3
        Destructor called for 'd'
        Destructor called for 'c'
        Destructor called for 'b'
        Destructor called for 'a'       */
}
//........................................................................................................
void test2(){
    
    Rational a ;
    std::cout <<"a = "<< a.str() <<" : " << a.raw_str() <<" is "<< a ;        // → a = 0 : 0/1 is 0
    /*  Default Constructor called for 'a'
        a = 0 : 0/1 is 0
        Destructor called for 'a'   */
    
    Rational b { 3 } ;
    std::cout <<"b = "<< b.str() <<" : " << b.raw_str() <<" is "<< b ;              // → b = 3 : 3/1 is 3
    /*  Default Constructor called for 'b'
        b = 3 : 3/1 is 3
        reduce():
            Default Constructor called for unnamed temporary Rational
            Move Assignment operator= called for the returned Rational
            Destructor called for unnamed temporary Rational
        Destructor called for 'b'       */
    
    Rational c = b ;
    std::cout <<"c = "<< c.str() <<" : " << c.raw_str() <<" is "<< c ;                  // → c = 3 : 3/1 is 3
    /*  Copy Constructor called for 'c'
        c = 3 : 3/1 is 3
        reduce():
            Default Constructor called for unnamed temporary Rational
            Move Assignment operator= called for the returned Rational
            Destructor called for unnamed temporary Rational
        Destructor called for 'c'      */
    
    Rational d {252,105} ;
    std::cout << "252/105 can be reduced to: " << d.reduce().raw_str() << std::endl  ;
    // 252/105 can be reduced to: 12/5
    std::cout << "252/105 can be reduced to: " << d.reduce().str() << std::endl  ;
    // 252/105 can be reduced to: 2 2/5
}
//........................................................................................................
/* Adding Literals and Rational objects */
void test3(){
    
    Rational b {3,5} ;
    Rational temp = b + 3 ;
    std::cout <<"b + 3 = "<< temp  ;                       // → b + 3 = 3 3/5
    
    /*  Default Constructor called for 'b'
        Default Constructor called for '3' (acts as a Conversion Constructor)
            operator +
                Default Constructor called for unnamed temporary Rational
                Destructor called for unnamed temporary Rational
        Rational 'temp' is created via Copy Elision (compiler optimization)
        b + 3 = 3
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        3/5     */
    
    temp = 3 + b ;
    std::cout <<"3 + b = "<< temp  ;                       // → 3 + b = 3 3/5
     
    /*  Default Constructor called for '3' (acts as a Conversion Constructor)
            operator +
                Default Constructor called for unnamed temporary Rational
                Destructor called for unnamed temporary Rational
        Rational 'temp' is assigned via Copy Elision (else move assignment operator= would be called)
        Destructor called for '3'
        3 + b = 3
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        3/5
        Destructor called for 'temp'
        Destructor called for 'b'  */
}
//........................................................................................................
// Binary Arithmetic
void test4(){
    
    Rational a {3,7} ;
    Rational b {2,5} ;
    
    Rational temp = a + b ;
    std::cout <<"a + b = "<< temp  ;                        // → a + b = 29/35
    temp = a - b ;
    std::cout <<"a - b = "<< temp  ;                        // → a - b = 1/35
    temp = a * b ;
    std::cout <<"a * b = "<< temp  ;                        // → a * b = 6/35
    temp = a / b ;
    std::cout <<"a / b = "<< temp  ;                        // → a / b = 1 1/14
    
    /*  Default Constructor called for 'a'
        Default Constructor called for 'b'
        operator +
            Default Constructor called for unnamed temporary Rational
        Rational 'temp' is created via Copy Elision (compiler optimization)
        a + b = 29/35
     
        operator -
            Default Constructor called for unnamed temporary Rational
            Destructor called
        Rational 'temp' is assigned via Copy Elision (else move assignment operator= would be called)
        a - b = 1/35
     
        operator *
            Default Constructor called
            Destructor called
        Rational 'temp' is assigned via Copy Elision (else move assignment operator= would be called)
        a * b = 6/35
     
        operator ÷
            Default Constructor called
            Destructor called
        Rational 'temp' is assigned via Copy Elision (else move assignment operator= would be called)
        a / b = 1
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        1/14
        Destructor called for 'temp'
        Destructor called for 'b'
        Destructor called for 'a'   */
}
//........................................................................................................
/* The func below is to test how the compiler implicitly converts Rational objects into std::string's
using the overloaded operator string() */
void print( const std::string & s ){
    std::cout << s << std::endl ;
}
//..................................................
/* Rational to string conversions */
void test5() {
    Rational f( 5,4 ) ;
    string s {"Rational is "} ;
    // Below Rational 'f' gets implicitly converted to string then as a string is concatenated to 's'
    s += f ;
    std::cout <<"s += f = "<< s <<std::endl ;               // → s += f = Rational is 1 1/4
    
    string x = f.str() ;
    std::cout << "x = f.str() = " << x << std::endl ;       // → x = f.str() = 1 1/4
    
    string y = f.raw_str() ;
    std::cout << "x = f.raw_str() = " << y << std::endl ;   // → x = f.raw_str() = 5/4
    
    /* The compiler uses f.str() for implicitly convert 'f' into a std::string so that it can be passed as
    an argument to the above print( const std::string & s ) function */
    print( f ) ;                                          // → 1 1/4
    
    
    /*  Default Constructor called for 'f'
        String Conversion operator called for 's'
        Default Constructor called while converting 's'
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        Destructor called for converted 's'
        s += f = Rational is 1 1/4
     
        Default Constructor called for unnamed temporary Rational in str()
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        Destructor called for unnamed temporary Rational in str()
        x = f.str() = 1 1/4
        x = f.raw_str() = 5/4
     
        String Conversion operator called for 'f' in print(f)
        Default Constructor called for unnamed temporary Rational in str()
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        Destructor called for unnamed temporary Rational in str()
        1 1/4
        Destructor called for 'f'           */
}
//........................................................................................................
/* Below I'm testing the overloaded post and pre increment/decrement operators */
void test6() {
    
    Rational g( 3,4 ) ;
    std::cout << "g = " << g ;                              // → g = 3/4
    std::cout << "++g = " << ++g ;                          // → ++g = 1 3/4
    std::cout << "g++ = " << (g++).str() << std::endl ;     // → g++ = 1 3/4
    std::cout << "g = " << g ;                              // → g = 2 3/4
    
    std::cout << "--g = " << --g ;                          // → --g = 1 3/4
    std::cout << "g-- = " << (g--).str() << std::endl ;     // → g-- = 1 3/4
    std::cout << "g = " << g ;                              // → g = 3/4
    
    /*  Default Constructor called for 'g'
        g = 3/4
        ++g = 1
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        3/4
     
        g++ =
            Copy Constructor called for 'temp' inside operator++( int )
            Default Constructor called for unnamed Rational inside str()
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
            Destructor called for unnamed Rational inside str()
        1 3/4
            Destructor called  for for 'temp' inside operator++( int )
     
        g = 2
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        3/4
     
        --g = 1
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
        3/4
     
        g-- =
            Copy Constructor called for 'temp' inside operator++( int )
            Default Constructor called for unnamed Rational inside str()
            reduce()
                Default Constructor called for unnamed temporary Rational
                Move Assignment operator= called for the returned Rational
                Destructor called for unnamed temporary Rational
            Destructor called for unnamed Rational inside str()
        1 3/4
            Destructor called for 'temp' inside operator++( int )
        g = 3/4
        Destructor called for 'g'  */
}
//........................................................................................................
/* Below I'm testing Move Constructor and Move Assignment operator= */
void test7(){
    
    Rational a {2,3} ;
    Rational b = std::move( a ) ;
    
    std::cout << "a = " << a.raw_str() << std::endl ;
    std::cout << "b = " << b.raw_str() << std::endl ;
    
    Rational c ;
    c = std::move( b ) ;
    
    std::cout << "b = " << b.raw_str() << std::endl ;
    std::cout << "c = " << c.raw_str() << std::endl ;
    
    /*  Default Constructor called for 'a'
        Move Constructor called for 'b'
        a = 0/1
        b = 2/3
        Default Constructor called for 'c'
        Move Assignment operator= called for 'c' (i.e. c = std::move( b )) ;
        b = 0/1
        c = 2/3
        Destructor called for 'c'
        Destructor called for 'b'
        Destructor called for 'a'  */
}
//........................................................................................................
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
int main() {
    
    //test1() ;
    //test2() ;
    //test3() ;
    //test4() ;
    //test5() ;
    //test6() ;
    test7() ;
    
    return 0 ;
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



