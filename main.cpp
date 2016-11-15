//Wai Phyo
//Robert Harris
//CS256-HW4
//completed on 02/15/2016

#include <iostream>
#include <string>
#include <sstream>
#include "Polynomial.h"

using std::string;

class PolyTester
{
public:
    void printResult(string output, bool pass) const
    {
        std::cout << (pass ? "PASS\t" : "FAIL\t")
              << output << std::endl;
    }

    void testExistence() const
    {
        Polynomial p;
        printResult("This should always pass.", true);
    }


    void testConstructors() const
    {
        Polynomial pDefault;
        printResult("default constructors", pDefault.coeff[0] == 0 && pDefault.size == 1);
        Polynomial pInt(5);
        printResult("int constructor", pInt.coeff[0] == 5 && pInt.size == 1);
        Polynomial pDouble(2.7);
        printResult("double constructor", pDouble.coeff[0] == 2.7 && pDouble.size == 1);
        double cf[5] = {2.1, 3.1, -2, 0, 5};
        int size = 5;
        Polynomial p(cf, size);
        bool pCorrect = true;
        for (int i = 0; i < size; i++)
        {
            if (p.coeff[i] != cf[i])
            {
                pCorrect = false;
            }
        }
        pCorrect &= p.size == size;
        printResult("array and int constructor", pCorrect);
        Polynomial pCopy(p);
        bool pCopyCorrect = true;
        for (int i = 0; i < size; i++)
        {
            if (pCopy.coeff[i] != p.coeff[i])
            {
                pCopyCorrect = false;
            }
        }
        pCopyCorrect &= pCopy.size == p.size;
        printResult("copy constructor", pCopyCorrect);
        pCopy = pDouble;
        bool pAssignCorrect = pCopy.coeff[0] == pDouble.coeff[0] 
                && pCopy.size == 1 && pDouble.size == 1;
        printResult("assignment operator", pAssignCorrect);
    }

