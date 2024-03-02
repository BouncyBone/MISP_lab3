#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include "modRouteCipher.h"
#include <locale>
#include <codecvt>


using namespace std;
string wst (int k, wstring s1)
{
    PerestanCipher w(k);
    wstring s=w.CoderPerestanCipher(w, s1);
    const string s2 (s.begin(), s.end() );
    return s2;
}
string wst1 (int k, wstring s1)
{
    PerestanCipher w(k);
    wstring s=w.DecoderPerestanCipher(k, s1);
    const string s2 (s.begin(), s.end() );
    return s2;
}
SUITE (KeyTest)
{
    wstring test = L"ПРОСТОТЕКСТ";
    int k;
    TEST (ValidKey) {
        CHECK_EQUAL(wst(k=3,test),"ООКРТЕТПСТС");
    }
    TEST(EmptyKey) {
        CHECK_THROW(wst(k=999,test), cipher_error);
    }
    TEST(NegativeKey) {
        CHECK_THROW(wst(k=0,test), cipher_error);
    }

    TEST(A_characters_in_the_key_instead_of_numbers) {
        CHECK_THROW(wst(k=-3,test), cipher_error);
    }
}
SUITE(EncryptTest)
{
    TEST(ValidText) {
        CHECK_EQUAL(wst(3,L"ПРОСТОТЕКСТ"),"ООКРТЕТПСТС");
    }
    TEST(LowText) {
        CHECK_EQUAL(wst(3,L"ПростоТекст"),"оокртетПсТс");
    }
    TEST(SpaceText) {
        CHECK_EQUAL(wst(3,L"ПРОСТО ТЕКСТ"),"ООЕТРТТСПС К");
    }
    TEST(EmptyText) {
        CHECK_THROW(wst(3,L" "),cipher_error);
    }
    TEST(ValiDTextWithoutletters) {
        CHECK_THROW(wst(3,L"А?А?А?А?"),cipher_error);
    }
    TEST(TextWithNumber) {
        CHECK_EQUAL(wst(3,L"12345"),"32514");
    }
}
SUITE(DecryptText)
{
    TEST(ValidTEXT) {
        CHECK_EQUAL(wst1(3,L"ООКРТЕТПСТС"),"ПРОСТОТЕКСТ");
    }
    TEST(LowTEXT) {
        CHECK_EQUAL(wst1(3,L"оокртетПсТс"),"ПростоТекст");
    }
    TEST(SpaceTEXT) {
        CHECK_EQUAL(wst1(3,L"ООЕТРТТСПС К"),"ПРОСТО ТЕКСТ");
    }
    TEST(EmptyTEXT) {
        CHECK_THROW(wst1(3,L" "),cipher_error);
    }
    TEST(TextNumberText) {
        CHECK_EQUAL(wst1(3,L"32514"),"12345");
    }
    TEST(TextSymbolText) {
        CHECK_EQUAL(wst1(3,L"А??А?А?А"),"А?А?А?А?");
    }

}

int main()
{
    return UnitTest::RunAllTests();
}