    void testSizes() const
    {
        Polynomial p(4);
        bool lengthCorrect = p.getSize() == 1;
        double cf[7] = {3, 1.2, 6, 1, -5, 2.2, 3.14159};
        p = Polynomial(cf, 7);
        lengthCorrect &= p.getSize() == 7;
        printResult("getSize()", lengthCorrect);
        bool degreeCorrect = p.degree() == 6;
        double cf2[14] = {2.1, 3, -1, 4, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
        p = Polynomial(cf2, 14);
        degreeCorrect &= p.degree() == 7;
        printResult("degree()", degreeCorrect);
    }

    void testToString() const
    {
        Polynomial pTemp;
        printResult("str:0", pTemp.str() == "0");
        Polynomial p(2.1);
        printResult("str: 2.1", p.str() == "2.1");
        double cf[3] = {0, 0, 4};
        p = Polynomial(cf, 3);
        printResult("str: 4x^2", p.str() == "4x^2");
        double cf2[6] = {-1.3, 2, 3.14, 0, 0, 8};
        p = Polynomial(cf2, 6);
        printResult("str: 8x^5 + 3.14x^2 + 2x - 1.3", p.str() == "8x^5 + 3.14x^2 + 2x - 1.3");
        double cf3[9] = {0, 0, -1, 0, -1, 1, 2, 3, 4};
        p = Polynomial(cf3, 9);
        printResult("str: 4x^8 + 3x^7 + 2x^6 + x^5 - x^4 - x^2", p.str() == "4x^8 + 3x^7 + 2x^6 + x^5 - x^4 - x^2");
    }

    void testSolve() const
    {
        Polynomial p(7);
        printResult("7 solve(7)", p.solve(7) == 7);
        double cf[5] = {-3, 41, -6, 2, 9};
        p = Polynomial(cf, 5);
        printResult("9x^4 + 2x^3 - 6x^2 + 41x - 3 solve(3)", p.solve(3) == 849);
    }

    void testBrackets() const
    {
        Polynomial p(0);
        p[0] = 4;
        printResult("[0] = 4", p.coeff[0] == 4 && p.degree() == 0);
        p[1] = 2.1;
        printResult("[1] = 2.1", p.coeff[0] == 4 && p.coeff[1] == 2.1 && p.degree() == 1);
        p[4] = -5;
        printResult("[4] = -5", p.coeff[0] == 4 && p.coeff[1] == 2.1 && p.coeff[2] == 0 
                && p.coeff[3] == 0 && p.coeff[4] == -5 && p.degree() == 4);
    }

    void testArithmetic() const
    {
        Polynomial p1(3);
        Polynomial p2(8);
        Polynomial p3(p1 + p2);
        printResult("deg0 + deg0", p1.coeff[0] == 3 && p2.coeff[0] == 8 && p3.coeff[0] == 11 && p3.degree() == 0);
        double cf1[4] = {2, 1, -4, 9.3};
        double cf2[7] = {3, -1, 18.66, 2, -5, 11, -1};
        p1 = Polynomial(cf1, 4);
        p2 = Polynomial(cf2, 7);
        p3 = p1 + p2;
        double resCf[7] = {5, 0, 14.66, 11.3, -5, 11, -1};
        bool plusCorrect = true;
        for (int i = 0; i < 7; i++)
        {
            if (p3.coeff[i] != resCf[i])
            {
                plusCorrect = false;
            }
        }
        plusCorrect &= p3.degree() == 6;
        printResult("deg4 + deg7", plusCorrect);
        p3 = p3 - p3;
        printResult("p3 - p3", p3.coeff[0] == 0 && p3.degree() == 0);
        Polynomial p4(p1 * p2);
	printResult("p1 * p2", p4.str() == "-9.3x^9 + 106.3x^8 - 91.5x^7 + 47.6x^6 + 182.538x^5 - 91.94x^4 + 54.56x^3 + 24.32x^2 + x + 6");
        Polynomial p5(p1 * 4);
        printResult("p1 * 4", p5.str() == "37.2x^3 - 16x^2 + 4x + 8");
    }

    void testAssignments() const
    {
        double cf1[4] = {2, 1, -4, 9.3};
        double cf2[7] = {3, -1, 18.66, 2, -5, 11, -1};
        Polynomial p1(cf1, 4);
        Polynomial p2(cf2, 7);
        p1 += p2;
        printResult("p1 += p2", p1.str() == "-x^6 + 11x^5 - 5x^4 + 11.3x^3 + 14.66x^2 + 5");
        p1 -= p2;
        printResult("p1 -= p2", p1.str() == "9.3x^3 - 4x^2 + x + 2");
        p2 *= p1;
        printResult("p2 *= p1", p2.str() == "-9.3x^9 + 106.3x^8 - 91.5x^7 + 47.6x^6 + 182.538x^5 - 91.94x^4 + 54.56x^3 + 24.32x^2 + x + 6");
        p2 = p2 = p2 = p2 = p2 = p2 = p2;
        printResult("p2 = p2", p2.str() == "-9.3x^9 + 106.3x^8 - 91.5x^7 + 47.6x^6 + 182.538x^5 - 91.94x^4 + 54.56x^3 + 24.32x^2 + x + 6");
    }

    void testEquals() const
    {
        double cf1[4] = {2, 1, -4, 9.3};
        double cf2[7] = {3, -1, 18.66, 2, -5, 11, -1};
        Polynomial p1(cf1, 4);
        Polynomial p2(cf2, 7);
        Polynomial p3(p1);
        printResult("p1 == p3", p1 == p3);
        printResult("p1 != p2", p1 != p2);
        p1[0] = 2;
        p1[1] = 1;
        p1[2] = -4;
        p1[3] = 9.3;
        printResult("p1 != p2 after copy", p1 != p2);
    }

    void testOutput() const
    {
        double cf2[7] = {3, -1, 18.66, 2, -5, 11, -1};
        Polynomial p2(cf2, 7);
        std::ostringstream sout;
        sout << p2;
        std::string s = sout.str();
        printResult("Test <<", s == p2.str() && p2.str() == "-x^6 + 11x^5 - 5x^4 + 2x^3 + 18.66x^2 - x + 3");
    }

};

    

int main()
{
    PolyTester pt;
//while(1) //infinite loop to test memory leak
//{
    pt.testExistence();

    pt.testConstructors();
    pt.testSizes();
    pt.testToString();
    pt.testSolve();
    pt.testBrackets();
    pt.testArithmetic();
    pt.testAssignments();
    pt.testEquals();
    pt.testOutput();
    
//}
    return 0;
}
